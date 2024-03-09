#include "board.h"

void Eep_1st_Write(void)
{
	Eep_Write(EEP_1st_Addr, EEP_1st_DATA);

	Eep_Write(EEP_Ver_Addr, Sys.Version);

	Eep_Write(EEP_WIRELESS_FWD_DET_LEVEL_Addr0, (uchar)(Fwd.Det_Level>>8));
	Eep_Write(EEP_WIRELESS_FWD_DET_LEVEL_Addr1, (uchar)Fwd.Det_Level);
	Eep_Write(EEP_WIRELESS_FWD_AGC_DET_LEVEL_Addr0, (uchar)(Fwd.Agc_Det_Level>>8));
	Eep_Write(EEP_WIRELESS_FWD_AGC_DET_LEVEL_Addr1, (uchar)Fwd.Agc_Det_Level);
	Eep_Write(EEP_WIRELESS_FWD_AGC_OUT_LEVEL_Addr0, (uchar)(Fwd.Agc_Out_Level>>8));
	Eep_Write(EEP_WIRELESS_FWD_AGC_OUT_LEVEL_Addr1, (uchar)Fwd.Agc_Out_Level);

	Eep_Write(EEP_WIRELESS_REV_DET_LEVEL_Addr0, (uchar)(Rev.Det_Level>>8));
	Eep_Write(EEP_WIRELESS_REV_DET_LEVEL_Addr1, (uchar)Rev.Det_Level);
	Eep_Write(EEP_WIRELESS_REV_AGC_DET_LEVEL_Addr0, (uchar)(Rev.Agc_Det_Level>>8));
	Eep_Write(EEP_WIRELESS_REV_AGC_DET_LEVEL_Addr1, (uchar)Rev.Agc_Det_Level);
	Eep_Write(EEP_WIRELESS_REV_AGC_OUT_LEVEL_Addr0, (uchar)(Rev.Agc_Out_Level>>8));
	Eep_Write(EEP_WIRELESS_REV_AGC_OUT_LEVEL_Addr1, (uchar)Rev.Agc_Out_Level);

#if USE_FM
	Eep_Write(EEP_FM_AGC_LEVEL_Addr0, (uchar)(FM.Agc_Level>>8));
	Eep_Write(EEP_FM_AGC_LEVEL_Addr1, (uchar)FM.Agc_Level);
#endif

	Eep_Write(EEP_MAX_UNLOCK_CNT_Addr0, (uchar)(Sys.Max_Unlock_Cnt>>8));
	Eep_Write(EEP_MAX_UNLOCK_CNT_Addr1, (uchar)Sys.Max_Unlock_Cnt);
}

void Eep_Data_Read(void)
{
	Sys.Version = Eep_Read(EEP_Ver_Addr);

	Fwd.Det_Level = ((uint)Eep_Read(EEP_WIRELESS_FWD_DET_LEVEL_Addr0)<<8) | (uint)Eep_Read(EEP_WIRELESS_FWD_DET_LEVEL_Addr1);
	Fwd.Agc_Det_Level = ((uint)Eep_Read(EEP_WIRELESS_FWD_AGC_DET_LEVEL_Addr0)<<8) | (uint)Eep_Read(EEP_WIRELESS_FWD_AGC_DET_LEVEL_Addr1);
	Fwd.Agc_Out_Level = ((uint)Eep_Read(EEP_WIRELESS_FWD_AGC_OUT_LEVEL_Addr0)<<8) | (uint)Eep_Read(EEP_WIRELESS_FWD_AGC_OUT_LEVEL_Addr1);

	Rev.Det_Level = ((uint)Eep_Read(EEP_WIRELESS_REV_DET_LEVEL_Addr0)<<8) | (uint)Eep_Read(EEP_WIRELESS_REV_DET_LEVEL_Addr1);
	Rev.Agc_Det_Level = ((uint)Eep_Read(EEP_WIRELESS_REV_AGC_DET_LEVEL_Addr0)<<8) | (uint)Eep_Read(EEP_WIRELESS_REV_AGC_DET_LEVEL_Addr1);
	Rev.Agc_Out_Level = ((uint)Eep_Read(EEP_WIRELESS_REV_AGC_OUT_LEVEL_Addr0)<<8) | (uint)Eep_Read(EEP_WIRELESS_REV_AGC_OUT_LEVEL_Addr1);

#if USE_FM
	FM.Agc_Level = ((uint)Eep_Read(EEP_FM_AGC_LEVEL_Addr0)<<8) | (uint)Eep_Read(EEP_FM_AGC_LEVEL_Addr1);
#endif

	Sys.Max_Unlock_Cnt = ((uint)Eep_Read(EEP_MAX_UNLOCK_CNT_Addr0)<<8) | (uint)Eep_Read(EEP_MAX_UNLOCK_CNT_Addr1);
}

uchar Eep_Read(uint Addr)
{
	while(EECR & (1<<EEWE));

	EEAR = Addr;
	EECR |= (1<<EERE);
	delay_ms(1);

	return(EEDR);
}

void Eep_Write(uint Adr,uchar Val)
{
	while(EECR & (1<<EEWE));

	EEAR = Adr;
	EEDR = Val;
	EECR |= (1<<EEMWE);
	EECR |= (1<<EEWE);

	delay_ms(1);
}

