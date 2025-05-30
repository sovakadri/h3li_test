#include "H3LI5331DL_I2C.h"

namespace SENSOR_DRIVER{
    H3LI5331DL_I2C::H3LI5331DL_I2C(INTERFACES::I2C_Interface& i2c, uint8_t device_address) : i2c(i2c), device_address(device_address) {}

    void H3LI5331DL_I2C:: readInterface(uint8_t address, uint8_t* pData, uint16_t size) {
        i2c.read(device_address,address, pData, size);
    }

    void H3LI5331DL_I2C:: writeInterface(uint8_t address, uint8_t* pData, uint16_t size) {
        i2c.write(device_address,address, pData, size);
    }
}