#ifndef itg3200_h
#define itg3200_h

#include <inttypes.h>

#define ITG3200_ADDRESS 0x68

#define ITG3200_REG_WHO_AM_I 	0x00
#define ITG3200_REG_SMPLRT_DIV 	0x15
#define ITG3200_REG_DLPF_FS 	0x16
#define ITG3200_REG_INT_CFG 	0x17
#define ITG3200_REG_INT_STATUS 	0x1a
#define ITG3200_REG_TEMP_OUT_H 	0x1b
#define ITG3200_REG_TEMP_OUT_L 	0x1c

#define ITG3200_REG_GYRO_XOUT_H 0x1d
#define ITG3200_REG_GYRO_XOUT_L 0x1e
#define ITG3200_REG_GYRO_YOUT_H 0x1f
#define ITG3200_REG_GYRO_YOUT_L 0x20
#define ITG3200_REG_GYRO_ZOUT_H 0x21
#define ITG3200_REG_GYRO_ZOUT_L 0x22

#define ITG3200_REG_PWR_MGM 	0x3e

#define ITG3200_BIT_FS_SEL_FULL_RANGE 0x18


#define ITG3200_LPF_MAX		0x06


#define ITG3200_LPF_256HZ 	0x00
#define ITG3200_LPF_188HZ 	0x01
#define ITG3200_LPF_98HZ 	0x02
#define ITG3200_LPF_42HZ 	0x03
#define ITG3200_LPF_20HZ 	0x04
#define ITG3200_LPF_10HZ 	0x05
#define ITG3200_LPF_5HZ 	0x06

#define ITG3200_BIT_PWR_MGM_H_RESET	0x80
#define ITG3200_BIT_PWR_MGM_SLEEP	0x40

#define ITG3200_BIT_PWR_MGM_STBY_XG	0x20
#define ITG3200_BIT_PWR_MGM_STBY_YG	0x10
#define ITG3200_BIT_PWR_MGM_STBY_ZG	0x08

#define ITG3200_BIT_PWR_MGM_CLK_SEL_INTERNAL	0
#define ITG3200_BIT_PWR_MGM_CLK_SEL_PLL_XG		1
#define ITG3200_BIT_PWR_MGM_CLK_SEL_PLL_YG		2
#define ITG3200_BIT_PWR_MGM_CLK_SEL_PLL_ZG		3
#define ITG3200_BIT_PWR_MGM_CLK_SEL_PLL_EXT_32K	4
#define ITG3200_BIT_PWR_MGM_CLK_SEL_PLL_EXT_19M	5


class ITG3200{
public:
	ITG3200();
	void init();
	void enterLowPowerMode();
	void enterNormalMode();
	void sample();
	
	int16_t getX();
	int16_t getY();
	int16_t getZ();
	
	float getXScaled();
	float getYScaled();
	float getZScaled();
	
	float getTemp();
	
	void setLowPassFilterValue(uint8_t lpf);
private:
	void setLowPassFilter(uint8_t lpf);
	uint8_t buffer[8];
};

extern ITG3200 Gyro;

#endif