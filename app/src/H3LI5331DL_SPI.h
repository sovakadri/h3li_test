#pragma once
#include "H3LI5331DL.h"
#include "SPI_Interface.h"
using namespace INTERFACES;

namespace SENSOR_DRIVER{
    
    class H3LI5331DL_SPI: public H3LI5331DL  {
    public:
        H3LI5331DL_SPI(SPI_Interface& spi, Pin CS_Pin);
    private:
      void readInterface(uint8_t address, uint8_t* pData, uint16_t size);
      void writeInterface(uint8_t address, uint8_t* pData, uint16_t size);
      
      Pin CS_Pin;
      SPI_Interface& spi;
    };
}