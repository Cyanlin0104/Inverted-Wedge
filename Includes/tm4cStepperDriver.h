/*
 * tm4cStepperDriver.h
 *
 *  Created on: 2018/5/22
 *      Author: Cyanlin
 */

#ifndef INCLUDES_TM4CSTEPPERDRIVER_H_
#define INCLUDES_TM4CSTEPPERDRIVER_H_

#include "Includes/tm4cUtil.h"
#include "driverlib/pwm.h"
#include "Includes/tm4cUart.h"
#include "inc/hw_types.h"
// for timer interrupt
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "Includes/inverted_Wedge.h"


extern IOpin stepPin;
extern IOpin dirPin;

namespace Motor{

void motorSetup(SysRecord& SR);

void setupTimerAndInt(void);

bool motorTest(SysRecord&);

}


#endif /* INCLUDES_TM4CSTEPPERDRIVER_H_ */
