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
  delay(x);
}

int motorRight(int x) {
  motor.run(BACKWARD);
  motor2.run(FORWARD);
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
  motor.setSpeed(255); //250 is good   
  motor2.setSpeed(255);
  
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
    motorForward(0);
    //motorStop(25);
  } else if (position > 3000) {
    Serial.print("LEFT");
    motorLeft(0);
    //motorStop(25);
  } else if (position < 2400) {
    Serial.print("RIGHT");
    motorRight(0);
    //motorStop(25);
  } else {
    Serial.print("Error, position out of range: ");
    //motorStop(1000);
  }
  Serial.println(position);
  //delay(250);

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
