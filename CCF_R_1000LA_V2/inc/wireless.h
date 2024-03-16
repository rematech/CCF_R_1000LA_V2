#ifndef __WIRELESS_H__
#define __WIRELESS_H__



void Wireless_Check();	
void FM_Check();


void setDetectLevel_FWD(uint uiLevel, uint uiAmpOutLevel);
void setDetectLevel_REV(uint uiLevel, uint uiAmpOutLevel);
void setDetectLevel_FM(uint uiLevel);

void Wireless_REV_Set(void);
void Wireless_FWD_Set(void);
void Wireless_Mute(uchar mute);
void Wireless_Direction_Set(uchar direct);

void Wireless_ModeChange(int iMode);


#if 0
// ATT Define
#define FWD_ATT_DET					0
#define FWD_ATT_1st					1
#define FWD_ATT_2nd					2
#define FWD_ATT_3rd					3

#define REV_ATT_DET					4
#define REV_ATT_1st					5
#define REV_ATT_2nd					6
#define REV_ATT_3rd					7

// Mute Define
#define WL_MUTE_OFF					0
#define WL_MUTE_ON					1

// RF Level Define
#define MIN_ATT						0		// 0 dB
#define MAX_ATT						31		// -31 dB
#define ATT_STEP					1		// Step -1 dB

#define LIMIT_1st_ATT				5		// -5 dB

#define DET_GND_DELAY				300		// 100 ms


void RF_Level_Set(uchar att_sel, uchar rf_db);
void RF_Level_Init(void);


void Wireless_Mute(uchar mute);
void Wireless_Boot_Level_Set(void);
void Wireless_Detect_Ground(uchar direct);

void Wireless_Direction_Set(uchar direct);

void Wireless_Check(void);
void Wireless_Forward_Set(void);
void Wireless_Reverse_Set(void);

void Wireless_AGC_Control(void);
void AGC_Forward_Det_Control(void);
void AGC_Forward_Out_Control(void);
void AGC_Reverse_Out_Control(void);
void AGC_Reverse_Det_Control(void);
#endif


#endif
