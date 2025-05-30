#include "gpio.h"
#include "examples/h3li5331dl_i2c_example.h"

extern "C" void SystemClock_Config(void);

int main() {
    h3li5331dl_i2c_example();
}