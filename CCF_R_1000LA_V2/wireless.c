#include "board.h"



// Att Value : 0 ~ 63(63=최대 감소)
void RF_Level_Set(uchar att_sel, uchar rf_db)
{
	uchar i, temp;

	ATT_SCK_LOW;

	switch(att_sel)
	{
		case FWD_ATT_DET :
			FWD_ATT_DET_LE_LOW;
			break;
		case FWD_ATT_1st :
			FWD_ATT_1st_LE_LOW;
			break;
		case FWD_ATT_2nd :
			FWD_ATT_2nd_LE_LOW;
			break;
		case FWD_ATT_3rd :
			FWD_ATT_3rd_LE_LOW;
			break;
		case REV_ATT_DET :
			REV_ATT_DET_LE_LOW;
			break;
		case REV_ATT_1st :
			REV_ATT_1st_LE_LOW;
			break;
		case REV_ATT_2nd :
			REV_ATT_2nd_LE_LOW;
			break;
		case REV_ATT_3rd :
			REV_ATT_3rd_LE_LOW;
			break;
		default :
			break;
	}

	temp = (rf_db * 2);

	for (i=0; i<6; i++)
	{
		delay_us(10);

		if ((temp >> (5-i)) & 0x01)		ATT_DOUT_HIGH;
		else							ATT_DOUT_LOW;

		delay_us(10);
		ATT_SCK_HIGH;

		delay_us(10);
		ATT_SCK_LOW;
	}

	delay_us(10);
	switch(att_sel)
	{
		case FWD_ATT_DET :
			FWD_ATT_DET_LE_HIGH;
			break;
		case FWD_ATT_1st :
			FWD_ATT_1st_LE_HIGH;
			break;
		case FWD_ATT_2nd :
			FWD_ATT_2nd_LE_HIGH;
			break;
		case FWD_ATT_3rd :
			FWD_ATT_3rd_LE_HIGH;
			break;
		case REV_ATT_DET :
			REV_ATT_DET_LE_HIGH;
			break;
		case REV_ATT_1st :
			REV_ATT_1st_LE_HIGH;
			break;
		case REV_ATT_2nd :
			REV_ATT_2nd_LE_HIGH;
			break;
		case REV_ATT_3rd :
			REV_ATT_3rd_LE_HIGH;
			break;
		default :
			break;
	}

	delay_us(10);
	switch(att_sel)
	{
		case FWD_ATT_DET :
			FWD_ATT_DET_LE_LOW;
			break;
		case FWD_ATT_1st :
			FWD_ATT_1st_LE_LOW;
			break;
		case FWD_ATT_2nd :
			FWD_ATT_2nd_LE_LOW;
			break;
		case FWD_ATT_3rd :
			FWD_ATT_3rd_LE_LOW;
			break;
		case REV_ATT_DET :
			REV_ATT_DET_LE_LOW;
			break;
		case REV_ATT_1st :
			REV_ATT_1st_LE_LOW;
			break;
		case REV_ATT_2nd :
			REV_ATT_2nd_LE_LOW;
			break;
		case REV_ATT_3rd :
			REV_ATT_3rd_LE_LOW;
			break;
		default :
			break;
	}

	ATT_SCK_LOW;

	delay_us(10);
}

void RF_Level_Init(void)
{
	FWD_ATT_DET_LE_LOW;
	FWD_ATT_1st_LE_LOW;
	FWD_ATT_2nd_LE_LOW;
	FWD_ATT_3rd_LE_LOW;

	REV_ATT_DET_LE_LOW;
	REV_ATT_1st_LE_LOW;
	REV_ATT_2nd_LE_LOW;
	REV_ATT_3rd_LE_LOW;

	ATT_SCK_LOW;
}

