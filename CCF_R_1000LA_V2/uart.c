/**************************************************
  Prototypes for USART functions
***************************************************/

#include "board.h"

#define U2XN0 1
#define U2XN1 1

// Clock [Hz]
#define FCLK (double)16000000

// Baud rate
#define BAUD0 (double)115200
#define BAUD1 (double)115200

#ifdef UBRR0
#undef UBRR0
#endif

#ifdef UBRR1
#undef UBRR1
#endif

// Calculate the UBRR0 setting
#if (U2XN0)
#define UBRR0 ((uint) (FCLK/(8*BAUD0) - 1))
#else
#define UBRR0 ((uint) (FCLK/(16*BAUD0) - 1))
#endif

// Calculate the UBRR1 setting
#if (U2XN1)
#define UBRR1 ((uint) (FCLK/(8*BAUD1) - 1))
#else
#define UBRR1 ((uint) (FCLK/(16*BAUD1) - 1))
#endif

/*****************************************************************************
*
*   Function name : USART_Init
*
*   Returns :       None
*
*   Parameters :    uint baudrate
*
*   Purpose :       Initialize the USART
*
*****************************************************************************/

//UART0 initialize
// desired baud rate: 115200
// actual: baud rate:117647 (2.1%)
// char size: 8 bit
// parity: Disabled
void Uart0_Init(void)
{
	UCSR0B = 0x00; //disable while setting baud rate
	UCSR0A = (U2X0 << 1);
	UCSR0C = 0x06;
	UBRR0H = (uchar)(UBRR0 >> 8); //set baud rate hi
	UBRR0L = (uchar)(UBRR0 & 0xFF); //set baud rate lo
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0); // set receiver, transmitter enable, set Rx complete interrupt receiver
}

// Get a character from the USART0 Receiver
char Getchar0(void)
{
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

// Write a character to the USART0 Transmitter
void Putchar0(uchar c)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}

void Putstr0(uchar *str)
{
 	uchar i = 0;
 	do{
		Putchar0(str[i]) ;
   	}while(str[++i] != 0x00);	//null=0x00
}

//UART1 initialize
// desired baud rate: 115200
// actual: baud rate:117647 (2.1%)
// char size: 8 bit
// parity: Disabled
void Uart1_Init(void)
{
	UCSR1B = 0x00; //disable while setting baud rate
	UCSR1A = (U2X1 << 1);
	UCSR1C = 0x06;
	UBRR1H = (uchar)(UBRR1 >> 8); //set baud rate hi
	UBRR1L = (uchar)(UBRR1 & 0xFF); //set baud rate lo
	UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1); // set receiver, transmitter enable, set Rx complete interrupt receiver
}

// Get a character from the USART0 Receiver
char Getchar1(void)
{
	while (!(UCSR1A & (1 << RXC1)));
	return UDR1;
}

// Write a character to the USART0 Transmitter
void Putchar1(uchar c)
{
	while (!(UCSR1A & (1 << UDRE1)));
	UDR1 = c;
}

void Putstr1(uchar *str)
{
 	uchar i = 0;
 	do{
		Putchar1(str[i]) ;
   	}while(str[++i] != 0x00);	//null=0x00
}

//*****************************************************************************
//*************************    UART End    ***********************************
//*****************************************************************************
#if 0
static void put_one_char(char c, void *dummy)
{
  Putchar1 (c);
  (void)dummy;  /* Warning on this line OK (Optimized Away) */
}
#endif

char g_ucPrintBuf[256];
int printf(const char *format, ...)                    /* Our main entry */
{
#if 1
	va_list args;

	va_start(args,format);
	vsprintf(g_ucPrintBuf,format,args);
	va_end(args);

	Putstr1((unsigned char*)g_ucPrintBuf);

	return 0;
#else
	va_list args;
	int i;
	int count;

	va_start(args,format);
	vsprintf(g_ucPrintBuf,format,args);
	va_end(args);
	
	count = sizeof(g_ucPrintBuf);

	for( i=0; i<count; i++)
		Putchar1(g_ucPrintBuf[i]);

	return count;
#endif
}

