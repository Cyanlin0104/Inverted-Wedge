/*
 * tm4cUart.cpp
 *
 *  Created on: 2018Äê5ÔÂ21ÈÕ
 *  Description:
 *      Pin:
 *
 *      Author: 18379
 */

#include "Includes/tm4cUart.h"

inline void ok(const char* s){
    UARTprintf("%s, OK\n", s);
}
void ConfigureUART(SysRecord& SR, uint32_t ui32Baud){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); //enable PORTA
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0); //enable UART0
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    // make PA0,PA1 UART Pin
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    // using UART0, baud rate 115200, let 16MHZ internal quartz crystal
    // be the source clock
    UARTStdioConfig(0, ui32Baud, 16e6);
    SR.checkRecord.uart = 1;
}

void GyroUARTinit(SysRecord& SR, uint32_t GyroBaud, uint32_t defaultSysBaud){
    if(!SR.checkRecord.uart)
        ConfigureUART(SR, defaultSysBaud);
    // Configure Gyro UART

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD); //enable PORTA
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2); //enable UART2
    GPIOPinConfigure(GPIO_PD6_U2RX);
    GPIOPinConfigure(GPIO_PD7_U2TX);

    GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6|GPIO_PIN_7);
    UARTClockSourceSet(UART2_BASE, UART_CLOCK_PIOSC);

//    UARTStdioConfig(2, GyroBaud, 16e6);
    UARTConfigSetExpClk(UART2_BASE, 16e6, GyroBaud,
    (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
    UART_CONFIG_PAR_NONE));
    SR.checkRecord.gyroscope = 1;

}


void getGyroData(SysRecord& SR, int8_t & angle, uint32_t defaultSysBaud, uint32_t defaultGyroBaud){
    if(!SR.checkRecord.uart)
        ConfigureUART(SR, defaultSysBaud);
    if(!SR.checkRecord.gyroscope)
        GyroUARTinit(SR, defaultGyroBaud, defaultSysBaud);
    // read data from U2Rx
    if(UARTCharsAvail(UART2_BASE)){

        angle = UARTCharGet(UART2_BASE);
        angle = angle - 87;
    }
}
