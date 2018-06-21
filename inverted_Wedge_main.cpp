#include "Includes/inverted_Wedge.h"
#include "Includes/tm4cUart.h"

SysRecord::SysRecord(uint32_t systemClock_)
: systemClock(systemClock_),
  checkRecord{0,0,0}
{
}
bool SysRecord::sysCheck(uint8_t verbose){
    auto u = this->checkRecord.uart;
    auto m = this->checkRecord.motor;
    auto g = this->checkRecord.gyroscope;

    if(verbose){
        const char* ss = "System Check Record: \n "
                "uart: %i\n"
                "motor: %i\n"
                "gyroscope: %i\n";

        UARTprintf(ss, u, m, g);
    }
    return(u && m && g);
}
