#include "board.h"

void USART1_RXC_interrupt(void);
ISR(USART0_RX_vect)
{
	USART1_RXC_interrupt();
}

//--------------------[ Uart Function ]-------------------------------------
//#pragma vector = USART1_RXC_vect
void USART1_RXC_interrupt(void)
{
	uchar temp;
//	CLI;

	temp = UDR1;

	if ((temp == 'A') || (temp == 'a'))	Sys.Debug_Flag |= DEBUG_FWD_DET_LVL_FLAG;
	if ((temp == 'B') || (temp == 'b'))	Sys.Debug_Flag |= DEBUG_REV_DET_LVL_FLAG;
	if ((temp == 'J') || (temp == 'j'))	Sys.Debug_Flag |= DEBUG_FWD_AGC_DET_FLAG;
	if ((temp == 'K') || (temp == 'k'))	Sys.Debug_Flag |= DEBUG_REV_AGC_DET_FLAG;
	if ((temp == 'L') || (temp == 'l'))	Sys.Debug_Flag |= DEBUG_FWD_AGC_OUT_FLAG;
	if ((temp == 'M') || (temp == 'm'))	Sys.Debug_Flag |= DEBUG_REV_AGC_OUT_FLAG;
	//if ((temp == 'N') || (temp == 'n'))	Sys.Debug_Flag |= DEBUG_FM_ATT_FLAG;
	if ((temp == 'U') || (temp == 'u'))	Sys.Debug_Flag |= DEBUG_UP_FLAG;
	if ((temp == 'D') || (temp == 'd'))	Sys.Debug_Flag |= DEBUG_DOWN_FLAG;
	if ((temp == 'V') || (temp == 'v'))	Sys.Debug_Flag |= DEBUG_ALL_ATT_0dB_FLAG;
	if ((temp == 'W') || (temp == 'w'))	Sys.Debug_Flag |= DEBUG_ALL_ATT_10dB_FLAG;
	if ((temp == 'X') || (temp == 'x'))	Sys.Debug_Flag |= DEBUG_PATH_OPEN_FLAG;
	if ((temp == 'C') || (temp == 'c'))	Sys.Debug_Flag |= DEBUG_MAX_UNLOCK_CNT_FLAG;
	if ((temp == 'P') || (temp == 'p'))	Sys.Debug_Flag |= DEBUG_DSP_START_FLAG;
	if ((temp == 'S') || (temp == 's'))	Sys.Debug_Flag |= DEBUG_DSP_PAUSE_FLAG;
	if ((temp == 'Q') || (temp == 'q'))	Sys.Debug_Flag |= DEBUG_CLEAR_FLAG;
	if ((temp == 'I') || (temp == 'i'))	Sys.Debug_Flag |= DEBUG_INIT_FLAG;
	if ((temp == 'H') || (temp == 'h'))	Sys.Debug_Flag |= DEBUG_HELP_FLAG;

//	SEI;
}

