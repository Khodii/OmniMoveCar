#define LED 2

#define MOTOR_VR_EN 21
#define MOTOR_VR_DIR1 22
#define MOTOR_VR_DIR2 23


// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int MotorVRChannel = 1;
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
  pinMode(MOTOR_VR_EN, OUTPUT);
  pinMode(MOTOR_VR_DIR1, OUTPUT);
  pinMode(MOTOR_VR_DIR2, OUTPUT);

  digitalWrite(MOTOR_VR_DIR1, HIGH);
  digitalWrite(MOTOR_VR_DIR2, LOW);

  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  ledcSetup(MotorVRChannel, freq, resolution);
  
  // attach the channel to the GPIO2 to be controlled
  ledcAttachPin(LED, ledChannel);
  ledcAttachPin(MOTOR_VR_EN, MotorVRChannel);
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
        digitalWrite(MOTOR_VR_DIR1, HIGH);
        digitalWrite(MOTOR_VR_DIR2, LOW);
        a = 1024;}
      if(a < 0){
        digitalWrite(MOTOR_VR_DIR1, LOW);
        digitalWrite(MOTOR_VR_DIR2, LOW);
        a = 0;
      }
      ledcWrite(ledChannel,a);
      ledcWrite(MotorVRChannel,a);
      Serial.print("Motor speed set to: ");
      Serial.println(a);
    }
  }
}
