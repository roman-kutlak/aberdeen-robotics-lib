#ifndef HMC5883L_H
#define HMC5883L_H

#include <inttypes.h>

#define HMC5883L_ADDRESS	0x1e

#define HMC5883L_REG_CONF_A	0x00
#define HMC5883L_REG_CONF_B	0x01
#define HMC5883L_REG_MODE	0x02
#define HMC5883L_REG_X_H	0x03
#define HMC5883L_REG_X_L	0x04
#define HMC5883L_REG_Z_H	0x05
#define HMC5883L_REG_Z_L	0x06
#define HMC5883L_REG_Y_H	0x07
#define HMC5883L_REG_Y_L	0x08
#define HMC5883L_REG_STAT	0x09
#define HMC5883L_REG_ID_A	0x0a
#define HMC5883L_REG_ID_B	0x0b
#define HMC5883L_REG_ID_C	0x0c




#define HMC5883L_BIT_CONF_A_AVG_MAX	3
#define HMC5883L_BIT_CONF_A_AVG_SHIFT	5

#define HMC5883L_BIT_CONF_A_AVG_1	0x00
#define HMC5883L_BIT_CONF_A_AVG_2	0x20
#define HMC5883L_BIT_CONF_A_AVG_4	0x40
#define HMC5883L_BIT_CONF_A_AVG_8	0x60


#define HMC5883L_BIT_CONF_A_RATE_MAX	6
#define HMC5883L_BIT_CONF_A_RATE_SHIFT	2

#define HMC5883L_BIT_CONF_A_RATE_75		0x00
#define HMC5883L_BIT_CONF_A_RATE_150	0x04
#define HMC5883L_BIT_CONF_A_RATE_300	0x08
#define HMC5883L_BIT_CONF_A_RATE_750	0x0c
#define HMC5883L_BIT_CONF_A_RATE_1500 	0x10
#define HMC5883L_BIT_CONF_A_RATE_3000	0x14
#define HMC5883L_BIT_CONF_A_RATE_7500	0x18

#define HMC5883L_BIT_CONF_A_MEAS_MODE_MASK		0x03
#define HMC5883L_BIT_CONF_A_MEAS_MODE_NORMAL	0x00
#define HMC5883L_BIT_CONF_A_MEAS_MODE_P_BIAS	0x01
#define HMC5883L_BIT_CONF_A_MEAS_MODE_N_BIAS	0x02


//#define HMC5883L_BIT_CONF_B_GAIN_MASK	0xe0
#define HMC5883L_BIT_CONF_B_GAIN_MAX	7
#define HMC5883L_BIT_CONF_B_GAIN_SHIFT	5

#define HMC5883L_BIT_CONF_B_GAIN_1370	0x00
#define HMC5883L_BIT_CONF_B_GAIN_1090	0x20
#define HMC5883L_BIT_CONF_B_GAIN_820	0x40
#define HMC5883L_BIT_CONF_B_GAIN_660	0x60
#define HMC5883L_BIT_CONF_B_GAIN_440	0x80
#define HMC5883L_BIT_CONF_B_GAIN_390	0xa0
#define HMC5883L_BIT_CONF_B_GAIN_330	0xc0
#define HMC5883L_BIT_CONF_B_GAIN_230	0xe0



#define HMC5883L_BIT_MODE_CONT		0x00
#define HMC5883L_BIT_MODE_SINGLE	0x01
#define HMC5883L_BIT_MODE_IDLE		0x02


#define HMC5883L_BIT_STAT_LOCK	0x02
#define HMC5883L_BIT_STAT_RDY	0x01


class HMC5883L{
public:
	HMC5883L();
	void init();
	void enterContinuousMode();;
	void enterIdleMode();
	void singleShotSample();
	
	void setBias(int8_t bias);
	
	void sample();
	
	int16_t getX();
	int16_t getY();
	int16_t getZ();
	
	float getXScaled();
	float getYScaled();
	float getZScaled();
	
	
	void setGain(uint8_t gain);
	void setSampleRate(uint8_t srate);
	void setAverageMode(uint8_t mode);
	
	uint8_t ready();
	
private:
	void updateRegConfA();
	uint8_t confABias;
	uint8_t confASRate;
	uint8_t confAAvg;
	
	uint8_t gainIndex;
	
	uint8_t ssMode;
	uint8_t buffer[6];
	static float gainMap[];
};

extern HMC5883L Compass;



#endif