void Command_Check(void)
{
	if (Sys.Debug_Flag & DEBUG_FWD_DET_LVL_FLAG)	Debug_Forward_Det_Level();
	if (Sys.Debug_Flag & DEBUG_REV_DET_LVL_FLAG)	Debug_Reverse_Det_Level();

	if (Sys.Debug_Flag & DEBUG_FWD_AGC_DET_FLAG)	Debug_Forward_Agc_Det();
	if (Sys.Debug_Flag & DEBUG_REV_AGC_DET_FLAG)	Debug_Reverse_Agc_Det();

	if (Sys.Debug_Flag & DEBUG_FWD_AGC_OUT_FLAG)	Debug_Forward_Agc_Out();
	if (Sys.Debug_Flag & DEBUG_REV_AGC_OUT_FLAG)	Debug_Reverse_Agc_Out();


	if (Sys.Debug_Flag & DEBUG_UP_FLAG)
	{
		if (Fwd.Debug_Det_Lvl_En)			Debug_Fwd_Det_Level_UpDown(1);
		if (Rev.Debug_Det_Lvl_En)			Debug_Rev_Det_Level_UpDown(1);
		if (Fwd.Debug_Agc_Det_En)			Debug_Fwd_Agc_Det_UpDown(1);
		if (Rev.Debug_Agc_Det_En)			Debug_Rev_Agc_Det_UpDown(1);
		if (Fwd.Debug_Agc_Out_En)			Debug_Fwd_Agc_Out_UpDown(1);
		if (Rev.Debug_Agc_Out_En)			Debug_Rev_Agc_Out_UpDown(1);
		if (Sys.Debug_Max_Unlock_Cnt_En)	Debug_Max_Unlock_Cnt_UpDown(1);

		Sys.Debug_Flag &= ~DEBUG_UP_FLAG;
	}

	if (Sys.Debug_Flag & DEBUG_DOWN_FLAG)
	{
		if (Fwd.Debug_Det_Lvl_En)			Debug_Fwd_Det_Level_UpDown(0);
		if (Rev.Debug_Det_Lvl_En)			Debug_Rev_Det_Level_UpDown(0);
		if (Fwd.Debug_Agc_Det_En)			Debug_Fwd_Agc_Det_UpDown(0);
		if (Rev.Debug_Agc_Det_En)			Debug_Rev_Agc_Det_UpDown(0);
		if (Fwd.Debug_Agc_Out_En)			Debug_Fwd_Agc_Out_UpDown(0);
		if (Rev.Debug_Agc_Out_En)			Debug_Rev_Agc_Out_UpDown(0);
		if (Sys.Debug_Max_Unlock_Cnt_En)	Debug_Max_Unlock_Cnt_UpDown(0);

		Sys.Debug_Flag &= ~DEBUG_DOWN_FLAG;
	}

	if (Sys.Debug_Flag & DEBUG_ALL_ATT_0dB_FLAG)
	{
		Debug_All_Att(0);
		Sys.Debug_Flag &= ~DEBUG_ALL_ATT_0dB_FLAG;
	}

	if (Sys.Debug_Flag & DEBUG_ALL_ATT_10dB_FLAG)
	{
		Debug_All_Att(DEBUG_ALL_ATT_VALUE);
		Sys.Debug_Flag &= ~DEBUG_ALL_ATT_10dB_FLAG;
	}

	if (Sys.Debug_Flag & DEBUG_PATH_OPEN_FLAG)
	{
		Debug_Path_Open();
		Sys.Debug_Flag &= ~DEBUG_PATH_OPEN_FLAG;
	}

	if (Sys.Debug_Flag & DEBUG_MAX_UNLOCK_CNT_FLAG)
	{
		Sys.Debug_Max_Unlock_Cnt_En = true;
		printf("\n\n\rDebug>> Max Unlock Count Value = %d0 msec\n\r", Sys.Max_Unlock_Cnt);
		Sys.Debug_Flag &= ~DEBUG_MAX_UNLOCK_CNT_FLAG;
	}

	if (Sys.Debug_Flag & DEBUG_DSP_START_FLAG)	Debug_Display(1);
	if (Sys.Debug_Flag & DEBUG_DSP_PAUSE_FLAG)	Debug_Display(0);

	if (Sys.Debug_Flag & DEBUG_CLEAR_FLAG)		Debug_Clear();
	if (Sys.Debug_Flag & DEBUG_INIT_FLAG)		Factory_Init();
	if (Sys.Debug_Flag & DEBUG_HELP_FLAG)		Debug_Help_Dsp();
}


void Debug_Forward_Det_Level(void)
{
	printf("\n\n\rDebug>> Forward Detect Level Control\n\r");

	Fwd.Debug_Det_Lvl_En = true;
	Rev.Debug_Det_Lvl_En = false;

	Fwd.Debug_Agc_Det_En = false;
	Rev.Debug_Agc_Det_En = false;

	Fwd.Debug_Agc_Out_En = false;
	Rev.Debug_Agc_Out_En = false;


	Sys.Direction = FORWARD_SEL;
	Wireless_Direction_Set(Sys.Direction);

	RF_Level_Set(REV_ATT_DET, DET_DEFAULT_ATT_LEVEL);
	Wireless_Mute(WL_MUTE_OFF);

	Sys.Debug_Flag &= ~DEBUG_FWD_DET_LVL_FLAG;
}

