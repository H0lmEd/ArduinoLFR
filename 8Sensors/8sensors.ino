#include <PololuQTRSensors.h>
#include <QTRSensors.h>

#define NUM_SENSORS   6     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 us for sensor 


QTRSensorsRC qtrrc((unsigned char[]) {A0,A1,A2,A3,A4,A5},  NUM_SENSORS, 
                          TIMEOUT, QTR_NO_EMITTER_PIN); 
unsigned int sensorValues[NUM_SENSORS];

void setup()
{
  Serial.begin(9600);
  delay(500);
  int i;
  for (i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtrrc.calibrate();       // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
  for (i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print("Min:\t\tMax\n");
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print("\t\t");
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.println(" ");
  }
}

void loop()
{
  qtrrc.read(sensorValues, QTR_NO_EMITTER_PIN);
  unsigned int position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON);
  
  unsigned char i;
  for (i = 0; i < NUM_SENSORS; i++) {
    Serial.print(sensorValues[i] * 10 / 1001);
    Serial.print(' ');
  }
  Serial.print("   ");
  Serial.println(position);
  
  delay(250);
}
