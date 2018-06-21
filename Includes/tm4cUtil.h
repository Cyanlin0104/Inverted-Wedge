/*
 * tm4cUtil.h
 *
 *  Created on: 2018Äê5ÔÂ16ÈÕ
 *      Author: 18379
 */

#ifndef TM4CUTIL_H_
#define TM4CUTIL_H_

#include <stdint.h>
#include <inc/tm4c123gh6pge.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"


typedef struct {
    uint32_t port;
    uint8_t pin;
} IOpin;

#endif /* TM4CUTIL_H_ */
