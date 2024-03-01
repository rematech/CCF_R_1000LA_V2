
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


