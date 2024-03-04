/*
 * CCF_R_1000LA_V2.c
 *
 * Created: 2024-02-27 ?�전 10:55:43
 * Author : jace
 */ 

#include <avr/io.h>

#include "inc/board.h"



SysTime_Param	Systime;
Wireless_Param	Fwd;
Wireless_Param	Rev;
System_Param	Sys;

int main(void)
{
	Init_MCU();
	Init_System();

    while (1) 
    {
		if (Sys.Debug_Flag)	
			Command_Check();
		
    }
}