void Wireless_Mute(uchar mute)
{
	if (mute)
	{
		DEBUGF(MCU_DEBUG, ("Wireless>> Mute On...\r\n"));

		WL_OUT_MUTE0_LOW;
		WL_OUT_MUTE1_LOW;
		WL_OUT_MUTE2_LOW;
		WL_OUT_MUTE3_LOW;

		REV_DIRECTION_SW1_LOW;
		FWD_DIRECTION_SW1_LOW;
		REV_DIRECTION_SW2_HIGH;
		FWD_DIRECTION_SW2_HIGH;

		FWD_LED_OFF;
		REV_LED_OFF;
	}
	else
	{
		DEBUGF(MCU_DEBUG, ("Wireless>> Mute Off...\r\n"));

		WL_OUT_MUTE0_HIGH;
		WL_OUT_MUTE1_HIGH;
		WL_OUT_MUTE2_HIGH;
		WL_OUT_MUTE3_HIGH;
	}
}

void Wireless_Direction_Set(uchar direct)
{
	if (direct == FORWARD_SEL)
	{
		DEBUGF(MCU_DEBUG, ("Wireless>> Direction Select : Forward ...\r\n"));
		REV_DIRECTION_SW1_LOW;
		FWD_DIRECTION_SW1_HIGH;
		REV_DIRECTION_SW2_LOW;
		FWD_DIRECTION_SW2_HIGH;

		FWD_LED_ON;
		REV_LED_OFF;
	}
	else
	{
		DEBUGF(MCU_DEBUG, ("Wireless>> Direction Select : Reverse ...\r\n"));
		REV_DIRECTION_SW1_HIGH;
		FWD_DIRECTION_SW1_LOW;
		REV_DIRECTION_SW2_HIGH;
		FWD_DIRECTION_SW2_LOW;

		FWD_LED_OFF;
		REV_LED_ON;
	}
}


void Wireless_Boot_Level_Set(void)
{
	RF_Level_Set(FWD_ATT_DET, Fwd.Att_Det_dB);
	RF_Level_Set(FWD_ATT_3rd, Fwd.Att_3rd_dB);
	RF_Level_Set(FWD_ATT_2nd, Fwd.Att_2nd_dB);
	RF_Level_Set(FWD_ATT_1st, Fwd.Att_1st_dB);

	RF_Level_Set(REV_ATT_DET, Rev.Att_Det_dB);
	RF_Level_Set(REV_ATT_3rd, Rev.Att_3rd_dB);
	RF_Level_Set(REV_ATT_2nd, Rev.Att_2nd_dB);
	RF_Level_Set(REV_ATT_1st, Rev.Att_1st_dB);
}

void Wireless_Detect_Ground(uchar direct)
{
	if (direct == FORWARD_SEL)
	{
		// Port B, Bit6 Output
		//PORTB = 0x3F;
		DDRB  = 0x5B;
		REV_SET_GND;

		delay_ms(DET_GND_DELAY);

		// Port B, Bit6 Input
		PORTB = 0x3F;
		DDRB  = 0x1B;
	}
	else
	{
		// Port B, Bit7 Output
		//PORTB = 0x3F;
		DDRB  = 0x9B;
		FWD_SET_GND;

		delay_ms(DET_GND_DELAY);

		// Port B, Bit7 Input
		PORTB = 0x3F;
		DDRB  = 0x1B;
	}
}





