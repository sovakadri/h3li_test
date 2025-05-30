#include "gpio.h"
#include "serial.h"
#include "H3LI5331DL_I2C.h"

extern "C" void SystemClock_Config(void);

using namespace INTERFACES;
using namespace UART_DEBUG;
using namespace SENSOR_DRIVER;

int h3li5331dl_i2c_example() {
    HAL_Init();
    SystemClock_Config();
    MX_I2C1_Init();
    MX_GPIO_Init();
    MX_USART2_UART_Init();

    println("New run");

    I2C_Interface i2c(hi2c1);

    H3LI5331DL_I2C H3li(i2c, 0b0011000);
    H3li.initialize(0b00101111,
                    0b00000000,
                    0b00000000,
                    0b10000000,
                    0b00000000);
    
    DataH3li data;

    while (true) {
        data = H3li.read();
        print("x = ");print(data.x);
        print(" y = ");print(data.y);
        print(" z = ");println(data.z);

        HAL_Delay(100);
    }

}