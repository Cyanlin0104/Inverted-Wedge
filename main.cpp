/*
 * main.cpp
 *
 *  Created on: 2018/5/16
 *      Author: Cyanlin
 */

#include "Includes/tm4cUtil.h"
#include "Includes/basicFunc.h"
#include "Includes/tm4cUart.h"
#include "Includes/tm4cStepperDriver.h"


IOpin stepPin = {GPIO_PORTC_BASE, GPIO_PIN_6};
IOpin dirPin = {GPIO_PORTC_BASE, GPIO_PIN_7};


const int8_t goal = 0;
int8_t angle = 0;
int8_t error_p = 0;
int8_t last_error_p = 0;
int32_t error_d = 0;
int32_t error_i = 0;
int32_t Control_P = 0;
int32_t Control_D = 0;
int32_t Control_I = 0;

const uint32_t Kp = 1500;
const uint32_t Kd = 0;
const uint32_t Ki = 0;



const uint32_t INTERRUPTTIME = 32000; //100ms
volatile int32_t controlfactor = 1;
int32_t controlfactor_ = 1;
#define ABORTCONTROL 300


extern "C"
void stepperMotorInt(void){
/*
 * Des:
 *  Implementing a timmer interrupt function, called each time the timer counts up.
 *
 * Args:
 *  Inputs:
 *      None
 *  Outputs:
 *      None
 *  (Note that this function actually read volatile variable 'PulseWaitingTime')
 */
    static uint32_t sc = SysCtlClockGet();
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    controlfactor_ = controlfactor;

    if(controlfactor < 0){
        controlfactor_ = -controlfactor;
        GPIOPinWrite(dirPin.port, dirPin.pin, dirPin.pin);
    }
    else
        GPIOPinWrite(dirPin.port, dirPin.pin, 0);

    controlfactor_ = controlfactor_ > 9500? 9500:controlfactor_;
    if(!(controlfactor_ < ABORTCONTROL)){
        float d = 6000000.0 / controlfactor_; //  d = 3 * 1000 * 2 / controlfactor
        for(float i = 0; i < INTERRUPTTIME; i = i + d){
           GPIOPinWrite(stepPin.port, stepPin.pin, stepPin.pin);
           SysCtlDelay(sc/controlfactor_);
           GPIOPinWrite(stepPin.port, stepPin.pin, 0);
           SysCtlDelay(sc/controlfactor_);
        }
    }
}



int main(){

/*******************************/
/*          START              */
/*******************************/


// System Clock Setup
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|
                   SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

// Create System Record
    SysRecord SR(SysCtlClockGet());

// UART Setup
    ConfigureUART(SR, 115200);

// Motor Setup
    Motor::motorSetup(SR);
//    Motor::motorTest(SR);

// Gyroscope Setup
    GyroUARTinit(SR, 115200);

// System Check Up
    while(!SR.sysCheck(1));



/**************************
 *     LOOP
 *
 **************************/
// initializing

    Motor::setupTimerAndInt();

while(1){
    getGyroData(SR, angle);
    UARTprintf("angle: %d\n", angle);

    // PID Control
    error_p = goal - angle;
    error_d = error_p - last_error_p;
    error_i = error_i + last_error_p;
    Control_P = error_p * Kp;
    Control_D = error_d * Kd;
    Control_I = error_i * Ki;
    controlfactor = Control_P + Control_D + Control_I;
    last_error_p = error_p;
}


}

