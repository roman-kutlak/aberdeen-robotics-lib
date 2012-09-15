#include <Wire.h>
#include <i2c.h>
#include <HMC5883L.h>

void setup(){
 Serial.begin(9600);
 Compass.init(); 
 Compass.setGain(4);
 Compass.setSampleRate(7);
}
  
  
  
void loop(){
  Compass.sample();
  Serial.print("X:");  
  Serial.print(Compass.getXScaled());
  Serial.print(" Y:");  
  Serial.print(Compass.getYScaled());
  Serial.print(" Z:");  
  Serial.print(Compass.getZScaled());
  
  Serial.print("\n");
  
  
  delay(500);
  
}