///////////////////////////////////
void Wireless_Check(void)
{
	bool detect;

	if (Sys.WL_Check_Sel == REVERSE_SEL)
	{
		if (Rev.Detect)
		{
			if (Rev.Adc_Value >= (Rev.Det_Level-WIRELESS_DET_RANGE_VOL))	
				detect = true;
			else
				detect = false;
		}
		else
		{
			if (Rev.Adc_Value >= Rev.Det_Level)
				detect = true;
			else
				detect = false;
		}

		if ((Rev.Detect != detect) && (Fwd.Detect == false))
		{
			if (!Rev.Detect)
			{
				Rev.Detect = detect;
				Wireless_Reverse_Set();
				Rev.Unlock_Cnt = 0;
			}
			else
			{
				if (!detect)
				{
					if (Rev.Unlock_Cnt < Sys.Max_Unlock_Cnt)
					{
						Rev.Unlock_Cnt++;
					}
					else
					{
						Rev.Detect = detect;
						Wireless_Reverse_Set();
						Rev.Unlock_Cnt = 0;
					}
				}
				else
				{
					Rev.Unlock_Cnt = 0;
				}
			}
		}

		Sys.WL_Check_Sel = FORWARD_SEL;
	}
	else
	{
		if (Fwd.Detect)
		{
			if (Fwd.Adc_Value >= (Fwd.Det_Level-WIRELESS_DET_RANGE_VOL))	detect = true;
			else															detect = false;
		}
		else
		{
			if (Fwd.Adc_Value >= Fwd.Det_Level)								detect = true;
			else															detect = false;
		}

		if ((Fwd.Detect != detect) && (Rev.Detect == false))
		{
			if (!Fwd.Detect)
			{
				Fwd.Detect = detect;
				Wireless_Forward_Set();
				Fwd.Unlock_Cnt = 0;
			}
			else
			{
				if (!detect)
				{
					if (Fwd.Unlock_Cnt < Sys.Max_Unlock_Cnt)
					{
						Fwd.Unlock_Cnt++;
					}
					else
					{
						Fwd.Detect = detect;
						Wireless_Forward_Set();
						Fwd.Unlock_Cnt = 0;
					}
				}
				else
				{
					Fwd.Unlock_Cnt = 0;
				}
			}
		}

		Sys.WL_Check_Sel = REVERSE_SEL;
	}
}

void Wireless_Forward_Set(void)
{
	Wireless_Detect_Ground(FORWARD_SEL);

	if (Fwd.Detect)
	{
		DEBUGF(MCU_DEBUG, ("Wireless>> Forward Signal Detect...\r\n"));

		Fwd.Detect = true;
		Fwd.Agc_En = true;

		Sys.Direction = FORWARD_SEL;
		Wireless_Direction_Set(Sys.Direction);

		RF_Level_Set(REV_ATT_DET, DET_DEFAULT_ATT_LEVEL);
		Wireless_Mute(WL_MUTE_OFF);
	}
	else
	{
		Wireless_Mute(WL_MUTE_ON);
		DEBUGF(MCU_DEBUG, ("Wireless>> Forward Signal Loss...\r\n"));

		Fwd.Detect = false;
		Fwd.Agc_En = false;
		Fwd.Att_Det_dB = BOOT_DET_DEFAULT_LEVEL;
		Fwd.Att_1st_dB = BOOT_AGC_DEFAULT_LEVEL;
		Fwd.Att_2nd_dB = BOOT_AGC_DEFAULT_LEVEL;
		Fwd.Att_3rd_dB = BOOT_AGC_DEFAULT_LEVEL;

		Rev.Att_Det_dB = BOOT_DET_DEFAULT_LEVEL;

		RF_Level_Set(FWD_ATT_DET, Fwd.Att_Det_dB);
		RF_Level_Set(FWD_ATT_1st, Fwd.Att_1st_dB);
		RF_Level_Set(FWD_ATT_2nd, Fwd.Att_2nd_dB);
		RF_Level_Set(FWD_ATT_3rd, Fwd.Att_3rd_dB);

		RF_Level_Set(REV_ATT_DET, Rev.Att_Det_dB);
	}
}

