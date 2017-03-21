// If fails, check print table. Ensure all are positive. Then check
// base speed (l11), maybe lower it, if not check setting the left
// and right motor speeds (l82), one goes negative and one pos, if
// the speeds printed are negtive/base val(100)/0 then change sign

#include <QTRSensors.h> // Sensor Libraries
#include <AFMotor.h>

#define Kp  0.2 //change these two depending on weight, kd 5x kp
#define Kd  4
#define rightMaxSpeed   250 //255?
#define leftMaxSpeed    250
#define rightBaseSpeed  200 // maybe lower this
#define leftBaseSpeed   200
#define NUM_SENSORS 6
#define TIMEOUT     2500 //wait 2500us for sensors

//#include <PololuQTRSensors.h> needed?

// "motor" on port 1 of the motorshield:
AF_DCMotor motor(1);   //right wheel
// "motor2" on port 2 of the motorshield:
AF_DCMotor motor2(2); // left wheel

QTRSensorsRC qtrrc((unsigned char[]) {A0,A1,A2,A3,A4,A5}, NUM_SENSORS,                      TIMEOUT, QTR_NO_EMITTER_PIN);

unsigned int sensorValues[NUM_SENSORS];

int motorForward(int x) { // set arg as motor speed
  motor.setSpeed(x);
  motor2.setSpeed(x);
  //motor.run(FORWARD);
  //motor2.run(FORWARD);
}

int motorBackward(int x) {
  motor.run(BACKWARD);
  motor2.run(BACKWARD);
  delay(x);
}

int motorLeft(int x) {
  motor2.setSpeed(x);
  //motor.run(FORWARD);
  //motor2.run(BACKWARD);
}

int motorRight(int x) {
  motor.setSpeed(x);
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
  //motor.setSpeed(250);    
  //motor2.setSpeed(250);
  

}

unsigned char i;
int lastError = 0;

void loop() {
  //motor.setSpeed(150);
  //motor2.setSpeed(150);
  unsigned int sensors[6];
  qtrrc.read(sensors, QTR_NO_EMITTER_PIN);
  unsigned int position = qtrrc.readLine(sensors);
  int error = position - 2500; //2000? 2500?

  int motorSpeed = Kp * error + Kd * (error - lastError);
  lastError = error;

  int rightMotorSpeed = rightBaseSpeed + motorSpeed; //poss change - and + here ERROR PROBABLY HERE
  int leftMotorSpeed = leftBaseSpeed - motorSpeed;
  
  if (rightMotorSpeed > rightMaxSpeed ) rightMotorSpeed = rightMaxSpeed; //stops motor going beyond max speed
  if (leftMotorSpeed > leftMaxSpeed ) leftMotorSpeed = leftMaxSpeed;
  if (rightMotorSpeed < 0) rightMotorSpeed = 0; //keep speed +ve
  if (leftMotorSpeed < 0) leftMotorSpeed = 0;
  
  //motorSpeed = 150;
  Serial.println("Motor\tright\tleft\terror\tkp\tposition");
  Serial.print(motorSpeed);
  Serial.print("\t");
  Serial.print(rightMotorSpeed);
  Serial.print("\t");
  Serial.print(leftMotorSpeed);
  Serial.print("\t");
  Serial.print(error);
  Serial.print("\t");
  Serial.print(Kp);
  Serial.print("\t");
  Serial.println(position);
  
  motor.setSpeed(rightMotorSpeed);
  motor2.setSpeed(leftMotorSpeed);
  motor.run(FORWARD);
  motor2.run(FORWARD);
}
