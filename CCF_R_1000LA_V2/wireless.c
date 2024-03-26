#include "board.h"



////Switch Direction
void setDetectLevel_FWD(uint uiLevel, uint uiAmpOutLevel)
{
	g_Data.eep.detectLevel.FWD = uiLevel;
	g_Data.eep.detectLevel.FWD2_AMP = uiAmpOutLevel;
}

void setDetectLevel_REV(uint uiLevel, uint uiAmpOutLevel)
{
	g_Data.eep.detectLevel.REV = uiLevel;
	g_Data.eep.detectLevel.REV2_AMP = uiAmpOutLevel;
}

void setDetectLevel_FM(uint uiLevel)
{
	g_Data.eep.detectLevel.FM = uiLevel;
	//g_Data.eep.detectLevel.FM_Range = uiRange;
}


#define FWD__IS_DETECTED()					g_Data.detect_status.FWD
#define FWD__SET_STATUS(x)					(g_Data.detect_status.FWD = x)
#define FWD__CHECK_SIGNAL()					(g_Data.readADC.FWD >= g_Data.eep.detectLevel.FWD)
#define FWD__CHECK_SIGNAL2()				( (g_Data.readADC.FWD >= (g_Data.eep.detectLevel.FWD - g_Data.eep.uto.FWD)) ||  (g_Data.readADC.FWD2_AMP >= WIRELESS_FWD2_AMP_OUT_LEVEL ))
#define FWD__UNDETECTED_SIGNAL()			( g_Data.undetectCount.FWD >= g_Data.eep.uiUnlock_count )
#define FWD__DETECT_SIGNAL()				( g_Data.detectCount.FWD >= g_Data.eep.uiLock_count )


#define REV__IS_DETECTED()					g_Data.detect_status.REV
#define REV__SET_STATUS(x)					(g_Data.detect_status.REV = x)
#define REV__CHECK_SIGNAL()					(g_Data.readADC.REV >= g_Data.eep.detectLevel.REV)
#define REV__CHECK_SIGNAL2()				( (g_Data.readADC.REV >= (g_Data.eep.detectLevel.REV - g_Data.eep.uto.REV)) ||  (g_Data.readADC.REV2_AMP >= WIRELESS_REV2_AMP_OUT_LEVEL ))
#define REV__UNDETECTED_SIGNAL()			( g_Data.undetectCount.REV >= g_Data.eep.uiUnlock_count )
#define REV__DETECT_SIGNAL()				( g_Data.detectCount.REV >= g_Data.eep.uiLock_count )


#define _REV_RECHECK__1ST		180
#define _REV_RECHECK__2ND		150
#define _REV_RECHECK__FWD1		589
#define _REV_RECHECK__FWD2		580

BOOL Recheck_REV()
{
	if(g_Data.eep.detectLevel.REV >= _REV_RECHECK__1ST)
		return 1;
	
	if(g_Data.readADC.REV >= _REV_RECHECK__1ST )
		return 1;
	else if(g_Data.readADC.REV >= _REV_RECHECK__2ND )
	{
		if(g_Data.readADC.FWD <= _REV_RECHECK__FWD1)
			return 0;
	}
	else
	{
		if(g_Data.readADC.FWD <= _REV_RECHECK__FWD2)
			return 0;
	}

	return 0;
}