void Wireless_Reverse_Set(void)
{
	Wireless_Detect_Ground(REVERSE_SEL);

	if (Rev.Detect)
	{
		DEBUGF(MCU_DEBUG, ("Wireless>> Reverse Signal Detect...\r\n"));

		Rev.Detect = true;
		Rev.Agc_En = true;

		Sys.Direction = REVERSE_SEL;
		Wireless_Direction_Set(Sys.Direction);

		RF_Level_Set(FWD_ATT_DET, DET_DEFAULT_ATT_LEVEL);
		Wireless_Mute(WL_MUTE_OFF);
	}
	else
	{
		Wireless_Mute(WL_MUTE_ON);
		DEBUGF(MCU_DEBUG, ("Wireless>> Reverse Signal Loss...\r\n"));

		Rev.Detect = false;
		Rev.Agc_En = false;
		Rev.Att_Det_dB = BOOT_DET_DEFAULT_LEVEL;
		Rev.Att_1st_dB = BOOT_AGC_DEFAULT_LEVEL;
		Rev.Att_2nd_dB = BOOT_AGC_DEFAULT_LEVEL;
		Rev.Att_3rd_dB = BOOT_AGC_DEFAULT_LEVEL;

		Fwd.Att_Det_dB = BOOT_DET_DEFAULT_LEVEL;

		RF_Level_Set(REV_ATT_DET, Rev.Att_Det_dB);
		RF_Level_Set(REV_ATT_1st, Rev.Att_1st_dB);
		RF_Level_Set(REV_ATT_2nd, Rev.Att_2nd_dB);
		RF_Level_Set(REV_ATT_3rd, Rev.Att_3rd_dB);

		RF_Level_Set(FWD_ATT_DET, Fwd.Att_Det_dB);
	}
}

void Wireless_AGC_Control(void)
{
	if (Sys.Direction == FORWARD_SEL)
	{
		if (Fwd.Agc_En)
		{
			if (RX_AGC_EN)	AGC_Forward_Det_Control();
			AGC_Forward_Out_Control();
		}
	}
	else
	{
		if (Rev.Agc_En)
		{
			if (RX_AGC_EN)	AGC_Reverse_Det_Control();
			AGC_Reverse_Out_Control();
		}
	}
}

void AGC_Forward_Det_Control(void)
{
	if (Fwd.Adc_Value > Fwd.Agc_Det_Level)
	{
		if (Fwd.Att_Det_dB < MAX_ATT)
		{
			Fwd.Att_Det_dB += ATT_STEP;
			RF_Level_Set(FWD_ATT_DET, Fwd.Att_Det_dB);
		}
	}
}

void AGC_Forward_Out_Control(void)
{
	if (Rev.Adc_Value > Fwd.Agc_Out_Level)
	{
		if (Fwd.Att_3rd_dB < LIMIT_1st_ATT)
		{
			Fwd.Att_3rd_dB += ATT_STEP;
			RF_Level_Set(FWD_ATT_3rd, Fwd.Att_3rd_dB);
		}
		else if (Fwd.Att_2nd_dB < LIMIT_1st_ATT)
		{
			Fwd.Att_2nd_dB += ATT_STEP;
			RF_Level_Set(FWD_ATT_2nd, Fwd.Att_2nd_dB);
		}
		else if (Fwd.Att_1st_dB < LIMIT_1st_ATT)
		{
			Fwd.Att_1st_dB += ATT_STEP;
			RF_Level_Set(FWD_ATT_1st, Fwd.Att_1st_dB);
		}
		else
		{
			if ((Fwd.Att_3rd_dB <= Fwd.Att_2nd_dB) && (Fwd.Att_3rd_dB <= Fwd.Att_1st_dB))
			{
				if (Fwd.Att_3rd_dB < MAX_ATT)
				{
					Fwd.Att_3rd_dB += ATT_STEP;
					RF_Level_Set(FWD_ATT_3rd, Fwd.Att_3rd_dB);
				}
			}
			else if (Fwd.Att_3rd_dB > Fwd.Att_2nd_dB)
			{
				if (Fwd.Att_2nd_dB < MAX_ATT)
				{
					Fwd.Att_2nd_dB += ATT_STEP;
					RF_Level_Set(FWD_ATT_2nd, Fwd.Att_2nd_dB);
				}
			}
			else if (Fwd.Att_3rd_dB > Fwd.Att_1st_dB)
			{
				if (Fwd.Att_1st_dB < MAX_ATT)
				{
					Fwd.Att_1st_dB += ATT_STEP;
					RF_Level_Set(FWD_ATT_1st, Fwd.Att_1st_dB);
				}
			}
		}
	}
	else if (Rev.Adc_Value < (Fwd.Agc_Out_Level-WIRELESS_AGC_RANGE_VOL))
	{
		Fwd.Att_1st_dB = BOOT_AGC_DEFAULT_LEVEL;
		Fwd.Att_2nd_dB = BOOT_AGC_DEFAULT_LEVEL;
		Fwd.Att_3rd_dB = BOOT_AGC_DEFAULT_LEVEL;
		RF_Level_Set(FWD_ATT_1st, Fwd.Att_1st_dB);
		RF_Level_Set(FWD_ATT_2nd, Fwd.Att_2nd_dB);
		RF_Level_Set(FWD_ATT_3rd, Fwd.Att_3rd_dB);
	}
}

