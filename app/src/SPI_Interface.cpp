#include "SPI_Interface.h"

namespace INTERFACES{
    SPI_Interface::SPI_Interface(SPI_HandleTypeDef& spi_handle) : spi_handle(spi_handle) {
        currentCS = {0,0};
    }


    bool SPI_Interface::read(Pin CS_pin, uint8_t startAddress, uint8_t* rxData, uint16_t size) {
        uint8_t dummyByte = 0;
        startAddress |= 0x80;
        if(enableCS(CS_pin)){
            HAL_SPI_TransmitReceive(&spi_handle, &startAddress, &dummyByte, 1, HAL_MAX_DELAY);
            for(int i = 0; i < size; i++){
                HAL_SPI_TransmitReceive(&spi_handle, &dummyByte, &rxData[i], 1, HAL_MAX_DELAY);
            }
            disableCS();
            return true;
        }
        return false;
    }


    bool SPI_Interface::write(Pin CS_pin, uint8_t startAddress, uint8_t* txData, uint16_t size) {
        uint8_t dummyByte = 0;
        uint8_t addrToWrite = startAddress & 0x7F;
        if(enableCS(CS_pin)){
            for(int i = 0; i < size; i++){
                HAL_SPI_TransmitReceive(&spi_handle, &addrToWrite, &dummyByte, 1, HAL_MAX_DELAY);
                HAL_SPI_TransmitReceive(&spi_handle, &txData[i], &dummyByte, 1, HAL_MAX_DELAY);
                addrToWrite++;
            }
            disableCS();
            return true;
        }
        return false;
    }


    uint8_t SPI_Interface::transmitResponse(Pin CS_pin, uint8_t txByte){
        uint8_t dummyByte = 0;
        uint8_t rxByte = 0;
        if(enableCS(CS_pin)){
            HAL_SPI_TransmitReceive(&spi_handle, &txByte, &dummyByte, 1, HAL_MAX_DELAY);
            HAL_SPI_TransmitReceive(&spi_handle, &dummyByte, &rxByte, 1, HAL_MAX_DELAY);
            disableCS();
            return rxByte;
        }
        return rxByte;
    }


    bool SPI_Interface::enableCS(Pin CS_pin){
        if(currentCS.GPIO_Pin == 0 && currentCS.GPIO_Type == 0){
            HAL_GPIO_WritePin(CS_pin.GPIO_Type, CS_pin.GPIO_Pin, GPIO_PIN_RESET);
            currentCS = CS_pin;
            return true;
        }
        return false;
    }


    void SPI_Interface::disableCS(){
        HAL_GPIO_WritePin(currentCS.GPIO_Type, currentCS.GPIO_Pin, GPIO_PIN_SET);
        currentCS = {0,0};
    }
}