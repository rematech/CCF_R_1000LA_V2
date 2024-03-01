#ifndef __UART_H__
#define __UART_H__

void Uart0_Init(void);
void Uart1_Init(void);

char Getchar0(void);
void Putchar0(uchar c);
void Putstr0(uchar *str);

char Getchar1(void);
void Putchar1(uchar c);
void Putstr1(uchar *str);

int printf(const char *format, ...);


#endif