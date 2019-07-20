#include "communication.h"

AsyncWebSocketClient *ws_client = nullptr;

void Communication::onWSData(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, uint8_t *data, size_t len) {
    ws_client = client;

    int16_t *d16 = (int16_t *)data;
    int16_t id = d16[0];

    switch (id) {
    case OmniMessageType::DRIVE:
        onDrive(d16[1], d16[2], d16[3], d16[4]);
        break;

    default:
        Serial.printf("No such command %i\n", id);
        break;
    }
}

void Communication::onDrive(int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
    // Serial.printf("Driving with speed: %i, %i and %i, %i now\n", x1, y1, x2, y2);
    Movement::drive(y1, x1, x2);
}

void Communication::sendCurrGyro(XYZ speed, XYZ accel, XYZ rot) {
    int16_t buff[10] = {OmniMessageType::CURR_GYRO, speed.x, speed.y, speed.z, accel.x, accel.y, accel.z, rot.x, rot.y, rot.z};
    ws->binaryAll((uint8_t *)buff, 20);
}

void Communication::sendCurrGyBatComb(int16_t sX, int16_t sY, int16_t sZ, int16_t aX, int16_t aY, int16_t aZ, int16_t rX, int16_t rY, int16_t rZ, int16_t bat, int16_t temp) {
    int16_t buff[12] = {OmniMessageType::CURR_GY_BAT_COMB, sX, sY, sZ, aX, aY, aZ, rX, rY, rZ, bat, temp};
    ws->binaryAll((uint8_t *)buff, 24);
}

void Communication::sendCurrMotor(int16_t vl, int16_t vr, int16_t hl, int16_t hr) {
    int16_t buff[5] = {OmniMessageType::CURR_MOTOR, vl, vr, hl, hr};
    // Serial.println("should send now");
    ws->binaryAll((uint8_t *)buff, 10);
}

void Communication::sendCurrBattery(int16_t cell1, int16_t cell2) {
    int16_t buff[5] = {OmniMessageType::CURR_BATTERY, cell1, cell2};
    // Serial.println("should send now");
    ws->binaryAll((uint8_t *)buff, 10);
}

AsyncWebSocket *Communication::ws;