void Debug_Reverse_Det_Level(void)
{
	printf("\n\n\rDebug>> Reverse Detect Level Control\n\r");

	Fwd.Debug_Det_Lvl_En = false;
	Rev.Debug_Det_Lvl_En = true;

	Fwd.Debug_Agc_Det_En = false;
	Rev.Debug_Agc_Det_En = false;

	Fwd.Debug_Agc_Out_En = false;
	Rev.Debug_Agc_Out_En = false;

	Sys.Direction = REVERSE_SEL;
	Wireless_Direction_Set(Sys.Direction);

	RF_Level_Set(FWD_ATT_DET, DET_DEFAULT_ATT_LEVEL);
	Wireless_Mute(WL_MUTE_OFF);

	Sys.Debug_Flag &= ~DEBUG_REV_DET_LVL_FLAG;
}

void Debug_Forward_Agc_Det(void)
{
	printf("\n\n\rDebug>> Forward Detect AGC Control\n\r");

	Fwd.Debug_Det_Lvl_En = false;
	Rev.Debug_Det_Lvl_En = false;

	Fwd.Debug_Agc_Det_En = true;
	Rev.Debug_Agc_Det_En = false;

	Fwd.Debug_Agc_Out_En = false;
	Rev.Debug_Agc_Out_En = false;


	Sys.Direction = FORWARD_SEL;
	Wireless_Direction_Set(Sys.Direction);

	Fwd.Att_Det_dB = BOOT_DET_DEFAULT_LEVEL;
	RF_Level_Set(FWD_ATT_DET, Fwd.Att_Det_dB);

	RF_Level_Set(REV_ATT_DET, DET_DEFAULT_ATT_LEVEL);
	Wireless_Mute(WL_MUTE_OFF);

	Sys.Debug_Flag &= ~DEBUG_FWD_AGC_DET_FLAG;
}

void Debug_Reverse_Agc_Det(void)
{
	printf("\n\n\rDebug>> Reverse Detect AGC Control\n\r");

	Fwd.Debug_Det_Lvl_En = false;
	Rev.Debug_Det_Lvl_En = false;

	Fwd.Debug_Agc_Det_En = false;
	Rev.Debug_Agc_Det_En = true;

	Fwd.Debug_Agc_Out_En = false;
	Rev.Debug_Agc_Out_En = false;


	Sys.Direction = REVERSE_SEL;
	Wireless_Direction_Set(Sys.Direction);

	Rev.Att_Det_dB = BOOT_DET_DEFAULT_LEVEL;
	RF_Level_Set(REV_ATT_DET, Rev.Att_Det_dB);

	RF_Level_Set(FWD_ATT_DET, DET_DEFAULT_ATT_LEVEL);
	Wireless_Mute(WL_MUTE_OFF);

	Sys.Debug_Flag &= ~DEBUG_REV_AGC_DET_FLAG;
}

void Debug_Forward_Agc_Out(void)
{
	printf("\n\n\rDebug>> Forward Output AGC Control\n\r");

	Fwd.Debug_Det_Lvl_En = false;
	Rev.Debug_Det_Lvl_En = false;

	Fwd.Debug_Agc_Det_En = false;
	Rev.Debug_Agc_Det_En = false;

	Fwd.Debug_Agc_Out_En = true;
	Rev.Debug_Agc_Out_En = false;


	Sys.Direction = FORWARD_SEL;
	Wireless_Direction_Set(Sys.Direction);

	Fwd.Att_1st_dB = BOOT_AGC_DEFAULT_LEVEL;
	Fwd.Att_2nd_dB = BOOT_AGC_DEFAULT_LEVEL;
	Fwd.Att_3rd_dB = BOOT_AGC_DEFAULT_LEVEL;

	RF_Level_Set(FWD_ATT_3rd, Fwd.Att_3rd_dB);
	RF_Level_Set(FWD_ATT_2nd, Fwd.Att_2nd_dB);
	RF_Level_Set(FWD_ATT_1st, Fwd.Att_1st_dB);

	RF_Level_Set(REV_ATT_DET, DET_DEFAULT_ATT_LEVEL);
	Wireless_Mute(WL_MUTE_OFF);

	Sys.Debug_Flag &= ~DEBUG_FWD_AGC_OUT_FLAG;
}

