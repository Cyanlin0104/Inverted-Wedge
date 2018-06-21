/*
 * tm4cUart.h
 *
 *  Created on: 2018Äê5ÔÂ21ÈÕ
 *      Author: 18379
 */

#ifndef INCLUDES_TM4CUART_H_
#define INCLUDES_TM4CUART_H_

#include "tm4cUtil.h"
#include "driverlib/uart.h"
#include "driverlib/fpu.h"
#include "driverlib/pin_map.h"
#include "utils/uartstdio.h"
/***************************/

#include "Includes/inverted_Wedge.h"


void ConfigureUART(SysRecord& SR, uint32_t ui32Baud);

void GyroUARTinit(SysRecord& SR, uint32_t GyroBaud=115200, uint32_t defaultSysBaud=115200);

void getGyroData(SysRecord& SR, int8_t& angle, uint32_t defaultSysBaud=115200, uint32_t defaultGyroBaud=115200);

#endif /* INCLUDES_TM4CUART_H_ */
