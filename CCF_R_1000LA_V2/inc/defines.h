#ifndef __DEFINES_H__
#define __DEFINES_H__

typedef signed char			schar;
typedef unsigned char		uchar;
typedef signed  int			sint;
typedef unsigned int		uint;
typedef signed long			slong;
typedef unsigned long		ulong;
typedef bool BOOL;

#define CLI					SREG &= ~Bit7;
#define SEI					SREG |= Bit7;

#define Bit0				0x01
#define Bit1				0x02
#define Bit2				0x04
#define Bit3				0x08
#define Bit4				0x10
#define Bit5				0x20
#define Bit6				0x40
#define Bit7				0x80





// System Timer
typedef struct
{
	uchar	Flag_10ms		:1;
	uchar	Flag_20ms		:1;
	uchar	Flag_50ms		:1;
	uchar	Flag_100ms		:1;
	uchar	Flag_250ms		:1;
	uchar	Flag_500ms		:1;
	uchar	Flag_1000ms		:1;
	uint	Count_10ms;
} SysTime_Param;




typedef struct
{
	struct 
	{
		uint FWD;
		uint REV;
		uint FM;
		//uint FM_Range;

		uint FWD2_AMP;
		uint REV2_AMP;
	} detectLevel;

	struct
	{
		uint FWD;
		uint REV;
	} uto;	//undetect threshold reduce offset

	uint uiLock_count;			// 
	uint uiUnlock_count;		// default : 2

	uint uiSWVersion;
	uchar uc1stCheck;

	uchar ucChecksum;


} EEPROM_MAP;

typedef enum
{
	CM_REV,
	CM_FWD,
} CHECK_MODE;
	
typedef struct 
{

	uchar ucCurrentCheckMode;

	struct
	{
		uchar FWD;
		uchar REV;
	} detect_status;
	
	struct
	{
		uchar FWD;
		uchar REV;
	} undetectCount;
	
	struct
	{
		uchar FWD;
		uchar REV;
	} detectCount;
	
	struct
	{
		uint FWD;
		uint REV;
		uint FM;
		uint FWD2_AMP;
		uint REV2_AMP;
		
	} readADC;

	uchar ucDebug;
	uchar ucPrint;
	uchar ucForceFWD;
	uchar ucForceREV;
	////EEPROM MAP START
	EEPROM_MAP eep;

#if 0 
	struct 
	{
		uint FWD;
		uint REV;
		uint FM;
		uint FM_Range;

		uint FWD2_AMP;
		uint REV2_AMP;
	} detectLevel;

	struct
	{
		uint FWD;
		uint REV;
	} uto;	//undetect threshold reduce offset

	struct
	{
		uint FWD;
		uint REV;
	} unlockCount;

	uint uiLock_count;
	uint uiUnlock_count;
#endif

	////EEPROM MAP END
} GlobalData;
extern GlobalData g_Data;






#endif

