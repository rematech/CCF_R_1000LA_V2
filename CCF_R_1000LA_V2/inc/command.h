#ifndef __COMMAND_H__
#define __COMMAND_H__


#if 0
#define DEBUG_FWD_DET_LVL_FLAG		0x00001
#define DEBUG_REV_DET_LVL_FLAG		0x00002
#define DEBUG_FWD_AGC_DET_FLAG		0x00004
#define DEBUG_REV_AGC_DET_FLAG		0x00008
#define DEBUG_FWD_AGC_OUT_FLAG		0x00010
#define DEBUG_REV_AGC_OUT_FLAG		0x00020
#define DEBUG_FM_ATT_FLAG			0x00040
#define DEBUG_UP_FLAG				0x00080
#define DEBUG_DOWN_FLAG				0x00100
#define DEBUG_DSP_START_FLAG		0x00200
#define DEBUG_DSP_PAUSE_FLAG		0x00400
#define DEBUG_ALL_ATT_0dB_FLAG		0x00800
#define DEBUG_ALL_ATT_10dB_FLAG		0x01000
#define DEBUG_CLEAR_FLAG			0x02000
#define DEBUG_INIT_FLAG				0x04000
#define DEBUG_HELP_FLAG				0x08000
#define DEBUG_PATH_OPEN_FLAG		0x10000
#define DEBUG_MAX_UNLOCK_CNT_FLAG	0x20000

void Command_Check(void);
void Debug_Forward_Det_Level(void);
void Debug_Reverse_Det_Level(void);
void Debug_Forward_Agc_Det(void);
void Debug_Reverse_Agc_Det(void);
void Debug_Forward_Agc_Out(void);
void Debug_Reverse_Agc_Out(void);
void Debug_FM_Att(void);
void Debug_Fwd_Det_Level_UpDown(uchar updown);
void Debug_Rev_Det_Level_UpDown(uchar updown);
void Debug_Fwd_Agc_Det_UpDown(uchar updown);
void Debug_Rev_Agc_Det_UpDown(uchar updown);
void Debug_Fwd_Agc_Out_UpDown(uchar updown);
void Debug_Rev_Agc_Out_UpDown(uchar updown);
void Debug_FM_Att_UpDown(uchar updown);
void Debug_Max_Unlock_Cnt_UpDown(uchar updown);
void Debug_All_Att(uchar dB);
void Debug_Display(uchar dsp);
void Debug_Clear(void);
void Factory_Init(void);
void Debug_Help_Dsp(void);
void Agc_Display(void);
void Debug_Path_Open(void);
#endif






#define USART1_P_STARTCODE			'S'
#define USART1_P_ENDCODE			'E'
#define USART1_MAX_BUF				20

typedef struct strUartProtocol
{
	union
	{
		uchar ucCmdBuf[USART1_MAX_BUF];
		struct
		{
			uchar ucStartCode;
			uchar ucCommand;
			uint uiData;
			uchar ucEndCode;
		} pa;
	};
	
	uchar ucRecieveCount;

	
} STR_UART_PROTOCOL;
extern STR_UART_PROTOCOL g_uart;

////////////////////////////////////////////////////
#define __U1CMD__HELP_					'H'
#define __U1CMD__SET_FWD_				'A'
#define __U1CMD__SET_REV_				'B'
#define __U1CMD__SET_FM_				'F'

// Undetect threshold offset
#define __U1CMD__SET_FWD_UTO_			'U'
#define __U1CMD__SET_REV_UTO_			'D'

#define __U1CMD__SET_DIRECTION_SW		'X'
#define __U1CMD__MAX_UNLOCK_COUNT		'C'
#define __U1CMD__MAX_LOCK_COUNT			'L'

#define __U1CMD__PRINT_EN				'P'
#define __U1CMD__PRINT_DIS				'S'
#define __U1CMD__DEBUG_RESET			'Q'
#define __U1CMD__F_INIT					'I'
#define __U1CMD__PRINT_EEPROM			'R'

#define __U1CMD__FORCE_FWD				'Y'
#define __U1CMD__FORCE_REV				'Z'


////////////////////////////////////////////////////

typedef enum 
{
	USART1__STARTCODE,
	USART1__CMD,
	USART1__NUM_1,
	USART1__NUM_2,
	USART1__NUM_3,
	USART1__NUM_4,
	USART1__ENDCODE,

	USART1__COUNT
} USART1_PROTOCOL;
	

void USART1_InitialData();

 
void CommandProcess();
void PrintParameter();


#endif
