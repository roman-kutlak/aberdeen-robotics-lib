
#include "ITG3200.h"
#include <i2c.h>
#include <Arduino.h>

float scale = 0.061037019f;

ITG3200::ITG3200(){
	this->buffer[0] = 0;
	this->buffer[1] = 0;
	this->buffer[2] = 0;
	this->buffer[3] = 0;
	this->buffer[4] = 0;
	this->buffer[5] = 0;
	this->buffer[6] = 0;
	this->buffer[7] = 0;
	
}

void ITG3200::init(){
	i2c.init();
	i2c.write(ITG3200_ADDRESS, ITG3200_REG_PWR_MGM, ITG3200_BIT_PWR_MGM_H_RESET);
	this->setLowPassFilter(ITG3200_LPF_188HZ);
	this->enterNormalMode();
	delay(50);
}

void ITG3200::enterLowPowerMode(){
	i2c.write(ITG3200_ADDRESS, ITG3200_REG_PWR_MGM, ITG3200_BIT_PWR_MGM_CLK_SEL_INTERNAL + ITG3200_BIT_PWR_MGM_SLEEP);
}

void ITG3200::enterNormalMode(){
	i2c.write(ITG3200_ADDRESS, ITG3200_REG_PWR_MGM, ITG3200_BIT_PWR_MGM_CLK_SEL_PLL_XG);
}

void ITG3200::sample(){
	i2c.read(ITG3200_ADDRESS, ITG3200_REG_TEMP_OUT_H, 8, this->buffer);
}

int16_t ITG3200::getX(){
	int16_t result = (((uint16_t)this->buffer[2])<<8) | ((uint16_t) this->buffer[3]);
	return result;
}

int16_t ITG3200::getY(){
	int16_t result = (((uint16_t)this->buffer[4])<<8) | ((uint16_t) this->buffer[5]);
	return result;
}

int16_t ITG3200::getZ(){
	int16_t result = (((uint16_t)this->buffer[6])<<8) | ((uint16_t) this->buffer[7]);
	return result;
}

float ITG3200::getXScaled(){
	return this->getX()*scale;
}

float ITG3200::getYScaled(){
	return this->getY()*scale;
}

float ITG3200::getZScaled(){
	return this->getZ()*scale;
}




float ITG3200::getTemp(){
	int16_t result = (((uint16_t)this->buffer[0])<<8) | ((uint16_t) this->buffer[1]);
	return (result+13200)/280.f;
}

void ITG3200::setLowPassFilterValue(uint8_t lpf){
	if(lpf > ITG3200_LPF_MAX){
		lpf = ITG3200_LPF_MAX;
	}
	lpf = 6-lpf;
	i2c.write(ITG3200_ADDRESS, ITG3200_REG_DLPF_FS, ITG3200_BIT_FS_SEL_FULL_RANGE + lpf);
}

void ITG3200::setLowPassFilter(uint8_t lpf){
	i2c.write(ITG3200_ADDRESS, ITG3200_REG_DLPF_FS, ITG3200_BIT_FS_SEL_FULL_RANGE + lpf);
}




ITG3200 Gyro = ITG3200();