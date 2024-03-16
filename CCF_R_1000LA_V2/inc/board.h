#ifndef __BOARD_H__
#define __BOARD_H__


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
	
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU			16000000
#include <util/delay.h>


#include "defines.h"
#include "timer.h"
#include "initial.h"
#include "adc.h"
#include "Castcore_Debug.h"

//#include "common.h"
#include "eeprom.h"
#include "uart.h"
#include "wireless.h"
#include "command.h"




#define Main_SW_VER			0x2C


#define USE_FM				0

extern SysTime_Param		Systime;

#if 0
extern Wireless_Param		Fwd;
extern Wireless_Param		Rev;
extern System_Param			Sys;
extern FM_Param				FM;
#endif

//adc port
#define _ADCPORT_FWD2_AMP	3
#define _ADCPORT_REV2_AMP	4
#define _ADCPORT_FM_		5
#define _ADCPORT_REV_		6
#define _ADCPORT_FWD_		7



typedef enum
{
	SWMODE_RF2,
	SWMODE_RF1,
} SWITCH_MODE;

typedef enum
{
	LED_OFF,
	LED_ON,
} LED_;

	
void setSwitch_FWD1(BOOL bRF1);
void setSwitch_FWD2(BOOL bRF1);
void setSwitch_REV1(BOOL bRF1);
void setSwitch_REV2(BOOL bRF1);

void setLED_FWD(BOOL bLEDOn);
void setLED_REV(BOOL bLEDOn);
void setLED_FM(BOOL bLEDOn);



#endif