void Debug_Reverse_Agc_Out(void)
{
	printf("\n\n\rDebug>> Reverse Output AGC Control\n\r");

	Fwd.Debug_Det_Lvl_En = false;
	Rev.Debug_Det_Lvl_En = false;

	Fwd.Debug_Agc_Det_En = false;
	Rev.Debug_Agc_Det_En = false;

	Fwd.Debug_Agc_Out_En = false;
	Rev.Debug_Agc_Out_En = true;


	Sys.Direction = REVERSE_SEL;
	Wireless_Direction_Set(Sys.Direction);

	Rev.Att_1st_dB = BOOT_AGC_DEFAULT_LEVEL;
	Rev.Att_2nd_dB = BOOT_AGC_DEFAULT_LEVEL;
	Rev.Att_3rd_dB = BOOT_AGC_DEFAULT_LEVEL;

	RF_Level_Set(REV_ATT_3rd, Rev.Att_3rd_dB);
	RF_Level_Set(REV_ATT_2nd, Rev.Att_2nd_dB);
	RF_Level_Set(REV_ATT_1st, Rev.Att_1st_dB);

	RF_Level_Set(FWD_ATT_DET, DET_DEFAULT_ATT_LEVEL);
	Wireless_Mute(WL_MUTE_OFF);

	Sys.Debug_Flag &= ~DEBUG_REV_AGC_OUT_FLAG;
}

void Debug_Fwd_Det_Level_UpDown(uchar updown)
{
	if (updown)
	{
		if (Fwd.Det_Level < 0x3FF)	Fwd.Det_Level++;
	}
	else
	{
		if (Fwd.Det_Level > 0x000)	Fwd.Det_Level--;
	}

	printf("System>> Wireless Forward Detect Level = 0x%04x, Voltage = %f\n\r", Fwd.Det_Level, (((float)Fwd.Det_Level * AREF_VOL) / 1024.f));
	Eep_Write(EEP_WIRELESS_FWD_DET_LEVEL_Addr0, (uchar)(Fwd.Det_Level>>8));
	Eep_Write(EEP_WIRELESS_FWD_DET_LEVEL_Addr1, (uchar)Fwd.Det_Level);
}

void Debug_Rev_Det_Level_UpDown(uchar updown)
{
	if (updown)
	{
		if (Rev.Det_Level < 0x3FF)	Rev.Det_Level++;
	}
	else
	{
		if (Rev.Det_Level > 0x000)	Rev.Det_Level--;
	}

	printf("System>> Wireless Reverse Detect Level = 0x%04x, Voltage = %f\n\r", Rev.Det_Level, (((float)Rev.Det_Level * AREF_VOL) / 1024.f));
	Eep_Write(EEP_WIRELESS_REV_DET_LEVEL_Addr0, (uchar)(Rev.Det_Level>>8));
	Eep_Write(EEP_WIRELESS_REV_DET_LEVEL_Addr1, (uchar)Rev.Det_Level);
}

void Debug_Fwd_Agc_Det_UpDown(uchar updown)
{
	if (updown)
	{
		if (Fwd.Att_Det_dB > MIN_ATT)	Fwd.Att_Det_dB -= ATT_STEP;
	}
	else
	{
		if (Fwd.Att_Det_dB < MAX_ATT)	Fwd.Att_Det_dB += ATT_STEP;
	}

	printf("Debug>> Forward Detect Att : %d dB\n\r", Fwd.Att_Det_dB);

	RF_Level_Set(FWD_ATT_DET, Fwd.Att_Det_dB);

	delay_ms(100);

	Fwd.Adc_Value = Agc_Read(FORWARD_AGC);
	printf("Debug>> Forward ADC Value = 0x%04x, Voltage = %f\n\r", Fwd.Adc_Value, (((float)Fwd.Adc_Value * AREF_VOL) / 1024.f));
	Fwd.Agc_Det_Level = Fwd.Adc_Value;
	Eep_Write(EEP_WIRELESS_FWD_AGC_DET_LEVEL_Addr0, (uchar)(Fwd.Agc_Det_Level>>8));
	Eep_Write(EEP_WIRELESS_FWD_AGC_DET_LEVEL_Addr1, (uchar)Fwd.Agc_Det_Level);
}

