#pragma once
#include "i2c.h"

namespace INTERFACES{
  class I2C_Interface{
    public:
      /**
       * Constructor for I2C_Interface
       * @param i2c_handle the i2c handle object
       * @param device_address the i2c address of the device
       */
      I2C_Interface(I2C_HandleTypeDef& i2c_handle);

      /**
       * Checks if the i2c device is ready for communication
       * @param trials the number of attempts to be made when trying
       *        to establish communication with the device
       * @return true if the device is ready for communication, false otherwise
       */
      bool isReady(uint8_t devAddress, uint32_t trials);

      /**
       * Reads one or more bytes from the i2c device
       * @param devAddress the i2c device address
       * @param memAddress internal memory address
       * @param buffer storage for the data read from the device
       * @param size the number of bytes to read from the device
       * @return true if the write is succesful, false otherwise
       */
      bool read(uint8_t devAddress, uint8_t memAddress, uint8_t* buffer, size_t size);

      /**
       * Writes one or more bytes to the i2c device
       * @param devAddress the i2c device address
       * @param memAddress internal memory address
       * @param pData pointer to data buffer
       * @param size the number of bytes to write to the device
       * @return true if the write is succesful, false otherwise
       */
      bool write(uint8_t devAddress, uint16_t memAddress, uint8_t* pData, uint16_t size);

    private:
      I2C_HandleTypeDef& i2c_handle;
  };
}