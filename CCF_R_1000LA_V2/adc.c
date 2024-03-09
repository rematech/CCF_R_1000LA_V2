#include "board.h"

void Adc_Init(void)
{
	ADCSRA = ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));				// 16MHz/128 = 125KHz the ADC reference clock
//	ADCSRA = ((1<<ADATE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));		// ADC Auto Trigger Enable, 16MHz/128 = 125KHz the ADC reference clock
	ADMUX = (1<<REFS0);											// Voltage reference from Avcc
	ADCSRA |= (1<<ADEN);										// ADC Enable
}

uint Agc_Read(uchar channel)
{
	uchar loop;
	uint result;

//	ADMUX &= 0xF0;												// Clear the older channel that was read
	ADMUX &= 0xE0;												// Clear the older channel that was read
	ADMUX |= channel;											// Defines the new ADC channel to be read
	delay_us(10);

	ADCSRA |= ((1<<ADIF)|(1<<ADSC));							// Monitor end of conversion interrupt, Starts a new conversion
	while(!(ADCSRA&(1<<ADIF)));									// Monitor end of conversion interrupt
//	while(ADCSRA & (1<<ADSC));									// Wait until the conversion is done
	delay_us(10);

	result = 0;
	for (loop=0; loop<16; loop++)
	{
		ADCSRA |= ((1<<ADIF)|(1<<ADSC));						// Monitor end of conversion interrupt, Starts a new conversion
		while(!(ADCSRA&(1<<ADIF)));								// Monitor end of conversion interrupt
//		while(ADCSRA & (1<<ADSC));								// Wait until the conversion is done

		result += (uint)ADCL;
		result += ((uint)ADCH << 8);
		delay_us(10);
	}

	result >>= 4;

	return result;												// Returns the ADC value of the chosen channel
}

void AGC_All_Read(void)
{
	Fwd.Adc_Value = Agc_Read(FORWARD_AGC);
	Rev.Adc_Value = Agc_Read(REVERSE_AGC);

	FM.Adc_Value = Agc_Read(FM_AGC);
}

