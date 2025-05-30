#pragma once
/*
* File: I2C_Scanner
* Created on: Mar 28, 2020
* Ver: 1.0
* Author:     Khaled Magdy
* -------------------------------------------
* For More Information, Tutorials, etc.
* Visit Website: www.DeepBlueMbedded.com
*
*/
 
#include "stdio.h"
#include "i2c.h"
#include "gpio.h"
#include "usart.h"
 
extern "C" void SystemClock_Config(void);
 
uint8_t Buffer[25] = {0};
uint8_t Space[] = " - ";
uint8_t StartMSG[] = "Starting I2C Scanning: \r\n";
uint8_t EndMSG[] = "Done! \r\n\r\n";
 
// void SystemClock_Config(void);
// static void MX_GPIO_Init(void);
// static void MX_I2C3_Init(void);
// static void MX_USART2_UART_Init(void);

void i2c_detect()
{
    uint8_t i = 0, ret;
 
    SystemClock_Config();
    HAL_Init();
    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART2_UART_Init();
 
    HAL_Delay(1000);
 
    /*-[ I2C Bus Scanning ]-*/
    HAL_UART_Transmit(&huart2, StartMSG, sizeof(StartMSG), 10000);
    for(i=1; i<128; i++)
    {
        ret = HAL_I2C_IsDeviceReady(&hi2c1, (uint16_t)(i<<1), 3, 5);
        if (ret != HAL_OK) /* No ACK Received At That Address */
        {
            HAL_UART_Transmit(&huart2, Space, sizeof(Space), 10000);
        }
        else if(ret == HAL_OK)
        {
            sprintf((char*)Buffer, "0x%X", i);
            HAL_UART_Transmit(&huart2, Buffer, sizeof(Buffer), 10000);
        }
    }
    HAL_UART_Transmit(&huart2, EndMSG, sizeof(EndMSG), 10000);
    /*--[ Scanning Done ]--*/
 
    while (1)
    {
    }
}