#include <Wire.h>
#include <i2c.h>
#include <ITG3200.h>

void setup(){
 Serial.begin(9600);
 Gyro.init(); 
}
  
  
  
void loop(){
  Gyro.sample();
  Serial.print("X:");  
  Serial.print(Gyro.getXScaled());
  Serial.print(" Y:");  
  Serial.print(Gyro.getYScaled());
  Serial.print(" Z:");  
  Serial.print(Gyro.getZScaled());
  Serial.print(" Temp:");  
  Serial.print(Gyro.getTemp());
  Serial.print("\n");
  
  
  delay(500);
  
}
