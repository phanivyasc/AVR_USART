#include <avr/io.h> 
#include <stdio.h>
#include <avr/pgmspace.h>
#include <string.h>
#include "lcd_lib.h"
 
#ifndef F_CPU //define cpu clock speed if not defined
#define F_CPU 8000000
#endif

#define BAUDRATE 9600
#define UBRRVAL ((F_CPU/(BAUDRATE*16UL))-1)
int Uart_PutChar (char c, FILE *stream);
FILE uart_str = FDEV_SETUP_STREAM(Uart_PutChar, NULL, _FDEV_SETUP_WRITE);

void USART_Init(void)
{	               
UBRRL=UBRRVAL;		
UBRRH=(UBRRVAL>>8);	
UCSRC=(1<<URSEL)|(0<<UMSEL)|(0<<UPM1)|(0<<UPM0)|(0<<USBS)|(0<<UCSZ2)|(1<<UCSZ1)|(1<<UCSZ0);			
UCSRB=(1<<TXEN);
}

int Uart_PutChar (char c, FILE *stream)
 { 
    if (c == '\n')
    Uart_PutChar('\r', stream);
    loop_until_bit_is_set(UCSRA,UDRE); 
    UDR = c; 
    return 0; 
 }


int main(void)
{

USART_Init();
stdout=&uart_str;
LCDinit();
LCDclr();
LCDstring("USART",5);
while(1)	
{
printf("hi\n");
}	
return 0;
}
