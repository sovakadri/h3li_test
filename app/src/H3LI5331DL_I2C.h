#pragma once
#include "H3LI5331DL.h"
#include "I2C_Interface.h"
using namespace INTERFACES;
namespace SENSOR_DRIVER{

    class H3LI5331DL_I2C: public H3LI5331DL {
    public:
      H3LI5331DL_I2C(INTERFACES::I2C_Interface& i2c, uint8_t device_address);

    private:
      void readInterface(uint8_t address, uint8_t* pData, uint16_t size);
      void writeInterface(uint8_t address, uint8_t* pData, uint16_t size);
      
      uint8_t device_address;
      INTERFACES::I2C_Interface& i2c;
    };
}