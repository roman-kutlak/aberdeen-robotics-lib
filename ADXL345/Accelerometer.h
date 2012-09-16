/*
 *  \file Accelerometer.h
 *  Accelerometer
 *
 *  Created by Kutlak Roman on 15/09/2012.
 *  Copyright 2012 Kutlak Roman. All rights reserved.
 *
 */

#ifndef Accelerometer_h 
#define Accelerometer_h

#include <inttypes.h>


#define ADXL345_DEVID            0x0   // Device ID.
#define ADXL345_THRESH_TAP       0x1D  // Threshold for tap.
#define ADXL345_OFSX             0x1E  // X-axis offset.
#define ADXL345_OFSY             0x1F  // Y-axis offset.
#define ADXL345_OFSZ             0x20  // Z-axis offset.
#define ADXL345_DUR              0x21  // Tap duration.
#define ADXL345_LATENT           0x22  // Tap latency.
#define ADXL345_WINDOW           0x23  // Tap window.
#define ADXL345_THRESH_ACT       0x24  // Activity threshold.
#define ADXL345_THRESH_INACT     0x25  // Inactivity threshold.
#define ADXL345_TIME_INACT       0x26  // Inactivity time.
#define ADXL345_ACT_INACT_CTL    0x27  // Axis enable control for activity 
                                       //   and inactivity detection. 
#define ADXL345_THRESH_FF        0x28  // Free-fall threshold.
#define ADXL345_TIME_FF          0x29  // Free-fall time. 
#define ADXL345_TAP_AXES         0x2a  // Axis control for tap/double tap. 
#define ADXL345_ACT_TAP_STATUS   0x2b  // Source of tap/double tap. 
#define ADXL345_BW_RATE          0x2c  // Data rate and power mode control. 
#define ADXL345_POWER_CTL        0x2d  // Power-saving features control. 
#define ADXL345_INT_ENABLE       0x2e  // Interrupt enable control. 
#define ADXL345_INT_MAP          0x2f  // Interrupt mapping control. 
#define ADXL345_INT_SOURCE       0x30  // Source of interrupts. 
#define ADXL345_DATA_FORMAT      0x31  // Data format control. 
#define ADXL345_DATAX0           0x32  // X-Axis Data 0. 
#define ADXL345_DATAX1           0x33  // X-Axis Data 1. 
#define ADXL345_DATAY0           0x34  // Y-Axis Data 0. 
#define ADXL345_DATAY1           0x35  // Y-Axis Data 1. 
#define ADXL345_DATAZ0           0x36  // Z-Axis Data 0. 
#define ADXL345_DATAZ1           0x37  // Z-Axis Data 1. 
#define ADXL345_FIFO_CTL         0x38  // FIFO control. 
#define ADXL345_FIFO_STATUS      0x39  // FIFO status.

#define ADXL345_ADDRESS (0xA6>>1)


#define ADXL345_REG_DATAX0 (0x32)
#define ADXL345_REG_POWER_CTL (0x2D)
#define ADXL345_PWRCTL_MEASURE (1 << 3) //sleep off


class Adxl345
{
public:
  Adxl345();
  
  void init();
  
  void sample();
  
  int16_t getX() { return x_; }
  int16_t getY() { return y_; }
  int16_t getZ() { return z_; }
  
private:
  int16_t x_;
  int16_t y_;
  int16_t z_;
};


extern Adxl345 Accelerometer;
#endif // Accelerometer_h