void Wireless_Check()
{
	switch(g_Data.ucCurrentCheckMode)
	{
		case CM_FWD:
		default:
			if(FWD__IS_DETECTED())
			{
				if(FWD__CHECK_SIGNAL2())
				{
					g_Data.undetectCount.FWD = 0;
				}
				else
				{
					g_Data.undetectCount.FWD++;
				}

				if(FWD__UNDETECTED_SIGNAL())
				{
					FWD__SET_STATUS(0);
					Wireless_Mute(1);
				}
				
			}
			else
			{
				if(!REV__IS_DETECTED())
				{
					if(FWD__CHECK_SIGNAL())
						g_Data.detectCount.FWD++;
					else
						g_Data.detectCount.FWD = 0;

					if(FWD__DETECT_SIGNAL())
					{
						FWD__SET_STATUS(1);
						Wireless_ModeChange(CM_FWD);
					}
				}
				
			}


			g_Data.ucCurrentCheckMode = CM_REV;

			
			break;
		case CM_REV:
			if(REV__IS_DETECTED())
			{
				if(REV__CHECK_SIGNAL2())
				{
					g_Data.undetectCount.REV = 0;
				}
				else
				{
					g_Data.undetectCount.REV++;
				}

				if(REV__UNDETECTED_SIGNAL())
				{
					REV__SET_STATUS(0);
					Wireless_Mute(1);
				}
				
			}
			else
			{
				if(!FWD__IS_DETECTED())
				{
					if(REV__CHECK_SIGNAL())
						g_Data.detectCount.REV++;
					else
						g_Data.detectCount.REV = 0;

					if(REV__DETECT_SIGNAL())
					{
						REV__SET_STATUS(1);
						Wireless_ModeChange(CM_REV);

						if(!Recheck_REV())
						{
							REV__SET_STATUS(0);
							Wireless_Mute(1);
						}
					}
				}
				
			}


			g_Data.ucCurrentCheckMode = CM_FWD;


			break;
	}

	if(FWD__IS_DETECTED())
		setLED_FWD(1);
	else
		setLED_FWD(0);

	if(REV__IS_DETECTED())
		setLED_REV(1);
	else
		setLED_REV(0);
	

	//printf("F: %d, R: %d \r\n", FWD__IS_DETECTED(), REV__IS_DETECTED());
}


void Wireless_ModeChange(int iMode)
{
	if(iMode == CM_REV)
		Wireless_REV_Set();
	else
		Wireless_FWD_Set();
}


void Wireless_REV_Set(void)
{
	if(g_Data.detect_status.REV)
	{
		g_Data.ucCurrentCheckMode = CM_REV;
		Wireless_Direction_Set(CM_REV);
	}
	else
	{
		Wireless_Mute(1);
	}
}

void Wireless_FWD_Set(void)
{
	if(g_Data.detect_status.FWD)
	{
		g_Data.ucCurrentCheckMode = CM_FWD;
		Wireless_Direction_Set(CM_FWD);
	}
	else
	{
		Wireless_Mute(1);
	}
}

void Wireless_Direction_Set(uchar direct)
{
	if (direct == CM_FWD)
	{
		DEBUGF(MCU_DEBUG, ("Wireless>> Direction Select : Forward ...\r\n"));
		setSwitch_REV1(0);
		setSwitch_REV2(0);

		setSwitch_FWD1(1);
		setSwitch_FWD2(1);

		setLED_FWD(1);
		setLED_REV(0);
	}
	else
	{
		DEBUGF(MCU_DEBUG, ("Wireless>> Direction Select : Reverse ...\r\n"));
		setSwitch_REV1(1);
		setSwitch_REV2(1);

		setSwitch_FWD1(0);
		setSwitch_FWD2(0);

		setLED_FWD(0);
		setLED_REV(1);
	}
}

void Wireless_Mute(uchar mute)
{
	if (mute)
	{
		DEBUGF(MCU_DEBUG, ("Wireless>> Mute On...\r\n"));

		setSwitch_REV1(1);
		setSwitch_FWD1(1);
		setSwitch_REV2(0);
		setSwitch_FWD2(0);

		setLED_FWD(0);
		setLED_REV(0);
	}
	else
	{
		DEBUGF(MCU_DEBUG, ("Wireless>> Mute Off...\r\n"));

	}

	delay_ms(100);
}


void FM_Check()
{
	if( g_Data.readADC.FM >= g_Data.eep.detectLevel.FM )
		setLED_FM(1);
	else
		setLED_FM(0);
}