void Debug_Rev_Agc_Det_UpDown(uchar updown)
{
	if (updown)
	{
		if (Rev.Att_Det_dB > MIN_ATT)	Rev.Att_Det_dB -= ATT_STEP;
	}
	else
	{
		if (Rev.Att_Det_dB < MAX_ATT)	Rev.Att_Det_dB += ATT_STEP;
	}

	printf("Debug>> Reverse Detect Att : %d dB\n\r", Rev.Att_Det_dB);

	RF_Level_Set(REV_ATT_DET, Rev.Att_Det_dB);

	delay_ms(100);

	Rev.Adc_Value = Agc_Read(REVERSE_AGC);
	printf("Debug>> Reverse ADC Value = 0x%04x, Voltage = %f\n\r", Rev.Adc_Value, (((float)Rev.Adc_Value * AREF_VOL) / 1024.f));
	Rev.Agc_Det_Level = Rev.Adc_Value;
	Eep_Write(EEP_WIRELESS_REV_AGC_DET_LEVEL_Addr0, (uchar)(Rev.Agc_Det_Level>>8));
	Eep_Write(EEP_WIRELESS_REV_AGC_DET_LEVEL_Addr1, (uchar)Rev.Agc_Det_Level);
}

void Debug_Fwd_Agc_Out_UpDown(uchar updown)
{
	if (updown)
	{
		if (Fwd.Att_1st_dB > MIN_ATT)	Fwd.Att_1st_dB -= ATT_STEP;
		Fwd.Att_2nd_dB = Fwd.Att_1st_dB;
		Fwd.Att_3rd_dB = Fwd.Att_1st_dB;
	}
	else
	{
		if (Fwd.Att_1st_dB < MAX_ATT)	Fwd.Att_1st_dB += ATT_STEP;
		Fwd.Att_2nd_dB = Fwd.Att_1st_dB;
		Fwd.Att_3rd_dB = Fwd.Att_1st_dB;
	}

	printf("Debug>> Forward ATT Level : %d dB\n\r", Fwd.Att_1st_dB);

	RF_Level_Set(FWD_ATT_3rd, Fwd.Att_3rd_dB);
	RF_Level_Set(FWD_ATT_2nd, Fwd.Att_2nd_dB);
	RF_Level_Set(FWD_ATT_1st, Fwd.Att_1st_dB);

	delay_ms(100);

	Rev.Adc_Value = Agc_Read(REVERSE_AGC);
	printf("Debug>> Reverse ADC Value = 0x%04x, Voltage = %f\n\r", Rev.Adc_Value, (((float)Rev.Adc_Value * AREF_VOL) / 1024.f));
	Fwd.Agc_Out_Level = Rev.Adc_Value;
	Eep_Write(EEP_WIRELESS_FWD_AGC_OUT_LEVEL_Addr0, (uchar)(Fwd.Agc_Out_Level>>8));
	Eep_Write(EEP_WIRELESS_FWD_AGC_OUT_LEVEL_Addr1, (uchar)Fwd.Agc_Out_Level);
}

