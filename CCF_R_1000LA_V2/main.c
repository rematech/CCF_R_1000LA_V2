/*
 * CCF_R_1000LA_V2.c
 *
 * Created: 2024-02-27 ?�전 10:55:43
 * Author : jace
 */ 

#include <avr/io.h>

#include "board.h"



SysTime_Param	Systime;

#if 0
	Wireless_Param	Fwd;
	Wireless_Param	Rev;
	FM_Param		FM;

	System_Param	Sys;
#endif



void timer10msLoop();
void timer100msLoop();
void timer1000msLoop();
int main(void)
{
	Init_MCU();
	Init_System();

	printf("start");
    while (1) 
    {
		timer10msLoop();
		timer100msLoop();
		timer1000msLoop();
		
		//delay_ms(500);
		//printf("1sec: %d\r\n", Systime.Count_10ms);
    }
}

void timer10msLoop()
{
	if(Systime.Flag_10ms)
	{
		ADC_All_Read();

		Wireless_Check();
		FM_Check();


		Systime.Flag_10ms = 0;
	}
}

void timer100msLoop()
{
	if(Systime.Flag_100ms)
	{
		//
		//setLED_FWD(0);

		Systime.Flag_100ms = 0;
	}

}

//uchar ucTemp = 0;
void timer1000msLoop()
{	
	if(Systime.Flag_1000ms)
	{
		//ucTemp++;
		
		//setLED_FWD(ucTemp%2);
		//setLED_REV(ucTemp%2);
		//setLED_FM(ucTemp%2);
		CommandProcess();
		PrintParameter();

		
		//printf("1sec");
		printf("adc: %d %d %d %d %d ", g_Data.readADC.FWD, g_Data.readADC.REV, g_Data.readADC.FM, g_Data.readADC.FWD2_AMP, g_Data.readADC.REV2_AMP);
		Systime.Flag_1000ms = 0;
	}
}


