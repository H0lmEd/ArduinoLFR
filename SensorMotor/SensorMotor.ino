#include <AFMotor.h>

// "motor" on port 1 of the motorshield:
AF_DCMotor motor(1);   //right wheel

// "motor2" on port 2 of the motorshield:
AF_DCMotor motor2(2); // left wheel

int motorForward(int x) {
  motor.run(FORWARD);
  motor2.run(FORWARD);
  delay(x);
}

int motorBackward(int x) {
  motor.run(BACKWARD);
  motor2.run(BACKWARD);
  delay(x);
}

int motorLeft(int x) {
  motor.run(FORWARD);
  motor2.run(BACKWARD);
  delay(X);
}

int motorRight(int x) {
  motor.run(BACKWARD);
  motor.run(FORWARD);
  delay(x);
}

int motorStop(int x) {
  motor.run(RELEASE);
  motor2.run(RELEASE);
  delay(x);
}

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  // CALIBRATION
  motor.setSpeed(125);     //max speed = 255
  motor2.setSpeed(125);

  motorLeft(500);
  motorStop(100);
  motorRight(900);
  motorStop(100);
  motorLeft(1000);
  motorStop(100);
  motorRight(500);

  motor.setSpeed(200);    
  motor2.setSpeed(200);
}

void loop() {
  motorStop(100); //Stop Motor

  motor.run(FORWARD);      // command motor 1 to go forwards
  motor2.run(BACKWARD);  // command motor 2 to go backwards
  delay(100);


  motor.run(RELEASE);      // command motor 1 to stop
motor2.run(RELEASE);  // command motor 2 to stop
delay(100);

motor.run(BACKWARD);     // command motor 1 to go backwards
motor2.run(FORWARD);  //command motor 2 to go forwards
delay(100);

motor.run(RELEASE);      // command motor 1 to stop
motor2.run(RELEASE);  // command motor 2 to stop
delay(100);

motor.run(FORWARD);      // command motor 1 to go forawrds
motor2.run(FORWARD);  // command motor 2 to go forwards
delay(200);

motor.run(RELEASE);      // command motor 1 to stop
motor2.run(RELEASE);  // command motor 2 to stop
delay(100);

motor.run(BACKWARD);      // command motor 1 to go backwards
motor2.run(BACKWARD);  // command motor 2 to go backwards
delay(200);

motor.run(RELEASE);      // command motor 1 to stop
motor2.run(RELEASE);  // command motor 2 to stop
delay(100);
}
