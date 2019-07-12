#include "communication.h"

void Communication::onWSData(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, uint8_t *data, size_t len) {
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
    Serial.printf("Driving with speed: %i, %i and %i, %i now\n", x1, y1, x2, y2);
}

void Communication::sendCurrGyro(XYZ speed, XYZ accel, XYZ rot) {
    int16_t buff[10] = {OmniMessageType::CURR_GYRO, speed.x, speed.y, speed.z, accel.x, accel.y, accel.z, rot.x, rot.y, rot.z};
    ws->binaryAll((uint8_t *)buff, 10);
}

AsyncWebSocket *Communication::ws;