void AGC_Reverse_Det_Control(void)
{
	if (Rev.Adc_Value > Rev.Agc_Det_Level)
	{
		if (Rev.Att_Det_dB < MAX_ATT)
		{
			Rev.Att_Det_dB += ATT_STEP;
			RF_Level_Set(REV_ATT_DET, Rev.Att_Det_dB);
		}
	}
}

void AGC_Reverse_Out_Control(void)
{
	if (Fwd.Adc_Value > Rev.Agc_Out_Level)
	{
		if (Rev.Att_3rd_dB < LIMIT_1st_ATT)
		{
			Rev.Att_3rd_dB += ATT_STEP;
			RF_Level_Set(REV_ATT_3rd, Rev.Att_3rd_dB);
		}
		else if (Rev.Att_2nd_dB < LIMIT_1st_ATT)
		{
			Rev.Att_2nd_dB += ATT_STEP;
			RF_Level_Set(REV_ATT_2nd, Rev.Att_2nd_dB);
		}
		else if (Rev.Att_1st_dB < LIMIT_1st_ATT)
		{
			Rev.Att_1st_dB += ATT_STEP;
			RF_Level_Set(REV_ATT_1st, Rev.Att_1st_dB);
		}
		else
		{
			if ((Rev.Att_3rd_dB <= Rev.Att_2nd_dB) && (Rev.Att_3rd_dB <= Rev.Att_1st_dB))
			{
				if (Rev.Att_3rd_dB < MAX_ATT)
				{
					Rev.Att_3rd_dB += ATT_STEP;
					RF_Level_Set(REV_ATT_3rd, Rev.Att_3rd_dB);
				}
			}
			else if (Rev.Att_3rd_dB > Rev.Att_2nd_dB)
			{
				if (Rev.Att_2nd_dB < MAX_ATT)
				{
					Rev.Att_2nd_dB += ATT_STEP;
					RF_Level_Set(REV_ATT_2nd, Rev.Att_2nd_dB);
				}
			}
			else if (Rev.Att_3rd_dB > Rev.Att_1st_dB)
			{
				if (Rev.Att_1st_dB < MAX_ATT)
				{
					Rev.Att_1st_dB += ATT_STEP;
					RF_Level_Set(REV_ATT_1st, Rev.Att_1st_dB);
				}
			}
		}
	}
	else if (Fwd.Adc_Value < (Rev.Agc_Out_Level-WIRELESS_AGC_RANGE_VOL))
	{
		Rev.Att_1st_dB = BOOT_AGC_DEFAULT_LEVEL;
		Rev.Att_2nd_dB = BOOT_AGC_DEFAULT_LEVEL;
		Rev.Att_3rd_dB = BOOT_AGC_DEFAULT_LEVEL;
		RF_Level_Set(REV_ATT_1st, Rev.Att_1st_dB);
		RF_Level_Set(REV_ATT_2nd, Rev.Att_2nd_dB);
		RF_Level_Set(REV_ATT_3rd, Rev.Att_3rd_dB);
	}
}

void FM_AGC_Control(void)
{
	if ( (FM.Adc_Value < (FM.Agc_Level-FM_AGC_RANGE_VOL))
		|| (FM.Adc_Value > (FM.Agc_Level+FM_AGC_RANGE_VOL)) )
	{
		FM_LED_OFF;
	}
	else
	{
		FM_LED_ON;
	}
}


