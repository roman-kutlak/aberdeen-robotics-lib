#include "HMC5883L.h"
#include <i2c.h>
#include <Arduino.h>

float HMC5883L::gainMap[] = {4.35f,3.03f,2.56f,2.27f,1.52f,1.22f,0.92f,0.73f};

HMC5883L::HMC5883L(){
	this->buffer[0] = 0;
	this->buffer[1] = 0;
	this->buffer[2] = 0;
	this->buffer[3] = 0;
	this->buffer[4] = 0;
	this->buffer[5] = 0;
	
	this->confABias = 0;
	this->confASRate = 0;
	this->confAAvg = 0;
	this->ssMode = 0;
	this->gainIndex = 0;
}

void HMC5883L::init(){
	i2c.init();
	this->setGain(3);
	this->enterContinuousMode();
	
}

void HMC5883L::enterContinuousMode(){
	i2c.write(HMC5883L_ADDRESS, HMC5883L_REG_MODE, HMC5883L_BIT_MODE_CONT);
}

void HMC5883L::enterIdleMode(){
	i2c.write(HMC5883L_ADDRESS, HMC5883L_REG_MODE, HMC5883L_BIT_MODE_IDLE);
}

void HMC5883L::singleShotSample(){
	i2c.write(HMC5883L_ADDRESS, HMC5883L_REG_MODE, HMC5883L_BIT_MODE_SINGLE);
	delay(1);
	while(!this->ready()){
		delay(1);
	}
	this->sample();
}

void HMC5883L::setBias(int8_t bias){
	if(bias){
		if(bias>0){
			bias = HMC5883L_BIT_CONF_A_MEAS_MODE_P_BIAS;
		}else{
			bias = HMC5883L_BIT_CONF_A_MEAS_MODE_N_BIAS;
		}
	}else{
		bias = HMC5883L_BIT_CONF_A_MEAS_MODE_NORMAL;
	}
	this->confABias = bias;
	this->updateRegConfA();
	
}

void HMC5883L::sample(){
	i2c.read(HMC5883L_ADDRESS, HMC5883L_REG_X_H, 6, this->buffer);
}

int16_t HMC5883L::getX(){
	int16_t result = (((uint16_t)this->buffer[0])<<8) | ((uint16_t) this->buffer[1]);
	return result;
}

int16_t HMC5883L::getY(){
	int16_t result = (((uint16_t)this->buffer[4])<<8) | ((uint16_t) this->buffer[5]);
	return result;
}

int16_t HMC5883L::getZ(){
	int16_t result = (((uint16_t)this->buffer[2])<<8) | ((uint16_t) this->buffer[3]);
	return result;
}

float HMC5883L::getXScaled(){
	float f = getX() * this->gainMap[this->gainIndex];
	return f;
}


float HMC5883L::getYScaled(){
	float f = getY() * this->gainMap[this->gainIndex];
	return f;
}


float HMC5883L::getZScaled(){
	float f = getZ() * this->gainMap[this->gainIndex];
	return f;
}




void HMC5883L::setGain(uint8_t gain){
	if(gain > HMC5883L_BIT_CONF_B_GAIN_MAX){
		gain = HMC5883L_BIT_CONF_B_GAIN_MAX;
	}
	
	this->gainIndex = gain;
	gain = (HMC5883L_BIT_CONF_B_GAIN_MAX-gain)<<HMC5883L_BIT_CONF_B_GAIN_SHIFT;
	i2c.write(HMC5883L_ADDRESS, HMC5883L_REG_CONF_B, gain);

}

void HMC5883L::setSampleRate(uint8_t srate){
	if(srate > HMC5883L_BIT_CONF_A_RATE_MAX){
		srate = HMC5883L_BIT_CONF_A_RATE_MAX;
	}
	this->confASRate = srate<<HMC5883L_BIT_CONF_A_RATE_SHIFT;
	this->updateRegConfA();
}

void HMC5883L::setAverageMode(uint8_t mode){
	if(mode > HMC5883L_BIT_CONF_A_AVG_MAX){
		mode = HMC5883L_BIT_CONF_A_AVG_MAX;
	}
	this->confAAvg = mode<<HMC5883L_BIT_CONF_A_AVG_SHIFT;
	this->updateRegConfA();
}

void HMC5883L::updateRegConfA(){
	i2c.write(HMC5883L_ADDRESS, HMC5883L_REG_CONF_A, this->confABias + this->confASRate + this->confAAvg);
}

uint8_t HMC5883L::ready(){
	uint8_t result = i2c.read(HMC5883L_ADDRESS, HMC5883L_REG_STAT);
	
	return result&HMC5883L_BIT_STAT_RDY;
}

HMC5883L Compass = HMC5883L();
