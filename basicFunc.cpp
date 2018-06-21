/*
 * basicFunc.cpp
 *
 *  Created on: 2018Äê5ÔÂ16ÈÕ
 *      author: Cyanlin
 */

#include "Includes/basicFunc.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

void blink(const IOpin& ledPin)
{
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|
                   SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(ledPin.port);
    GPIOPinTypeGPIOOutput(ledPin.port, ledPin.pin);

    while(1){
        GPIOPinWrite(ledPin.port, ledPin.pin, ledPin.pin);
        SysCtlDelay(SysCtlClockGet()/6);
        GPIOPinWrite(ledPin.port, ledPin.pin,  0);
        SysCtlDelay(SysCtlClockGet()/6);
    }
}


void colorWheelingwithPWM(){
    int a = 0;
    int b = 0;
    SysCtlClockSet(SYSCTL_SYSDIV_1|SYSCTL_USE_OSC|SYSCTL_OSC_MAIN|
                   SYSCTL_XTAL_16MHZ);

    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);    // // PWM clock is processor clock /1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinConfigure(GPIO_PF1_M1PWM5);
    GPIOPinConfigure(GPIO_PF2_M1PWM6);
    GPIOPinConfigure(GPIO_PF3_M1PWM7);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, SysCtlClockGet());
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, SysCtlClockGet());


    PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
    PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);
    PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);
    PWMGenEnable(PWM1_BASE, PWM_GEN_2);
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);
    uint32_t sleepTime = SysCtlClockGet() / 200000;
    while(true){
        uint32_t led_light = 65536;
        for(a-0; a < led_light; a++){
            b = led_light - a;
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, a); // PF1 -> M1PWM5, Duty = a
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, b); // PF2 -> M1PWM6, Duty = b
            SysCtlDelay(sleepTime);
        }
        for(a=0; a<led_light; a++){
        b = led_light - a;
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, b);
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, a);
        SysCtlDelay(sleepTime);
        }
        for(a=0;a<led_light;a++){
        b = led_light - a;
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, b);
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, a);

        SysCtlDelay(sleepTime);
        }
        }

}

