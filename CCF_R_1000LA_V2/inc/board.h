#ifndef __BOARD_H__
#define __BOARD_H__


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdarg.h>

#include <avr/io.h>
#include <avr/interrupt.h>


#include "defines.h"
#include "timer.h"
#include "initial.h"
#include "adc.h"
#include "Castcore_Debug.h"

#include "common.h"
#include "eeprom.h"
#include "uart.h"
#include "wireless.h"
#include "command.h"




#define Main_SW_VER			0x2C


#define USE_FM				0



extern SysTime_Param		Systime;
extern Wireless_Param		Fwd;
extern Wireless_Param		Rev;
extern System_Param			Sys;
extern FM_Param				FM;





#endif
