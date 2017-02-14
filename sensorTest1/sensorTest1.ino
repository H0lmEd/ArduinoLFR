#include <PololuQTRSensors.h>
#include <QTRSensors.h>

#define NUM_SENSORS   3     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 us for sensor 


QTRSensorsRC qtrrc((unsigned char[]) {10,11,12},  NUM_SENSORS, 
                          TIMEOUT, QTR_NO_EMITTER_PIN); 
unsigned int sensorValues[NUM_SENSORS];

void setup()
{
  Serial.begin(9600);
  delay(1000);
}

void loop()
{
  qtrrc.read(sensorValues, QTR_NO_EMITTER_PIN);

  
  unsigned char i;
  for (i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print(" ");
  }
  Serial.println(" ");
  delay(250);
}
