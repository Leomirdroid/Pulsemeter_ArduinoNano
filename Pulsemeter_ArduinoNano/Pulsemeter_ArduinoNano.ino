#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
const int l = 200;
int data[l];
int dataeval[l-1];
int dataeval2[l-10];
int peaks;
sensors_event_t event;

void setup() {
   Serial.begin(9600);
  Serial.println("Light Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  //use tsl.begin() to default to Wire, 
  //tsl.begin(&Wire2) directs api to use Wire2, etc.
  if(!tsl.begin())
  {
    /* There was a problem detecting the TSL2561 ... check your connections */
    Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
    
  // put your setup code here, to run once:
tsl.setGain(TSL2561_GAIN_16X);
tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);

}

void loop() {
  // put your main code here, to run repeatedly:
/* Get a new sensor event */ 
 
  
  for (int i = 0; i < l ; i++){
  tsl.getEvent(&event);
   data[i] = event.light;
   delay(7);
  } 
   
  /* Display the results (light is measured in lux) */
for (int i = 0; i < l ; i++){
    //Serial.println(data[i]);
  }

for (int i = 0; i < l-1 ; i++){
  
  if (data[i+1] >= data[i]) {
    dataeval[i] = 1;
  }
    else {
      dataeval[i] = 0;
    }
 for (int i = 0; i < l-10 ; i++){
  
  if ((dataeval[i]+dataeval[i+1]+dataeval[i+2]+dataeval[i+3]+dataeval[i+4]+dataeval[i+5]+dataeval[i+6]+dataeval[i+7]+dataeval[i+8]+dataeval[i+9]) > 9) {
    dataeval2[i] = 1;
  }
    else {
      dataeval2[i] = 0;
    } 
 }  
 /*for (int i = 0; i < l ; i++){
    for (int j = 0; j < 15; j++)
    if (dataeval[j]
    peaks = peaks + 1;
  }    */
}
  for (int i = 0; i < l-10 ; i++){
    Serial.print(data[i]);
    Serial.print(" ");
    Serial.print(dataeval[i]*300);
        Serial.print(" ");
    Serial.println(dataeval2[i]*300);
  }

}