void Debug_Rev_Agc_Out_UpDown(uchar updown)
{
	if (updown)
	{
		if (Rev.Att_1st_dB > MIN_ATT)	Rev.Att_1st_dB -= ATT_STEP;
		Rev.Att_2nd_dB = Rev.Att_1st_dB;
		Rev.Att_3rd_dB = Rev.Att_1st_dB;
	}
	else
	{
		if (Rev.Att_1st_dB < MAX_ATT)	Rev.Att_1st_dB += ATT_STEP;
		Rev.Att_2nd_dB = Rev.Att_1st_dB;
		Rev.Att_3rd_dB = Rev.Att_1st_dB;
	}

	printf("Debug>> Reverse ATT Level : %d dB\n\r", Rev.Att_1st_dB);

	RF_Level_Set(REV_ATT_3rd, Rev.Att_3rd_dB);
	RF_Level_Set(REV_ATT_2nd, Rev.Att_2nd_dB);
	RF_Level_Set(REV_ATT_1st, Rev.Att_1st_dB);

	delay_ms(100);

	Fwd.Adc_Value = Agc_Read(FORWARD_AGC);
	printf("Debug>> Forward ADC Value = 0x%04x, Voltage = %f\n\r", Fwd.Adc_Value, (((float)Fwd.Adc_Value * AREF_VOL) / 1024.f));
	Rev.Agc_Out_Level = Fwd.Adc_Value;
	Eep_Write(EEP_WIRELESS_REV_AGC_OUT_LEVEL_Addr0, (uchar)(Rev.Agc_Out_Level>>8));
	Eep_Write(EEP_WIRELESS_REV_AGC_OUT_LEVEL_Addr1, (uchar)Rev.Agc_Out_Level);
}

void Debug_Max_Unlock_Cnt_UpDown(uchar updown)
{
	if (updown)
	{
		if (Sys.Max_Unlock_Cnt < MAX_UNLOCK_CNT)	Sys.Max_Unlock_Cnt++;
	}
	else
	{
		if (Sys.Max_Unlock_Cnt > MIN_UNLOCK_CNT)	Sys.Max_Unlock_Cnt--;
	}

	printf("Debug>> Max Unlock Count Value = %d0 msec\n\r", Sys.Max_Unlock_Cnt);

	Eep_Write(EEP_MAX_UNLOCK_CNT_Addr0, (uchar)(Sys.Max_Unlock_Cnt>>8));
	Eep_Write(EEP_MAX_UNLOCK_CNT_Addr1, (uchar)Sys.Max_Unlock_Cnt);
}

void Debug_All_Att(uchar dB)
{
	printf("\n\n\rDebug>> All Att : %d dB\n\r", dB);

	RF_Level_Set(FWD_ATT_DET, dB);
	RF_Level_Set(REV_ATT_DET, dB);

	RF_Level_Set(FWD_ATT_3rd, dB);
	RF_Level_Set(FWD_ATT_2nd, dB);
	RF_Level_Set(FWD_ATT_1st, dB);

	RF_Level_Set(REV_ATT_3rd, dB);
	RF_Level_Set(REV_ATT_2nd, dB);
	RF_Level_Set(REV_ATT_1st, dB);
}

void Debug_Display(uchar dsp)
{
	if (dsp)
	{
		Sys.Debug_Dsp_En = true;
		Sys.Debug_Flag &= ~DEBUG_DSP_START_FLAG;
	}
	else
	{
		Sys.Debug_Dsp_En = false;
		Sys.Debug_Flag &= ~DEBUG_DSP_PAUSE_FLAG;
	}
}

void Debug_Clear(void)
{
	printf("\n\n\rDebug>> Debug Clear...\n\r");

	Fwd.Debug_Det_Lvl_En = false;
	Rev.Debug_Det_Lvl_En = false;

	Fwd.Debug_Agc_Det_En = false;
	Rev.Debug_Agc_Det_En = false;

	Fwd.Debug_Agc_Out_En = false;
	Rev.Debug_Agc_Out_En = false;


	Sys.Debug_Max_Unlock_Cnt_En = false;
	Sys.Debug_Dsp_En = false;

	Wireless_Mute(WL_MUTE_ON);

	Sys.Debug_Flag &= ~DEBUG_CLEAR_FLAG;
}

