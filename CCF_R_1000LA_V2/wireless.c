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


