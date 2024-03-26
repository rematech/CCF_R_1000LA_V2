

/*
 * board.c
 *
 * Created: 2024-03-09 오후 1:44:55
 *  Author: jace
 */ 

#include "board.h"


void setSwitch_FWD1(BOOL bRF1)
{
	if(bRF1)
		SET_BIT(PORTE, 5);
	else
		CLEAR_BIT(PORTE, 5);
}

void setSwitch_FWD2(BOOL bRF1)
{
	if(bRF1)
		SET_BIT(PORTB, 3);
	else
		CLEAR_BIT(PORTB, 3);
}

void setSwitch_REV1(BOOL bRF1)
{
	if(bRF1)
		SET_BIT(PORTE, 6);
	else
		CLEAR_BIT(PORTE, 6);
}

void setSwitch_REV2(BOOL bRF1)
{
	if(bRF1)
		SET_BIT(PORTB, 4);
	else
		CLEAR_BIT(PORTB, 4);
}

void setLED_FWD(BOOL bLEDOn)
{
	if(!bLEDOn)
		SET_BIT(PORTF, 2);
	else
		CLEAR_BIT(PORTF, 2);
}

void setLED_REV(BOOL bLEDOn)
{
	if(!bLEDOn)
		SET_BIT(PORTF, 1);
	else
		CLEAR_BIT(PORTF, 1);
}

void setLED_FM(BOOL bLEDOn)
{
	if(!bLEDOn)
		SET_BIT(PORTF, 0);
	else
		CLEAR_BIT(PORTF, 0);
}