void Factory_Init(void)
{
	printf("\n\n\rSystem>> Factory Init...\n\r");

	FM_LED_OFF;

#if 1
	Factory_Reset_Data();
	Eep_Data_Read();
#else
	Sys.DCV_Value = Agc_Read(DCV_AGC);

	Sys.WL_Fwd_Det_Level = (uint)((WIRELESS_FWD_DET_VOL*1024.0f) / (float)Sys.DCV_Value);
	Sys.WL_Fwd_Agc_Level = (uint)((WIRELESS_FWD_AGC_REF_VOL*1024.0f) / (float)Sys.DCV_Value);;

	Sys.WL_Rev_Det_Level = (uint)((WIRELESS_REV_DET_VOL*1024.0f) / (float)Sys.DCV_Value);
	Sys.WL_Rev_Agc_Level = (uint)((WIRELESS_REV_AGC_REF_VOL*1024.0f) / (float)Sys.DCV_Value);;

	Sys.FM_Agc_Min_Level = (uint)(((FM_AGC_REF_VOL-0.2f)*1024.0f) / (float)Sys.DCV_Value);
	Sys.FM_Agc_Max_Level = (uint)(((FM_AGC_REF_VOL+0.2f)*1024.0f) / (float)Sys.DCV_Value);
#endif

#if 0
	printf("System>> Wireless Forward Detect Level = 0x%04x, Voltage = %f\n\r", Fwd.Det_Level, (((float)Fwd.Det_Level * AREF_VOL) / 1024.f));
	printf("System>> Wireless Forward AGC Det Level = 0x%04x, Voltage = %f\n\r", Fwd.Agc_Det_Level, (((float)Fwd.Agc_Det_Level * AREF_VOL) / 1024.f));
	printf("System>> Wireless Forward AGC Out Level = 0x%04x, Voltage = %f\n\r", Fwd.Agc_Out_Level, (((float)Fwd.Agc_Out_Level * AREF_VOL) / 1024.f));
	printf("System>> Wireless Reverse Detect Level = 0x%04x, Voltage = %f\n\r", Rev.Det_Level, (((float)Rev.Det_Level * AREF_VOL) / 1024.f));
	printf("System>> Wireless Reverse AGC Det Level = 0x%04x, Voltage = %f\n\r", Rev.Agc_Det_Level, (((float)Rev.Agc_Det_Level * AREF_VOL) / 1024.f));
	printf("System>> Wireless Reverse AGC Out Level = 0x%04x, Voltage = %f\n\r", Rev.Agc_Out_Level, (((float)Rev.Agc_Out_Level * AREF_VOL) / 1024.f));
	printf("System>> FM AGC Level = 0x%04x, Voltage = %f\n\r", FM.Agc_Level, (((float)FM.Agc_Level * AREF_VOL) / 1024.f));
	printf("System>> Max Unlock Counter = %d0 msec\n\r", Sys.Max_Unlock_Cnt);
#endif

	Fwd.Detect = false;
	Fwd.Agc_En = false;
	Fwd.Att_Det_dB = BOOT_DET_DEFAULT_LEVEL;
	Fwd.Att_1st_dB = BOOT_AGC_DEFAULT_LEVEL;
	Fwd.Att_2nd_dB = BOOT_AGC_DEFAULT_LEVEL;
	Fwd.Att_3rd_dB = BOOT_AGC_DEFAULT_LEVEL;

	Rev.Detect = false;
	Rev.Agc_En = false;
	Rev.Att_Det_dB = BOOT_DET_DEFAULT_LEVEL;
	Rev.Att_1st_dB = BOOT_AGC_DEFAULT_LEVEL;
	Rev.Att_2nd_dB = BOOT_AGC_DEFAULT_LEVEL;
	Rev.Att_3rd_dB = BOOT_AGC_DEFAULT_LEVEL;

#if USE_FM
	FM.Agc_En = true;
	FM.Att_Up_En = false;
	FM.Att_Down_En = false;
	FM.Att_1st_dB = BOOT_AGC_DEFAULT_LEVEL;
	FM.Att_2nd_dB = BOOT_AGC_DEFAULT_LEVEL;

	FM.Debug_Att_En = false;
#endif

	Fwd.Debug_Det_Lvl_En = false;
	Rev.Debug_Det_Lvl_En = false;
	Fwd.Debug_Agc_Det_En = false;
	Rev.Debug_Agc_Det_En = false;
	Fwd.Debug_Agc_Out_En = false;
	Rev.Debug_Agc_Out_En = false;
	Sys.Debug_Dsp_En = false;
	Sys.Debug_Flag = 0x00;

	Sys.WL_Check_Sel = REVERSE_SEL;
	Sys.Direction = REVERSE_SEL;

	Wireless_Boot_Level_Set();
	Wireless_Mute(WL_MUTE_ON);

	Fwd.Unlock_Cnt = 0;
	Rev.Unlock_Cnt = 0;

	Sys.Main_Flag = SYS_MAIN;
	Sys.Main_Sub_Flag = SUB_MENU1;

	Sys.Debug_Flag &= ~DEBUG_INIT_FLAG;
}

