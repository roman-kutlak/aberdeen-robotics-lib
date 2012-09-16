#include <Wire.h>
#include <i2c.h>
#include <ADXL345.h>


void setup() {
  Serial.begin(9600);
  i2c.init();
  Accel.init();
}

void loop() {
  Accel.sample();
  Serial.print("X: ");
  Serial.print(Accel.getX());
  Serial.print(" Y: ");
  Serial.print(Accel.getY());
  Serial.print(" Z: ");
  Serial.print(Accel.getZ());
  Serial.print("\n");
  
  delay(1000);
}

