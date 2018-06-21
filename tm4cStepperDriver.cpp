/*
 * tm4cStepperDriver.cpp
 * Description:
 *     This Module defined the relative function to Stepper Motor.
 *     Including Setup and Timer Interrupt function.
 *     One thing important is that this module communicating with main loop
 *     through a volatile Variable [PulseWaitingTime].
 *
 *  Created on: 2018/ 05/ 22
 *      Author: Cyanlin
 */

// for timer interrupt
#include "Includes/tm4cStepperDriver.h"
#include "Includes/tm4cUart.h"
#include "driverlib/pwm.h"


namespace Motor{

inline void ok(const char* s){
    UARTprintf("%s, OK\n", s);
}

void motorSetup(SysRecord& SR){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    GPIOPinTypeGPIOOutput(stepPin.port, stepPin.pin);
    GPIOPinTypeGPIOOutput(dirPin.port, dirPin.pin);
    SR.checkRecord.motor = 1;
}

void setupTimerAndInt(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()/15);
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();
    TimerEnable(TIMER0_BASE,TIMER_A);
}


bool motorTest(SysRecord& SR){
    if(!SR.checkRecord.motor)
        motorSetup(SR);

    UARTprintf("Enter Command \'p\', \'n\', \'s\' "
            "(for positve, negative, and stop)");

    uint32_t sc = SR.systemClock;
    auto command = 's';
    for(;;){
        if(UARTCharsAvail(UART0_BASE))
            command = UARTCharGet(UART0_BASE);
        if(command == 'p'){
            GPIOPinWrite(dirPin.port, dirPin.pin, dirPin.pin);
        }
        else if(command == 'n'){
            GPIOPinWrite(dirPin.port, dirPin.pin, 0);
        }

        if(command != 's'){
            GPIOPinWrite(stepPin.port, stepPin.pin, stepPin.pin);
            SysCtlDelay(sc/10);
            GPIOPinWrite(stepPin.port, stepPin.pin, 0);
            SysCtlDelay(sc/10);
        }
        if(command == 'q')
            break;
    }
    return true;
}
}
//StepperDriver::StepperDriver()
//: stepStatus(0)
//{
//}

//StepperDriver::StepperDriver(const IOpin& stepPin, const IOpin& directionPin)
//: stepPin(stepPin),
//  directionPin(directionPin),
//  stepStatus(0)
//{
//    SysCtlPeripheralEnable(stepPin.port);
//    SysCtlPeripheralEnable(directionPin.pin);
//    GPIOPinTypeGPIOOutput(stepPin.port, directionPin.pin);
//}
//
////void StepperDriver::PWMInit(){
////    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);   // PWM clock is processor clock/1
////    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
////    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
////    GPIOPinConfigure(GPIO_PF1_M1PWM5);
////    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN1);
////    PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
////    PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
////    PWMGenEnable(PWM1_BASE, PWM_GEN_2);
////
////}
//void StepperDriver::setPin(const IOpin& stepPin, const IOpin& directionPin){
//    this->stepPin = stepPin;
//    this->directionPin = directionPin;
//    SysCtlPeripheralEnable(stepPin.port);
//    SysCtlPeripheralEnable(directionPin.pin);
//    GPIOPinTypeGPIOOutput(stepPin.port, directionPin.pin);
//
//}
//
////void StepperDriver::rotateSteps(uint16_t steps, bool direction, uint8_t velocity, float keepduring=0.01){
////
////    GPIOPinWrite(this->stepPin.port, this->stepPin.pin, this->stepPin.pin);
////    SysCtlDelay(keepduring);
////    GPIOPinWrite(this->stepPin.port, this->stepPin.pin, 0);
////    SysCtlDeylay()
////}
