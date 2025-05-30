#pragma once
#include "spi.h"

namespace INTERFACES{
  /**
   * The type and number of any pin. Some examples:
   * PA7 => {GPIOA, 7},
   * PB3 => {GPIOB, 3}.
   */
  struct Pin {
      GPIO_TypeDef* GPIO_Type; 
      uint16_t GPIO_Pin;
  };

  /**
   * This class can be used to communicate with devices using the SPI protocol.
   * In itself it does not include any device specific functionality, 
   * but it can be implemented in hardware specific drivers.
   * 
   * This class cannot take full advantage of the SPI protocol yet, as 
   * the read and write functions cannot operate simultaneously
   * (and so this is more like a half-duplex communication, rather than
   * a real full-duplex one).
   */
  class SPI_Interface {
    public:
      /**
       * Constructor for SPI_Interface class.
       * @param hspi The SPI handler object.
       */
      SPI_Interface(SPI_HandleTypeDef& spi_handle);

      /**
       * Transmits a single message to the SPI device, and reads the device's response.
       * Good for simple byte reads such as device ID. This function does not change
       * the read/write bit, so that has to be done manually (for example reading byte
       * 0x2F has to be transformed into 0xAF ( |= 0x80 )).
       * @param CS_pin The type and number of the Chip Select pin.
       * @param txByte The byte to be transmitted.
       * @return The response of the SPI device to txByte.
       */
      uint8_t transmitResponse(Pin CS_pin, uint8_t txByte);

      /**
       * Reads one or multiple bytes of data from consecutive addresses.
       * @param CS_pin The type and number of the Chip Select pin.
       * @param rxData Data buffer for storing the read data.
       * @param startAddress The starting address for the data read.
       * @param size The number of bytes to be read.
       * @return true if the read is succesful, false otherwise.
       */
      bool read(Pin CS_pin, uint8_t startAddress, uint8_t* rxData, uint16_t size);
      
      /**
       * Writes one or multiple bytes of data to consecutive addresses.
       * @param CS_pin The type and number of the Chip Select pin.
       * @param txData Data buffer containing the data to be written.
       * @param startAddress The starting address for the data write.
       * @param size The number of bytes to be written from txData.
       * @return true if the write is succesful, false otherwise.
       */
      bool write(Pin CS_pin, uint8_t startAddress, uint8_t* txData, uint16_t size);

    private:
      /**
       * Enables the SPI device connected to the given pin.
       * @param CS_pin The tpye and number of the Chip Select pin.
       * @return false if another CS line is already enabled, true otherwise.
       */
      bool enableCS(Pin CS_pin);
      
      /**
       * Disables the currently enabled CS line.
       */
      void disableCS(void);

      SPI_HandleTypeDef spi_handle;
      Pin currentCS;
  };

}