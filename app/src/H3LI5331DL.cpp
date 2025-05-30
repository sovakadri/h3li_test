#include "H3LI5331DL.h"
#include "gpio.h"

namespace SENSOR_DRIVER{

    H3LI5331DL::H3LI5331DL(){
        offX = 0;
        offY = 0;
        offZ = 0;
    }

    DataH3li H3LI5331DL::calibrate(){
        HAL_Delay(10);
        DataH3li zeroData = read();
        offX = zeroData.x;
        offY = zeroData.y;
        offZ = zeroData.z - 1;
        return zeroData;
    }

    DataH3li H3LI5331DL::read(){
        uint8_t out_data [6] = {0};
        readInterface ((0x28 | 0x40), out_data, 6);
        short x = (out_data[1]<<8 | out_data[0]);
        short y = (out_data[3]<<8 | out_data[2]);
        short z = (out_data[5]<<8 | out_data[4]);

        DataH3li data;
        data.x=(float)(x)*FS_100G_MULTIPLIER - offX;
        data.y=(float)(y)*FS_100G_MULTIPLIER - offY;
        data.z=(float)(z)*FS_100G_MULTIPLIER - offZ;
        return data;
    }

    void H3LI5331DL::initialize(uint8_t ctrl_reg1,
                                uint8_t ctrl_reg2,
                                uint8_t ctrl_reg3,
                                uint8_t ctrl_reg4,
                                uint8_t ctrl_reg5 ){
        
        writeInterface(0x20, &ctrl_reg1, 1);
        writeInterface(0x21, &ctrl_reg2, 1);
        writeInterface(0x22, &ctrl_reg3, 1);
        writeInterface(0x23, &ctrl_reg4, 1);
        writeInterface(0x24, &ctrl_reg5, 1);
    }
}