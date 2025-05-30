#include "I2C_Interface.h"

namespace INTERFACES{
    I2C_Interface::I2C_Interface(I2C_HandleTypeDef& i2c_handle)
        : i2c_handle(i2c_handle) {}


    bool I2C_Interface::isReady(uint8_t devAddress, uint32_t trials){
        return HAL_I2C_IsDeviceReady(&i2c_handle, devAddress, trials, HAL_MAX_DELAY) == HAL_OK;
    }

    bool I2C_Interface::read(uint8_t devAddress, uint8_t memAddress, uint8_t* buffer, size_t size) {
        if (HAL_I2C_Mem_Read(&i2c_handle, devAddress << 1, memAddress,
                            I2C_MEMADD_SIZE_8BIT, buffer, size,
                            HAL_MAX_DELAY) != HAL_OK) {
            return false;
        }
        return true;
    }

    bool I2C_Interface::write(uint8_t devAddress, uint16_t memAddress,
                                uint8_t* pData,
                                uint16_t size) {
        if( HAL_I2C_Mem_Write(&i2c_handle, devAddress << 1, memAddress,
                            I2C_MEMADD_SIZE_8BIT, pData, size,
                            HAL_MAX_DELAY) != HAL_OK){
            return false;
        }
        return true;
    }
}