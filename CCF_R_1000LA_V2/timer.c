


#include "board.h"


#define CLK					16000000
#define PRESCALE			1024
#define TIME_MS				10			// 10ms
#define TIMER0_CNT			(uchar)(0xFF - (uchar)(((ulong)CLK * (ulong)TIME_MS) / ((ulong)PRESCALE * (ulong)1000)))

void Timer0_Init(void)
{
    // 8-bit Fast PWM 모드 설정
	TCCR0 = ((1 << CS02) | (1 << CS01) | (1 << CS00));
    // 클럭 분주비 64 설정
    TCCR0 |= (1 << CS01) | (1 << CS00);
    // Timer0 오버플로우 인터럽트 허용
    TIMSK |= (1 << TOIE0);
    // 초기 TCNT0 값 설정
    TCNT0 = TIMER0_CNT;
    // 전역 인터럽트 허용
    sei();
//		CLI;


}

void TIMER0_OVF_interrupt(void)
{
	cli();

	TIMSK &= ~(1 << TOIE0);

	Systime.Flag_10ms = 1;
	Systime.Count_10ms++;

	if((Systime.Count_10ms % 2) == 0) 
		Systime.Flag_20ms = 1;
	
	if((Systime.Count_10ms % 5) == 0)
		Systime.Flag_50ms = 1;
	
	if((Systime.Count_10ms % 10) == 0) 
		Systime.Flag_100ms = 1;
	
	if((Systime.Count_10ms % 25) == 0)
		Systime.Flag_250ms = 1;
	
	if((Systime.Count_10ms % 50) == 0)
		Systime.Flag_500ms = 1;
	
	if(Systime.Count_10ms == 100) 
	{
		Systime.Flag_1000ms = 1;
		Systime.Count_10ms = 0;
	}

	TCNT0 = TIMER0_CNT;
	TIFR |= (1 << TOV0);
	TIMSK |= (1 << TOIE0);

	sei();
}


ISR(TIMER0_OVF_vect)
{
	TIMER0_OVF_interrupt();
}



////////////////////////////////////delay
#if 0
void delay_us(uint us)
{
 	uint i;

	for(i = 0; i < us; i++)	  // 4 cycle
	{
 		asm("PUSH R0");		  // 2 cycle
		asm("POP R0");		  // 2 cycle
		asm("PUSH R0");		  // 2 cycle
		asm("POP R0");		  // 2 cycle
 		asm("PUSH R0");		  // 2 cycle
		asm("POP R0");		  // 2 cycle
	}
}
#endif

void delay_ms(uint ms)
{
 	uint i;

	for(i = 0; i < ms; i++)
		_delay_us(1000);
}

void delay_sec(uint sec)
{
 	uint i;

	for(i = 0; i < sec; i++)
		_delay_ms(1000);
}