void Debug_Help_Dsp(void)
{
	printf("\n\n\r==================== Debug Command ====================\n\r");
	printf("*** [01] A, a : Forward Detect Level Control\n\r");
	printf("*** [02] B, b : Reverse Detect Level Control\n\r");
	printf("-------------------------------------------------------\n\r");
	printf("*** [03] J, j : Forward AGC Detect Control\n\r");
	printf("*** [04] K, k : Reverse AGC Detect Control\n\r");
	printf("*** [05] L, l : Forward AGC Output Control\n\r");
	printf("*** [06] M, m : Reverse AGC Output Control\n\r");
	//printf("*** [07] N, n : FM AGC Level Control\n\r");
	printf("-------------------------------------------------------\n\r");
	printf("*** [08] U, u : Debug Up\n\r");
	printf("*** [09] D, d : Debug Down\n\r");
	printf("-------------------------------------------------------\n\r");
	printf("*** [10] V, v : Debug All Att 0dB Set\n\r");
	printf("*** [11] W, w : Debug All Att 10dB Set\n\r");
	printf("*** [12] X, x : Debug Forward/Reverse Path Open\n\r");
	printf("-------------------------------------------------------\n\r");
	printf("*** [13] C, c : Max Unlock Counter Value\n\r");
	printf("-------------------------------------------------------\n\r");
	printf("*** [14] P, p : ADC Value Display Start\n\r");
	printf("*** [15] S, s : ADC Value Display Stop\n\r");
	printf("-------------------------------------------------------\n\r");
	printf("*** [16] Q, q : Debug Quit\n\r");
	printf("*** [17] I, i : Factory Init\n\r");
	printf("*** [18] H, h : Help\n\r");
	printf("=======================================================\n\n\r");

	Sys.Debug_Flag &= ~DEBUG_HELP_FLAG;
}

void Agc_Display(void)
{
	printf("\n\rWireless>> Forward ADC Value = 0x%04x, Voltage = %f\n\r", Fwd.Adc_Value, (((float)Fwd.Adc_Value * AREF_VOL) / 1024.f));
	printf("Wireless>> Reverse ADC Value = 0x%04x, Voltage = %f\n\r", Rev.Adc_Value, (((float)Rev.Adc_Value * AREF_VOL) / 1024.f));

#if USE_FM
	printf("FM>> ADC Value = 0x%04x, Voltage = %f\n\r", FM.Adc_Value, (((float)FM.Adc_Value * AREF_VOL) / 1024.f));
#endif

//	Sys.DCV_Value = Agc_Read(DCV_AGC);
//	printf("System>> Power ADC Value = 0x%04x, Voltage = %f\n\r", Sys.DCV_Value, (((float)Sys.DCV_Value * AREF_VOL) / 1024.f));
}

void Debug_Path_Open(void)
{
	printf("\n\n\rDebug>> Forward/Reverse Path Open...\n\r");

	FWD_DIRECTION_SW1_LOW;
	REV_DIRECTION_SW1_LOW;
}

//*****************************************************************************
//*************************    UART End    ***********************************
//*****************************************************************************

