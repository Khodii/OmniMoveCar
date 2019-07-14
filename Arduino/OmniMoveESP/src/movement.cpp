#include "movement.h"

// ----------------------------------- Motor Class -------------------------------------------------------
// ############### Functions ####################
void Motor::setSpeed(int16_t speed) {
    // disable before before changing direction
    // (probably not needed) safety to prevent shoutthrough
    ledcWrite(channel, 0);
    if (speed > 0) {
        digitalWrite(pin_dir1, LOW);
        digitalWrite(pin_dir2, HIGH);
    } else if (speed < 0) {
        digitalWrite(pin_dir1, HIGH);
        digitalWrite(pin_dir2, LOW);
    } else {
        digitalWrite(pin_dir1, LOW);
        digitalWrite(pin_dir2, LOW);
        return;
    }

    ledcWrite(channel, abs(speed));
}

void Motor::stop() {
    ledcWrite(channel, 0);
    digitalWrite(pin_dir1, LOW);
    digitalWrite(pin_dir2, LOW);
}

// ----------------------------------- Movement Class -------------------------------------------------------
// ############### Attributes ####################
Motor Movement::MOTOR_VL = Motor(CH_MOTOR_VL, PIN_MOTOR_VL_DIR1, PIN_MOTOR_VL_DIR2);
Motor Movement::MOTOR_VR = Motor(CH_MOTOR_VR, PIN_MOTOR_VR_DIR1, PIN_MOTOR_VR_DIR2);
Motor Movement::MOTOR_HL = Motor(CH_MOTOR_HL, PIN_MOTOR_HL_DIR1, PIN_MOTOR_HL_DIR2);
Motor Movement::MOTOR_HR = Motor(CH_MOTOR_HR, PIN_MOTOR_HR_DIR1, PIN_MOTOR_HR_DIR2);

// ############### Functions ####################
void Movement::initPWM() {
    Serial.println("Initing PWMs");

    // Setting all pins to output
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_MOTOR_VL_EN, OUTPUT);
    pinMode(PIN_MOTOR_VL_DIR1, OUTPUT);
    pinMode(PIN_MOTOR_VL_DIR2, OUTPUT);

    pinMode(PIN_MOTOR_VR_EN, OUTPUT);
    pinMode(PIN_MOTOR_VR_DIR1, OUTPUT);
    pinMode(PIN_MOTOR_VR_DIR2, OUTPUT);

    pinMode(PIN_MOTOR_HL_EN, OUTPUT);
    pinMode(PIN_MOTOR_HL_DIR1, OUTPUT);
    pinMode(PIN_MOTOR_HL_DIR2, OUTPUT);

    pinMode(PIN_MOTOR_HR_EN, OUTPUT);
    pinMode(PIN_MOTOR_HR_DIR1, OUTPUT);
    pinMode(PIN_MOTOR_HR_DIR2, OUTPUT);

    // Disable all pins by default to not possibly cause shootthrough
    digitalWrite(PIN_MOTOR_VL_EN, LOW);
    digitalWrite(PIN_MOTOR_VL_DIR1, LOW);
    digitalWrite(PIN_MOTOR_VL_DIR2, LOW);

    digitalWrite(PIN_MOTOR_VR_EN, LOW);
    digitalWrite(PIN_MOTOR_VR_DIR1, LOW);
    digitalWrite(PIN_MOTOR_VR_DIR2, LOW);

    digitalWrite(PIN_MOTOR_HL_EN, LOW);
    digitalWrite(PIN_MOTOR_HL_DIR1, LOW);
    digitalWrite(PIN_MOTOR_HL_DIR2, LOW);

    digitalWrite(PIN_MOTOR_HR_EN, LOW);
    digitalWrite(PIN_MOTOR_HR_DIR1, LOW);
    digitalWrite(PIN_MOTOR_HR_DIR2, LOW);

    // configure LED PWM functionalitites
    ledcSetup(CH_LED, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(CH_MOTOR_VL, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(CH_MOTOR_VR, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(CH_MOTOR_HL, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(CH_MOTOR_HR, PWM_FREQ, PWM_RESOLUTION);

    // attach the channel to the GPIO2 to be controlled
    ledcAttachPin(PIN_LED, CH_LED);
    ledcAttachPin(PIN_MOTOR_VL_EN, CH_MOTOR_VL);
    ledcAttachPin(PIN_MOTOR_VR_EN, CH_MOTOR_VR);
    ledcAttachPin(PIN_MOTOR_HL_EN, CH_MOTOR_HL);
    ledcAttachPin(PIN_MOTOR_HR_EN, CH_MOTOR_HR);

    Serial.println("Inited PWMs");
}

void Movement::drive(int controlFront, int controlSide, int controlTurn) {
    double phi = atan2(controlSide, controlFront);

    int vd = max(controlFront + controlSide, 1023);
    vd -= controlTurn / 2;
    int vphi = controlTurn / 2;

    double s = vd * sin(phi + PI / 4);
    double c = vd * cos(phi + PI / 4);

    int speedVL = s + vphi;
    int speedVR = c - vphi;
    int speedHL = c + vphi;
    int speedHR = s - vphi;

    MOTOR_VL.setSpeed(speedVL);
    MOTOR_VR.setSpeed(speedVR);
    MOTOR_HL.setSpeed(speedHL);
    MOTOR_HR.setSpeed(speedHR);

    // speedVL = speedVL / 1023.0 * USEABLE_UPPER_LIMIT + 1023 - USEABLE_UPPER_LIMIT;
    // speedVR = speedVR / 1023.0 * USEABLE_UPPER_LIMIT + 1023 - USEABLE_UPPER_LIMIT;
    // speedHL = speedHL / 1023.0 * USEABLE_UPPER_LIMIT + 1023 - USEABLE_UPPER_LIMIT;
    // speedHR = speedHR / 1023.0 * USEABLE_UPPER_LIMIT + 1023 - USEABLE_UPPER_LIMIT;

    printf("#######\n");
    printf("%i %i\n", speedVL, speedVR);
    printf("%i %i\n", speedHL, speedHR);
}