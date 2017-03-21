#include <QTRSensors.h> // Sensor Libraries

#include <AFMotor.h> // Motor Library

AF_DCMotor motor(1);            //"motor" on port 1 of the motorshield is the right wheel
AF_DCMotor motor2(2);           //"motor2" on port 2 of the motorshield is the left wheel

#define NUM_SENSORS     6       // Number of sensors used
#define TIMEOUT         2500    // Waits 2500us for sensors

QTRSensorsRC qtrrc((unsigned char[]) {A0,A1,A2,A3,A4,A5}, NUM_SENSORS, TIMEOUT, QTR_NO_EMITTER_PIN); //
unsigned int sensorValues[NUM_SENSORS];                                                              //

int motorForward(int x) {                                       //Set command "motorFoward" for vehicle to travel forward
  motor.setSpeed(255);                                          //Set speed of motor one to maximum   
  motor2.setSpeed(255);                                         //Set speed of motor two to maximum
  motor.run(FORWARD);                                           //Set motor one to forward direction
  motor2.run(FORWARD);                                          //Set motor two to forward direction
  delay(x);                                                     //Delay
}

int motorBackward(int x) {                                      //Set command "motorBackward"
  motor.setSpeed(255);                                          //Set speed of motor one to maximum
  motor2.setSpeed(255);                                         //Set speed of motor two to maximum
  motor.run(BACKWARD);                                          //Set motor one to backward direction
  motor2.run(BACKWARD);                                         //Set motor two to backward direction
  delay(x);                                                     //Delay
}

int motorLeft(int x) {                                          //Set command "motorLeft"
  motor.setSpeed(255);                                          //Set speed of motor one to maximum
  motor2.setSpeed(0);                                           //Set speed of motor two to zero
  motor.run(FORWARD);                                           //Set motor one to forward direction
  delay(x);                                                     //Delay
}

int motorRight(int x) {                                         //Set command "motorRight"
  motor.setSpeed(0);                                            //Set speed of motor one to zero   
  motor2.setSpeed(255);                                         //Set speed of motor two to maximum
  motor2.run(FORWARD);                                          //Set motor two to forward direction
  delay(x);                                                     //Delay
}

int motorStop(int x) {                                          //Set command "motorStop"
  motor.run(RELEASE);                                           //Set motor one to stop
  motor2.run(RELEASE);                                          //Set motor two to stop
  delay(x);                                                     //Delay
}

void setup() {
  Serial.begin(9600);                                           //Set up Serial library at 9600 bps
  delay(500);                                                   //Delay for 500us
  int i;                                                        //Set integer "i"
    
  for (i = 0; i < NUM_SENSORS; i++) {                           //Prints default calibration values from the sensor
    Serial.print("Min:\t\tMax:\n");                             //
    Serial.print(qtrrc.calibratedMinimumOn[i]);                 //
    Serial.print("\t\t");                                       //
    Serial.print(qtrrc.calibratedMaximumOn[i]);                 //
    Serial.println(" ");                                        //
  }
}

unsigned char i;                                                //

void loop() {
  
  qtrrc.read(sensorValues, QTR_NO_EMITTER_PIN);                 //
  unsigned int position = qtrrc.readLine(sensorValues);         //
  
  if (position > 2400 && position < 3000) {                     //If the sensors produce values between 2400 and 3000 it is on the line
    Serial.print("FORWARD");                                    //Print "FORWARD" in the serial monitor to show it's going forwards
    motorForward(50);                                           //Run command "motorFoward" for 50us
    
  } else if (position > 3000) {                                 //If the sensors produce values greater than 3000 it is on the right of the line
    Serial.print("LEFT");                                       //Print "LEFT" in the serial monitor to show it's turning left
    motorLeft(50);                                              //Run command "motorLeft" for 50us
    
  } else if (position < 2400) {                                 //If the sensors produce a value less than 2400 it is on the left of the line
    Serial.print("RIGHT");                                      //Print "RIGHT" in the serial monitor to show it's turning right
    motorRight(50);                                             //Run command "motorRight" for 50us
    
  } else if (position > 5000) {                                 //Used incase the sensors do not give sensible values
    Serial.print("Error, position out of range: ");             //i.e. a cable is not connected correctly, useful to degub
    motorStop(1000);                                            //Run command "motorStop" for 1000us
    
  } else if (position < 0) {                                    //Used incase the sensors do not give sensible values
    Serial.print("Error, position out of range: ");             //i.e. a cable is not connected correctly, useful to degub
    motorStop(1000);                                            //Run command "motorStop" for 1000us
  }
  Serial.println(position);                                     //

}
