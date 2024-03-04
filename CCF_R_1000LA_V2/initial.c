#include "inc/board.h"


void Init_MCU(void)
{
	// Timer/Counter 0 initialization
	TCCR0 = 0x00;
	TCNT0 = 0x00;
	OCR0 = 0x00;

	// Timer/Counter 1 initialization
	TCCR1A = 0x00;
	TCCR1B = 0x00;
	TCNT1H = 0x00;
	TCNT1L = 0x00;
	OCR1AH = 0x00;
	OCR1AL = 0x00;
	OCR1BH = 0x00;
	OCR1BL = 0x00;

	// External Interrupt(s) initialization
	MCUCR = 0x00;
	MCUCSR = 0xA0;
	EICRB = 0x00;

	// External SRAM page configuration:
	ACSR = 0x80;
	TIMSK = 0x00; 	// timer interrupt sources

	//============================== PORT Setting ==============================
	/*

	DDRA = 0xFF;			//PORTA(00000000)
							//		BIT7 - FM ATT 2nd LE
							//		BIT6 - FM ATT 1st LE
							//		BIT5 - Reverse ATT 3rd LE
							//		BIT4 - Reverse ATT 2nd LE
							//		BIT3 - Reverse ATT 1st LE
							//		BIT2 - Forward ATT 3rd LE
							//		BIT1 - Forward ATT 2nd LE
							//		BIT0 - Forward ATT 1st LE

	DDRB = 0x03;			//PORTB(11111111)
							//		BIT7 - Reserved
							//		BIT6 - Reserved
							//		BIT5 - Reserved
							//		BIT4 - Reserved
							//		BIT3 - Reserved
							//		BIT2 - Reserved
							//		BIT1 - SCK
							//		BIT0 - SS (Reserved)

	DDRC = 0xC3;			//PORTC(00111111)
							//		BIT7 - Reverse Detect ATT LE
							//		BIT6 - Wireless Direction Select
							//		BIT5 - Up Key
							//		BIT4 - Down Key
							//		BIT3 - Menu Key
							//		BIT2 - Enter Key
							//		BIT1 - Wireless Output Mute1
							//		BIT0 - Wireless Output Mute0

	DDRD = 0xCB;			//PORTD(00111111)
							//		BIT7 - ATT Data
							//		BIT6 - ATT Clock
							//		BIT5 - Reserved
							//		BIT4 - Reserved
							//		BIT3 - Uart1 Tx
							//		BIT2 - Uart1 Rx
							//		BIT1 - I2C SDA (Reserved)
							//		BIT0 - I2C SCL (Reserved)

	DDRE = 0x01;			//PORTE(11111111)
							//		BIT7 - Reserved
							//		BIT6 - Reserved
							//		BIT5 - Reserved
							//		BIT4 - Reserved
							//		BIT3 - Reserved
							//		BIT2 - Reserved
							//		BIT1 - MISO
							//		BIT0 - MOSI

	DDRF = 0x0F;			//PORTF(11111111)
							//		BIT7 - AGC Forward
							//		BIT6 - AGC Reverse
							//		BIT5 - AGC FM
							//		BIT4 - AGC Power
							//		BIT3 - Power LED
							//		BIT2 - Forward Detect LED
							//		BIT1 - Reverse Detect LED
							//		BIT0 - FM Detect LED

	DDRG = 0x07;			//PORTG(11111011)
							//		BIT7 - N.C
							//		BIT6 - N.C
							//		BIT5 - N.C
							//		BIT4 - Reserved
							//		BIT3 - Reserved
							//		BIT2 - Forward Detect ATT LE
							//		BIT1 - Wireless Output Mute3
							//		BIT0 - Wireless Output Mute2
	*/

	// Port A
	PORTA = 0x00;
	DDRA  = 0xFF;

	// Port B
	PORTB = 0x3F;           // 0xFF
	DDRB  = 0x1B;

	// Port C
	PORTC = 0x3C;
	DDRC  = 0xC3;

	// Port D
	PORTD = 0x3F;
	DDRD  = 0xCB;

	// Port E
	PORTE = 0xFF;
	DDRE  = 0x61;

	// Port F
	//PORTF = 0x0F;
	//PORTF = 0x07;
	DDRF  = 0x07;

	// Port G
	PORTG = 0xF8;
	DDRG  = 0x07;

	// Function Initialized
	Timer0_Init();
	Uart1_Init();
	Adc_Init();

	RF_Level_Init();

	SEI;	//re-enable interrupts

	//all peripherals are now initialized
}

void Init_System(void)
{
	FWD_LED_OFF;
	REV_LED_OFF;
	FM_LED_OFF;

	printf("\n\n\rSystem>> CCF-1000LA Init...\n\n\r");

	Wireless_Mute(WL_MUTE_ON);
	
}





