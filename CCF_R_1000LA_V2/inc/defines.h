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
	uint uiSWVersion;
	
	struct
	{
		uint FWD;
		uint REV;
		uint FM;
	} readADC;

	struct 
	{
		uint FWD;
		uint REV;
		uint FM;
	} detectLevel;

	uint uiLock_count;
	uint uiUnlock_count;

	
} GlobalData;
extern GlobalData g_Data;



#endif

