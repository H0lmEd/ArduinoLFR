#include <PololuQTRSensors.h>
#include <QTRSensors.h> // Sensor Libraries

#include <AFMotor.h> // Motor Library

// "motor" on port 1 of the motorshield:
AF_DCMotor motor(1);   //right wheel
// "motor2" on port 2 of the motorshield:
AF_DCMotor motor2(2); // left wheel

#define NUM_SENSORS     6       // number of sensors used
#define TIMEOUT         2500    // Waits 2500us for sensors

QTRSensorsRC qtrrc((unsigned char[]) {A0,A1,A2,A3,A4,A5}, NUM_SENSORS,                      TIMEOUT, QTR_NO_EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

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
  delay(500);
  int i;
  for (i = 0; i < 250; i++) {
    qtrrcalibrate(QTR_EMITERS_ON);
    delay(20);
  }                 // NEED THIS AND BELOW TO RUN TOGETHER???
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
  
  for (i = 0; i < NUM_SENSORS; i++) {
    Serial.print("Min:\t\tMax:\n");
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print("\t\t");
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.println(" ");
  }
}

unsigned char i;

void loop() {
  
  qtrrc.read(sensorValues, QTR_NO_EMITTER_PIN);
  unsigned int position = qtrrc.readLine(sensorValues);
  
  if (position > 2400 && position < 3000) { //change these vals TEST
    Serial.print("FORWARD");
    motorForward(200);
    motorStop(100);
  } else if (position > 3000) {
    Serial.print("LEFT");
    motorLeft(100);
    motorStop(100);
  } else if (position < 2400) {
    Serial.print("RIGHT");
    motorRight(100);
    motorStop(100);
  } else {
    Serial.print("Error, position out of range: ");
  }
  Serial.println(position);
  delay(250);

/*  legacy code pre-merge
  motorStop(100); //Stop Motor
  motorLeft(100);
  motorStop(100);
  motorRight(100);
  motorStop(100); 
  motorForward(200);
  motorStop(100);
  motorBackward(200);
  motorStop(100);
*/

}
