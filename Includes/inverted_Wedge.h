/*
 * inverted_Wedge.h
 *
 *  Created on: 2018Äê6ÔÂ17ÈÕ
 *      Author: 18379
 */

#ifndef INCLUDES_INVERTED_WEDGE_H_
#define INCLUDES_INVERTED_WEDGE_H_

/*
 * inverted_Wedge_main.h
 *
 * Description:
 *     this program demostrate the control system of Invert-Wedge.
 *
 *
 * Created on: 2018/6/5
 * author: Cyanlin
 *
 *
 */
#include "Includes/tm4cUtil.h"

/* Pin Configurations:
 *    UART:
 *      U0RX:       PA0
 *      U0TX:       PA1
 *      MotorDir    PC7
 *      MotorStep   PC6
 *
 *
 *
 * */



class SysRecord
{

public:
    typedef struct{
        uint8_t motor;
        uint8_t uart;
        uint8_t gyroscope;
    } CheckRecord;


    uint32_t systemClock;
    CheckRecord checkRecord;


public:
    SysRecord() = default;
    SysRecord(uint32_t systemClock_);
    bool sysCheck(uint8_t verbose);
};




#endif /* INCLUDES_INVERTED_WEDGE_H_ */
