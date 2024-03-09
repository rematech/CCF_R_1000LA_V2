/*
 * CCF_R_1000LA_V2.c
 *
 * Created: 2024-02-27 ?�전 10:55:43
 * Author : jace
 */ 

#include <avr/io.h>

#include "board.h"



SysTime_Param	Systime;

Wireless_Param	Fwd;
Wireless_Param	Rev;
FM_Param		FM;

System_Param	Sys;

int main(void)
{
	Init_MCU();
	Init_System();

    while (1) 
    {
		if (Sys.Debug_Flag)	
			Command_Check();

		
		///////////////////////////////////////////
		if(Systime.Flag_10ms)
		{
			AGC_All_Read();

			if ((!Fwd.Debug_Det_Lvl_En) && (!Rev.Debug_Det_Lvl_En)
					&& (!Fwd.Debug_Agc_Out_En) && (!Rev.Debug_Agc_Out_En))
			{
				Wireless_Check();
				Wireless_AGC_Control();
			}

			if ((FM_RUN_EN) && (!FM.Debug_Att_En))	
				FM_AGC_Control();


			Systime.Flag_10ms = 0;
		}

		///////////////////////////////////////////
		if(Systime.Flag_1000ms)
		{
			if (Sys.Debug_Dsp_En)
				Agc_Display();

			Systime.Flag_1000ms = 0;
		}


    }
}

