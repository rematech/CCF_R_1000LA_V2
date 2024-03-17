#ifndef __EEPROM_H__
#define __EEPROM_H__


#if 0
// EEPROM Define
#define EEP_1st_Addr							0x000
#define EEP_Ver_Addr							0x001

#define EEP_WIRELESS_FWD_DET_LEVEL_Addr0		0x010
#define EEP_WIRELESS_FWD_DET_LEVEL_Addr1		0x011
#define EEP_WIRELESS_FWD_AGC_DET_LEVEL_Addr0	0x012
#define EEP_WIRELESS_FWD_AGC_DET_LEVEL_Addr1	0x013
#define EEP_WIRELESS_FWD_AGC_OUT_LEVEL_Addr0	0x014
#define EEP_WIRELESS_FWD_AGC_OUT_LEVEL_Addr1	0x015

#define EEP_WIRELESS_REV_DET_LEVEL_Addr0		0x020
#define EEP_WIRELESS_REV_DET_LEVEL_Addr1		0x021
#define EEP_WIRELESS_REV_AGC_DET_LEVEL_Addr0	0x022
#define EEP_WIRELESS_REV_AGC_DET_LEVEL_Addr1	0x023
#define EEP_WIRELESS_REV_AGC_OUT_LEVEL_Addr0	0x024
#define EEP_WIRELESS_REV_AGC_OUT_LEVEL_Addr1	0x025

#define EEP_FM_AGC_LEVEL_Addr0					0x030
#define EEP_FM_AGC_LEVEL_Addr1					0x031

#define EEP_MAX_UNLOCK_CNT_Addr0				0x040
#define EEP_MAX_UNLOCK_CNT_Addr1				0x041

#define EEP_1st_DATA							0xA5
#endif





void Eep_1st_Write(void);
void Eep_Data_Read(void);
void Eep_Write(uint addr, uchar data);
uchar Eep_Read(uint addr);


void eeprom_write_All();
bool eeprom_read_All(EEPROM_MAP *data) ;


#endif
