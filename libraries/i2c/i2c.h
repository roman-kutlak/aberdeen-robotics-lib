#ifndef i2c_h
#define i2c_h

#include <inttypes.h>


class I2C {
public:
    I2C();
	
    void init();
    
    /*! Write information stored in data.
     \param address
     \param reg
     \param data
     */
    void write(uint8_t address, uint8_t reg, uint16_t count, uint8_t *data);
    
    /** Write one byte.
     */
    void write(uint8_t address, uint8_t reg, uint8_t data);
    
    
    uint8_t read(uint8_t address, uint8_t reg, uint16_t count, uint8_t* buffer);

    uint8_t read(uint8_t address, uint8_t reg);
    
    
    // disable copy construction and assignment as we only work with 1 object
private:
    I2C& operator=(I2C from);
    I2C(I2C& from);
};

extern I2C i2c;

#endif
