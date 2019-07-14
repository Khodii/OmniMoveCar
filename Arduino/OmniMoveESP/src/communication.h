#pragma once

#include "movement.h"
#include <ESPAsyncWebServer.h>

/**
 * Limitations due to js:
 * Buffer has to be all the same type
 * 
 * Type is int16 as well at the start of the array
 * 
 */
enum OmniMessageType {
    DRIVE = 0,        //L4 {x1} int16 [-1023, 1023] :: {y1} int16 [-1023, 1023] :: {x2} int16 [-1023, 1023] :: {y2} int16 [-1023, 1023]
    CURR_GYRO = 1,    //L18 {speed m/s} (x) int16 (y) int16 (z) int16 :: {accel m/s^2} (x) int16 (y) int16 (z) int16 :: {rot} (x) int16 (y) int16 (z) int16
    CURR_BATTERY = 2, //L4 {cell1} int16 [0, 2^12] :: {cell2} int16 [0, 2^12]
    CURR_MOTOR = 3,   //L4 {vl} int16 [-1023, 1023] :: {vr} int16 [-1023, 1023] :: {hl} int16 [-1023, 1023] :: {hr} int16 [-1023, 1023]
};

struct XYZ {
    int16_t x;
    int16_t y;
    int16_t z;
};

class Communication {
public:
    static void onWSData(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, uint8_t *data, size_t len);
    static void onDrive(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
    static void sendCurrGyro(XYZ speed, XYZ accel, XYZ rot);
    static void sendCurrBattery(uint16_t cell1, uint16_t cell2);
    static void sendCurrMotor(int16_t vl, int16_t vr, int16_t hl, int16_t hr);

    static AsyncWebSocket *ws;
};