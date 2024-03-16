#include "board.h"

void ADC_Init(void)
{
	ADCSRA = ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));				// 16MHz/128 = 125KHz the ADC reference clock
//	ADCSRA = ((1<<ADATE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));		// ADC Auto Trigger Enable, 16MHz/128 = 125KHz the ADC reference clock
	ADMUX = (1<<REFS0);											// Voltage reference from Avcc
	ADCSRA |= (1<<ADEN);										// ADC Enable
}

uint ADC_Read(uchar channel)
{
	uchar loop;
	uint result;

//	ADMUX &= 0xF0;												// Clear the older channel that was read
	ADMUX &= 0xE0;												// Clear the older channel that was read
	ADMUX |= channel;											// Defines the new ADC channel to be read
	_delay_us(10);

	ADCSRA |= ((1<<ADIF)|(1<<ADSC));							// Monitor end of conversion interrupt, Starts a new conversion
	while(!(ADCSRA&(1<<ADIF)));									// Monitor end of conversion interrupt
//	while(ADCSRA & (1<<ADSC));									// Wait until the conversion is done
	_delay_us(10);

	result = 0;
	for (loop=0; loop<16; loop++)
	{
		ADCSRA |= ((1<<ADIF)|(1<<ADSC));						// Monitor end of conversion interrupt, Starts a new conversion
		while(!(ADCSRA&(1<<ADIF)));								// Monitor end of conversion interrupt
//		while(ADCSRA & (1<<ADSC));								// Wait until the conversion is done

		result += (uint)ADCL;
		result += ((uint)ADCH << 8);
		_delay_us(10);
	}

	result >>= 4;

	return result;												// Returns the ADC value of the chosen channel
}

void ADC_All_Read(void)
{
	g_Data.readADC.FWD = ADC_Read(_ADCPORT_FWD_);
	g_Data.readADC.REV = ADC_Read(_ADCPORT_REV_);
	g_Data.readADC.FM = ADC_Read(_ADCPORT_FM_);

	g_Data.readADC.FWD2_AMP = ADC_Read(_ADCPORT_FWD2_AMP);
	g_Data.readADC.REV2_AMP = ADC_Read(_ADCPORT_REV2_AMP);
}

