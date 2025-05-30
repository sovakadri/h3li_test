#include "H3LI5331DL_SPI.h"

namespace SENSOR_DRIVER{
    H3LI5331DL_SPI::H3LI5331DL_SPI(SPI_Interface& spi, Pin CS_Pin) : spi(spi), CS_Pin(CS_Pin) {}

    void H3LI5331DL_SPI:: readInterface(uint8_t address, uint8_t* pData, uint16_t size) {
        spi.read(CS_Pin,address, pData, size);
    }

    void H3LI5331DL_SPI:: writeInterface(uint8_t address, uint8_t* pData, uint16_t size) {
        spi.write(CS_Pin,address, pData, size);
    }
}