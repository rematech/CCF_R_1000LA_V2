#ifndef __INITIAL_H__
#define __INITIAL_H__




// PORT의 비트를 설정하는 매크로
#define SET_BIT(port, bit) 				(port |= (1 << bit))

// PORT의 비트를 지우는 매크로
#define CLEAR_BIT(port, bit) 			(port &= ~(1 << bit))





#if 0
// Direction Select
//#define DIRECTION_REVERSE		PORTC &= ~Bit6
//#define DIRECTION_FORWARD		PORTC |= Bit6

#define FWD_DIRECTION_SW1_LOW	PORTB &= ~Bit3
#define FWD_DIRECTION_SW1_HIGH	PORTB |= Bit3
#define REV_DIRECTION_SW1_LOW	PORTB &= ~Bit4
#define REV_DIRECTION_SW1_HIGH	PORTB |= Bit4

#define FWD_DIRECTION_SW2_LOW	PORTE &= ~Bit5
#define FWD_DIRECTION_SW2_HIGH	PORTE |= Bit5
#define REV_DIRECTION_SW2_LOW	PORTE &= ~Bit6
#define REV_DIRECTION_SW2_HIGH	PORTE |= Bit6

// ATT Signals
#define FWD_ATT_DET_LE_LOW		PORTG &= ~Bit2
#define FWD_ATT_DET_LE_HIGH		PORTG |= Bit2

#define FWD_ATT_1st_LE_LOW		PORTA &= ~Bit0
#define FWD_ATT_1st_LE_HIGH		PORTA |= Bit0

#define FWD_ATT_2nd_LE_LOW		PORTA &= ~Bit1
#define FWD_ATT_2nd_LE_HIGH		PORTA |= Bit1

#define FWD_ATT_3rd_LE_LOW		PORTA &= ~Bit2
#define FWD_ATT_3rd_LE_HIGH		PORTA |= Bit2

#define REV_ATT_DET_LE_LOW		PORTC &= ~Bit7
#define REV_ATT_DET_LE_HIGH		PORTC |= Bit7

#define REV_ATT_1st_LE_LOW		PORTA &= ~Bit3
#define REV_ATT_1st_LE_HIGH		PORTA |= Bit3

#define REV_ATT_2nd_LE_LOW		PORTA &= ~Bit4
#define REV_ATT_2nd_LE_HIGH		PORTA |= Bit4

#define REV_ATT_3rd_LE_LOW		PORTA &= ~Bit5
#define REV_ATT_3rd_LE_HIGH		PORTA |= Bit5

#define FM_ATT_1st_LE_LOW		PORTA &= ~Bit6
#define FM_ATT_1st_LE_HIGH		PORTA |= Bit6

#define FM_ATT_2nd_LE_LOW		PORTA &= ~Bit7
#define FM_ATT_2nd_LE_HIGH		PORTA |= Bit7

#define ATT_SCK_LOW				PORTD &= ~Bit6
#define ATT_SCK_HIGH			PORTD |= Bit6

#define ATT_DOUT_LOW			PORTD &= ~Bit7
#define ATT_DOUT_HIGH			PORTD |= Bit7

// Wireless Output Mute
#define WL_OUT_MUTE0_LOW		PORTC &= ~Bit0
#define WL_OUT_MUTE0_HIGH		PORTC |= Bit0
#define WL_OUT_MUTE1_LOW		PORTC &= ~Bit1
#define WL_OUT_MUTE1_HIGH		PORTC |= Bit1
#define WL_OUT_MUTE2_LOW		PORTG &= ~Bit0
#define WL_OUT_MUTE2_HIGH		PORTG |= Bit0
#define WL_OUT_MUTE3_LOW		PORTG &= ~Bit1
#define WL_OUT_MUTE3_HIGH		PORTG |= Bit1


// ADC Signals
#define FWD_ADC					(PINF&Bit7)
#define REV_ADC					(PINF&Bit6)
#define FM_ADC					(PINF&Bit5)
//#define POWER_ADC				(PINF&Bit4)

// LED
//#define POWER_LED_OFF 			PORTF |= Bit3
//#define POWER_LED_ON			PORTF &= ~Bit3

#define FWD_LED_OFF 			PORTF |= Bit2
#define FWD_LED_ON				PORTF &= ~Bit2

#define REV_LED_OFF 			PORTF |= Bit1
#define REV_LED_ON				PORTF &= ~Bit1

#define FM_LED_OFF 				PORTF |= Bit0
#define FM_LED_ON				PORTF &= ~Bit0


// AGC Ground
#define FWD_SET_GND				PORTB &= ~Bit7
#define REV_SET_GND				PORTB &= ~Bit6

#endif


void Init_MCU(void);
void Init_System(void);
void Factory_Reset_Data(void);


#endif
