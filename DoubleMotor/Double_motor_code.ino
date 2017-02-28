

#include <AFMotor.h>

// "motor" on port 1 of the motorshield:
AF_DCMotor motor(1);  

// "motor2" on port 2 of the motorshield:
AF_DCMotor motor2(2);


void setup() {
Serial.begin(9600);           // set up Serial library at 9600 bps

// set the speed to 150 of 255 of "motor":  
motor.setSpeed(125);    

// set the speed to 150 of 255 of "motor2":
motor2.setSpeed(125);

motor.run(FORWARD);      // command motor 1 to go forwards
motor2.run(BACKWARD);  // command motor 2 to go backwards
delay(500);

motor.run(RELEASE);      // command motor 1 to stop
motor2.run(RELEASE);  // command motor 2 to stop
delay(100);

motor.run(BACKWARD);     // command motor 1 to go backwards
motor2.run(FORWARD);  //command motor 2 to go forwards
delay(900);

motor.run(RELEASE);      // command motor 1 to stop
motor2.run(RELEASE);  // command motor 2 to stop
delay(100);

motor.run(FORWARD);      // command motor 1 to go forwards
motor2.run(BACKWARD);  // command motor 2 to go backwards
delay(1000);

motor.run(RELEASE);      // command motor 1 to stop
motor2.run(RELEASE);  // command motor 2 to stop
delay(100);

motor.run(BACKWARD);     // command motor 1 to go backwards
motor2.run(FORWARD);  //command motor 2 to go forwards
delay(500);

// set the speed to 200 of 255 of "motor":  
motor.setSpeed(200);    

// set the speed to 200 of 255 of "motor2":
motor2.setSpeed(200);
}

void loop() {
  motor.run(RELEASE);      // command motor 1 to stop
motor2.run(RELEASE);  // command motor 2 to stop
delay(100);

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
