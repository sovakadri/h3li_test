#include "gpio.h"
#include "serial.h"
#include "H3LI5331DL_SPI.h"

extern "C" void SystemClock_Config(void);

using namespace INTERFACES;
using namespace UART_DEBUG;
using namespace SENSOR_DRIVER;

int h3li5331dl_spi_example() {
    HAL_Init();
    SystemClock_Config();
    MX_SPI1_Init();
    MX_GPIO_Init();
    MX_USART2_UART_Init();

    println("New run");

    SPI_Interface spi(hspi1);
    Pin H3li_PIN = {H3LI_CS_GPIO_Port, H3LI_CS_Pin};
    HAL_GPIO_WritePin(H3LI_CS_GPIO_Port, H3LI_CS_Pin, GPIO_PIN_SET);

    H3LI5331DL_SPI H3li(spi,H3li_PIN);
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