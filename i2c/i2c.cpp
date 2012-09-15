#include <Wire.h>
#include "i2c.h"


I2C::I2C() {
    init();
}

void I2C::init(){
	Wire.begin();
}

void I2C::write(uint8_t address, uint8_t reg, uint8_t data){
	write(address, reg, 1, &data);
}

void I2C::write(uint8_t address, uint8_t reg, uint16_t count, uint8_t *data){
  Wire.beginTransmission(address);
  Wire.write(reg);

  // Connect to device and send byte
  for(uint16_t i = 0; i < count; ++i) {
    Wire.write(data[i]); // low byte
  }
  
  Wire.endTransmission();
}

uint8_t I2C::read(uint8_t address, uint8_t reg,
                  uint16_t count, uint8_t* buffer) {
 // Send input register address
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.endTransmission();

  // Connect to device and request bytes
  //Wire.beginTransmission(address);
  Wire.requestFrom(address, count);
  uint16_t i = 0;
  while(Wire.available() && i < count) { // slave may send less than requested 
    uint8_t c = Wire.read();
    buffer[i] = c;
    ++i;
  }
  
  Wire.endTransmission();
  return i; //the number of bytes actually read
}


uint8_t I2C::read(uint8_t address, uint8_t reg) {
	uint8_t result = 0;
	read(address, reg, 1, &result);
	return result;
}

I2C i2c;
