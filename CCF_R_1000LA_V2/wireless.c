#include "inc/board.h"



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


