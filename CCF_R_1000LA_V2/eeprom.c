#include "board.h"
#include <avr/eeprom.h>

uchar calculateChecksum(EEPROM_MAP *data);

void Eep_1st_Write(void)
{

#if 0
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
#endif
}

void Eep_Data_Read(void)
{
#if 0
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
#endif
}

uchar Eep_Read(uint Addr)
{
#if 0
	eeprom_read_block(void * __dst, const void * __src, size_t __n)
#else
	while(EECR & (1<<EEWE));

	EEAR = Addr;
	EECR |= (1<<EERE);
	delay_ms(1);

	return(EEDR);
#endif
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



void eeprom_write_bytes(uint16_t address, uint8_t* data, uint16_t length) 
{
    for (uint16_t i = 0; i < length; i++) {
        eeprom_write_byte((uint8_t*)(address + i), data[i]);
    }
}

void eeprom_read_bytes(uint16_t address, uint8_t* data, uint16_t length)
{
    for (uint16_t i = 0; i < length; i++) {
        data[i] = eeprom_read_byte((uint8_t*)(address + i));
    }
}

void eeprom_write_All()
{
	g_Data.eep.ucChecksum = calculateChecksum(&g_Data.eep);

	eeprom_write_bytes(0, (uint8_t*)&g_Data.eep, sizeof(EEPROM_MAP));
}

bool eeprom_read_All(EEPROM_MAP *data) 
{
	uchar ucChecksum;
	EEPROM_MAP *eeprom_data_ptr;
	
	
    eeprom_data_ptr = (EEPROM_MAP *)0;

    for (size_t i = 0; i < sizeof(EEPROM_MAP); ++i) {
        ((uchar *)data)[i] = eeprom_read_byte((uchar *)(eeprom_data_ptr) + i);
    }

	ucChecksum = calculateChecksum(data);

	if(data->uiSWVersion != Main_SW_VER)
	{
		printf("SW Version Diff!!");
		return 0;
	}

	if(ucChecksum != data->ucChecksum)
	{
		printf("eeprom checksum error!!");
		return 0;
	}
	
	printf("eeprom checksum ok!!");
	return 1;
	
}

uchar calculateChecksum(EEPROM_MAP *data)
{
    unsigned char *ptr = (unsigned char *)data;
    data->ucChecksum = 0;

    for (size_t i = 0; i < sizeof(EEPROM_MAP)-1; ++i)
	{
        data->ucChecksum ^= ptr[i];
    }

	return data->ucChecksum;
}

uchar readChecksumFromEEPROM()
{
	EEPROM_MAP *eeprom_data_ptr;
	uchar ucChecksum;
	
	eeprom_data_ptr = (EEPROM_MAP *)0;
	ucChecksum = eeprom_read_byte(&eeprom_data_ptr->ucChecksum);

	return ucChecksum;
}
