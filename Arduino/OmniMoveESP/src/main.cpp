#include "MPU6050.h"
#include "communication.h"
#include "movement.h"
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <Wire.h>

// Replace with your network credentials
const char *ssid = "ESP32-OmniMove";
const char *password = "123456789";

// const byte DNS_PORT = 53;
const IPAddress apIP = IPAddress(192, 168, 4, 1);

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
MPU6050 mpu;

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {

    switch (type) {
    case WS_EVT_CONNECT:
        Serial.printf("Client connected from %s\n", client->remoteIP().toString().c_str());
        break;

    case WS_EVT_DATA:
        Communication::onWSData(server, client, type, data, len);
        break;

    default:
        break;
    }
}

void setup() {
    // enableCore1WDT();
    Serial.begin(115200);

    Wire.begin();

    mpu.initialize();

    // mpu.CalibrateAccel_MPU6500(6);
    // mpu.CalibrateGyro(6);

    // mpu.PrintActiveOffsets_MPU6500();
    mpu.setXGyroOffset(96);
    mpu.setYGyroOffset(92);
    mpu.setZGyroOffset(-20);

    // Serial.printf("\n");
    Movement::initPWM();

    // enable AP with dns
    WiFi.mode(WIFI_AP);

    // Setup websockets
    ws.onEvent(onEvent);
    server.addHandler(&ws);
    Communication::ws = &ws;
    ws.enable(true);

    // Initialize SPIFFS
    if (!SPIFFS.begin(true)) {
        while (true) {
            Serial.println("An Error has occurred while mounting SPIFFS");
            delay(1000);
        }
        return;
    } else {
        Serial.println("Mounted SPIFFS succesfully");
    }

    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        // Serial.println("request on index");
        request->send(SPIFFS, "/index.html", String(), false, nullptr);
    });

    // Route to load style.css file
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        // Serial.println("request on style");
        request->send(SPIFFS, "/style.css", "text/css");
    });

    // Route to load code.js file
    server.on("/code.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        // Serial.println("request on code");
        request->send(SPIFFS, "/code.js", "text/javascript");
    });

    // Route to load code.js file
    server.on("/progressbar.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        // Serial.println("request on progressbar");
        request->send(SPIFFS, "/progressbar.min.js", "text/javascript");
    });

    // WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.setSleep(false);
    WiFi.softAP(ssid, password, 6, 1);
    delay(1000);

    server.begin();
}

void loop() {

    // put your main code here, to run repeatedly:
    // dnsServer.processNextRequest();
    uint16_t v = analogRead(39);
    int16_t x, y, z, gx, gy, gz, temp;

    temp = mpu.getTemperature();
    mpu.getMotion6(&x, &y, &z, &gx, &gy, &gz);

    // Serial.printf("x: %6.2fg, y: %6.2fg, z: %6.2fg, gx: %6.2f°/s, gy: %6.2f°/s, gz: %6.2f°/s, temp: %6.2f°C\r", x / 16384.0, y / 16384.0, z / 16384.0, gx / 250.0, gy / 250.0, gz / 250.0, temp / 340.0 + 36.53);
    // power = (v / 4095 * 3.1 + .1) * 3;
    Communication::sendCurrGyBatComb(0, 0, 0, x, y, z, gx, gy, gz, v, temp);
    delay(1000);
}