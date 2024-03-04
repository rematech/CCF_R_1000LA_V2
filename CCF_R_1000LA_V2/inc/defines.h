#ifndef __DEFINES_H__
#define __DEFINES_H__

typedef signed char			schar;
typedef unsigned char		uchar;
typedef signed  int			sint;
typedef unsigned int		uint;
typedef signed long			slong;
typedef unsigned long		ulong;



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




//=============== Systen Menu Define ===========================================
#define SYS_INIT			0x01
#define SYS_BOOT_INIT		0x02
#define SYS_TOPMENU			0x04
#define SYS_SET_WAIT		0x05

#define SYS_REBOOT			0x0C
#define SYS_ERROR_REBOOT	0x0D

#define SYS_ERROR			0x0F

#define SYS_MAIN			0x10
#define SYS_SET_MENU		0x11


//=============== Systen Parameters Define =====================================
// Direction Select
#define REVERSE_SEL			0
#define FORWARD_SEL			1

// AGC Input Select
//#define DCV_AGC			6
//#define REVERSE_AGC			4
//#define DCV_AGC				4
#define REVERSE_AGC			6

#define FM_AGC				5
#define FORWARD_AGC			7

//=============== System Sub Define ============================================
#define SUB_MENU1			0
#define SUB_MENU2			1
#define SUB_MENU3			2
#define SUB_MENU4			3
#define SUB_MENU5			4
#define SUB_MENU6			5
#define SUB_MENU7			6
#define SUB_MENU8			7
#define SUB_MENU9			8
#define SUB_MENU10			9
#define SUB_MENU11			10
#define SUB_MENU12			11
#define SUB_MENU13			12
#define SUB_MENU14			13
#define SUB_MENU15			14
#define SUB_MENU16			15

#define RX_AGC_EN			1		//0
#define FM_RUN_EN			1

#define	WIRELESS_DEBUG_EN	0
#define FM_DEB_EN			0

#define MIN_UNLOCK_CNT		10		// 100 ms
#define MAX_UNLOCK_CNT		300		// 3000 ms
#define DEFAULT_UNLOCK_CNT	30		// 300 ms
////////////////////////////////////////////////////////////////




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
	bool	Debug_Det_Lvl_En;
	bool	Debug_Agc_Det_En;
	bool	Debug_Agc_Out_En;

	bool	Detect;
	bool	Agc_En;

	uint	Adc_Value;
	uchar	Att_Det_dB;
	uchar	Att_1st_dB;
	uchar	Att_2nd_dB;
	uchar	Att_3rd_dB;

	uint	Det_Level;
	uint	Agc_Det_Level;
	uint	Agc_Out_Level;

	uint	Unlock_Cnt;
} Wireless_Param;

typedef struct
{
	bool	Debug_Max_Unlock_Cnt_En;
	bool	Debug_Dsp_En;
	ulong	Debug_Flag;

	uchar	Version;

	uchar	WL_Check_Sel;
	uchar	Direction;

	uint	DCV_Value;

	uchar	Main_Flag;
	uchar	Main_Sub_Flag;

	uint	Max_Unlock_Cnt;
} System_Param;



#endif

