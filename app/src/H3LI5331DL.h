#pragma once
#include <cstdint.h>

// range setting [g] / 2^15 (signed short max number)
// This scales the signed 2 byte long data on the interval
#define FS_100G_MULTIPLIER 100.0f / 32768.0f
#define FS_200G_MULTIPLIER 200.0f / 32768.0f
#define FS_400G_MULTIPLIER 400.0f / 32768.0f

namespace SENSOR_DRIVER{

    struct DataH3li {
        float x, y, z;
    };

    /**
     * Abstract class for H3LI5331DL sensor. It is the parent class
     * for two children classes: H3LI5331DL_I2C and H3LI5331DL_SPI.
     *
     * Publicly they behave the same, but one uses the I2C interface
     * and the other uses the SPI interface.
     */
    class H3LI5331DL {
      public:
        /**
         * Constructor for H3LI5331DL class
         */
        H3LI5331DL();
        
        /**
         * Reads data from the H3LI5331DL sensor using either of the interfaces.
         * @return DataH3li object containing the read data.
         */
        DataH3li read();

        /**
         * Sets the control registers for the h3li sensor.DataH3li
         * @param ctrl_reg1 [7:5]: power mode, [4:3]: data rate, [2:0]: XYZ enable
         * @param ctrl_reg2 [7]: reboot memory, [6:5]: high-pass mode, [4]: Filtered data, [3:2]: HP filter enable, [1:0]: HP cutoff
         * @param ctrl_reg3 [7]: interrupt active, [6]: push-pull/open-drain, [5]: LIR2, [4:3]: I2_CFG, [2]: LIR1, [1:0]: I1_CFG
         * @param ctrl_reg4 [7]: block data update, [6]: big/little endian, [5:4]: range (100g/200g/400g), [0]: 3-wire SPI
         * @param ctrl_reg5 [1:0]: turn-on bits
         */
        void initialize(uint8_t ctrl_reg1, uint8_t ctrl_reg2, uint8_t ctrl_reg3, uint8_t ctrl_reg4, uint8_t ctrl_reg5 );

        /**
         * This function is used to calibrate the sensor. Align the sensor
         * horizontally, then call this function right after initialize().
         * Keep the device horizontal for this part. You can then upload the
         * code without the use of this function, so that it doesn't reset
         * the calibration each time the program starts.
         * @return the initial offset values to be saved.
         */
        DataH3li calibrate();

      protected:
        /**
         * Virtual function to specify reading using the chosen interface.
         * @param address the memory address to start reading at.
         * @param pData storage for the data rea
         * d from the device.
         * @param size the amount of bytes to be read.
         */
        virtual void readInterface(uint8_t address, uint8_t* pData, uint16_t size) = 0;
        
        /**
         * Virtual function to specify reading using the chosen interface.
         * @param address the memory address to start writing at.
         * @param pData storage for the data to be written.
         * @param size the amount of bytes to write.
         */
        virtual void writeInterface(uint8_t address, uint8_t* pData, uint16_t size) = 0;

        float offX, offY, offZ;
    };
}