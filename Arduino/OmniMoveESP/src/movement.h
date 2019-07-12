#pragma once

#include <Arduino.h>
#include <math.h>

class Motor {
private:
    char channel;
    char pin_dir1;
    char pin_dir2;

public:
    Motor(char channel, char pin_dir1, char pin_dir2) : channel(channel), pin_dir1(pin_dir1), pin_dir2(pin_dir2){};
    ~Motor() {}

    /**
     * speed in [-1023; 1023]
     */
    void setSpeed(int16_t speed);

    void stop();
};

class Movement {
private:
    /* data */
public:
    static const char PIN_LED = 2;

    static Motor MOTOR_VL;
    static Motor MOTOR_VR;
    static Motor MOTOR_HL;
    static Motor MOTOR_HR;

    /** Amount of values down from 1023 which can be used */
    static const int USEABLE_UPPER_LIMIT = 300;

    static const char PIN_MOTOR_VL_EN = 23;
    static const char PIN_MOTOR_VL_DIR1 = 18;
    static const char PIN_MOTOR_VL_DIR2 = 19;

    static const char PIN_MOTOR_VR_EN = 32;
    static const char PIN_MOTOR_VR_DIR1 = 12;
    static const char PIN_MOTOR_VR_DIR2 = 13;

    static const char PIN_MOTOR_HL_EN = 16;
    static const char PIN_MOTOR_HL_DIR1 = 17;
    static const char PIN_MOTOR_HL_DIR2 = 5;

    static const char PIN_MOTOR_HR_EN = 4;
    static const char PIN_MOTOR_HR_DIR1 = 2;
    static const char PIN_MOTOR_HR_DIR2 = 15;

    static const int PWM_FREQ = 5000;
    static const char CH_LED = 0;
    static const char CH_MOTOR_VL = 1;
    static const char CH_MOTOR_VR = 2;
    static const char CH_MOTOR_HL = 3;
    static const char CH_MOTOR_HR = 4;
    static const char PWM_RESOLUTION = 10; //Resolution 8, 10, 12, 15

    static void initPWM();

    static void driveMotor(char channel, char dir1, char dir2, int speed);

    /**
      * Converts the given controls into wheel speeds
      * Alogrithm source: http://eprints.utem.edu.my/16543/1/Omni%20Directional%20Control%20Algorithm%20For%20Mecanum%20Wheel%2024%20Pages.pdf
      */
    static void drive(int controlFront, int controlSide, int controlTurn);
};
