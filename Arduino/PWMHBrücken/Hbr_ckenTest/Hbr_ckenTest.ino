#define LED 2

#define MOTOR_VL_EN 23
#define MOTOR_VL_DIR1 18
#define MOTOR_VL_DIR2 19

#define MOTOR_VR_EN 32
#define MOTOR_VR_DIR1 12
#define MOTOR_VR_DIR2 13

#define MOTOR_HL_EN 16
#define MOTOR_HL_DIR1 17
#define MOTOR_HL_DIR2 5

#define MOTOR_HR_EN 4
#define MOTOR_HR_DIR1 2
#define MOTOR_HR_DIR2 15


// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int MotorVLChannel = 1;
const int MotorVRChannel = 2;
const int MotorHLChannel = 3;
const int MotorHRChannel = 4;
const int resolution = 10;//Resolution 8, 10, 12, 15

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

int speeds = 0;
String inString = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);
  pinMode(LED, OUTPUT);
  pinMode(MOTOR_VL_EN, OUTPUT);
  pinMode(MOTOR_VL_DIR1, OUTPUT);
  pinMode(MOTOR_VL_DIR2, OUTPUT);

  pinMode(MOTOR_VR_EN, OUTPUT);
  pinMode(MOTOR_VR_DIR1, OUTPUT);
  pinMode(MOTOR_VR_DIR2, OUTPUT);

  pinMode(MOTOR_HL_EN, OUTPUT);
  pinMode(MOTOR_HL_DIR1, OUTPUT);
  pinMode(MOTOR_HL_DIR2, OUTPUT);

  pinMode(MOTOR_HR_EN, OUTPUT);
  pinMode(MOTOR_HR_DIR1, OUTPUT);
  pinMode(MOTOR_HR_DIR2, OUTPUT);

  digitalWrite(MOTOR_VL_DIR1, HIGH);
  digitalWrite(MOTOR_VL_DIR2, LOW);

  digitalWrite(MOTOR_VR_DIR1, HIGH);
  digitalWrite(MOTOR_VR_DIR2, LOW);

  digitalWrite(MOTOR_HL_DIR1, HIGH);
  digitalWrite(MOTOR_HL_DIR2, LOW);

  digitalWrite(MOTOR_HR_DIR1, HIGH);
  digitalWrite(MOTOR_HR_DIR2, LOW);

  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  ledcSetup(MotorVLChannel, freq, resolution);
  ledcSetup(MotorVRChannel, freq, resolution);
  ledcSetup(MotorHLChannel, freq, resolution);
  ledcSetup(MotorHRChannel, freq, resolution);
  
  // attach the channel to the GPIO2 to be controlled
  ledcAttachPin(LED, ledChannel);
  ledcAttachPin(MOTOR_VL_EN, MotorVLChannel);
  ledcAttachPin(MOTOR_VR_EN, MotorVRChannel);
  ledcAttachPin(MOTOR_HL_EN, MotorHLChannel);
  ledcAttachPin(MOTOR_HR_EN, MotorHRChannel);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      int a = inString.toInt();
      inString = "";
      if(a > 1024){
        a = 1024;}
      if(a < 0){
        a = 0;
      }
      ledcWrite(ledChannel,a);
      ledcWrite(MotorVLChannel,a);
      
      ledcWrite(MotorVRChannel,a);
      
      ledcWrite(MotorHLChannel,a);
      
      ledcWrite(MotorHRChannel,a);
      
      Serial.print("Motor speed set to: ");
      Serial.println(a);
    }
  }
}
