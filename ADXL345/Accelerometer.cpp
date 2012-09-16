/*
 *  Accelerometer.cpp
 *  Accelerometer
 *
 *  Created by Kutlak Roman on 15/09/2012.
 *  Copyright 2012 Kutlak Roman. All rights reserved.
 *
 */

// SYSTEM INCLUDES

// PROJECT INCLUDES 
#include "Accelerometer.h"
#include <i2c.h>

Adxl345::Adxl345() : x_(0), y_(0), z_(0) {}

void Adxl345::init() {
  i2c.write(ADXL345_ADDRESS, ADXL345_REG_POWER_CTL, ADXL345_PWRCTL_MEASURE);  
}

void Adxl345::sample() {
  uint8_t buffer[20];
  i2c.read(ADXL345_ADDRESS, ADXL345_REG_DATAX0, 6, buffer);
  
  x_ = ((uint16_t)buffer[0]) | (((uint16_t)buffer[1])<<8);
  y_ = ((uint16_t)buffer[2]) | (((uint16_t)buffer[3])<<8);
  z_ = ((uint16_t)buffer[4]) | (((uint16_t)buffer[5])<<8);
}

Adxl345 Accelerometer;