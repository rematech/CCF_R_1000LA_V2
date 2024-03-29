#ifndef __ADC_H_
#define __ADC_H_


#define AREF_VOL					3.3f	// 3.3f

#define WIRELESS_FWD_DET_VOL		0.50f	//0.80f		// 0.08f	//0.15f		//1.20f		//0.93f
#define WIRELESS_FWD_AGC_DET_VOL	1.76f	// 1.76f
#define WIRELESS_FWD_AGC_OUT_VOL	1.85f	// 1.573f	// 1.573f	// 1.90f

#define WIRELESS_REV_DET_VOL		0.50f	//0.80f		// 0.08f	// 0.15f	// 1.20f	//0.92f
#define WIRELESS_REV_AGC_DET_VOL	1.78f	// 1.78f
#define WIRELESS_REV_AGC_OUT_VOL	1.85f	// 1.522f	// 1.522f	// 1.92f

#define WIRELESS_DET_RANGE_VOL		16.0f	// +/- 16.0, 3.0dB
#define WIRELESS_AGC_RANGE_VOL		16.0f	// +/- 16.0, 3.0dB

#define FM_DET_VOL					0.52f	// 0.52f
#define FM_AGC_REF_VOL				2.16f	// 2.99f	// 1.78f
#define FM_AGC_RANGE_VOL			64.0f	// +/- 64.0, 3dB

#define WIRELESS_FWD_DET_LEVEL		(uint)((WIRELESS_FWD_DET_VOL*1024.0f) / AREF_VOL)
#define WIRELESS_FWD_AGC_DET_LEVEL	(uint)((WIRELESS_FWD_AGC_DET_VOL*1024.0f) / AREF_VOL)
#define WIRELESS_FWD_AGC_OUT_LEVEL	(uint)((WIRELESS_FWD_AGC_OUT_VOL*1024.0f) / AREF_VOL)

#define WIRELESS_REV_DET_LEVEL		(uint)((WIRELESS_REV_DET_VOL*1024.0f) / AREF_VOL)
#define WIRELESS_REV_AGC_DET_LEVEL	(uint)((WIRELESS_REV_AGC_DET_VOL*1024.0f) / AREF_VOL)
#define WIRELESS_REV_AGC_OUT_LEVEL	(uint)((WIRELESS_REV_AGC_OUT_VOL*1024.0f) / AREF_VOL)

#define FM_AGC_LEVEL				(uint)((FM_AGC_REF_VOL*1024.0f) / AREF_VOL)

#define DCV_DET_LEVEL				(uint)(((AREF_VOL-0.5f)*1024.0f) / AREF_VOL)

// ATT Default Level Define
#define BOOT_DET_DEFAULT_LEVEL		0		// 0.0 dB
#define BOOT_AGC_DEFAULT_LEVEL		0		// 0.0 dB
#define DET_DEFAULT_ATT_LEVEL		30		// -30 dB
#define DEBUG_ALL_ATT_VALUE			10		// -10 dB

void Adc_Init(void);
uint Agc_Read(uchar channel);
void AGC_All_Read(void);



#endif
