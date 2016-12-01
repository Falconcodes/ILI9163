/*******************************************************
*******************************************************/

#include <mega328p.h>
#include <spi.h>

//Подключения
#define DC  PORTB.0  // A0 pin
#define RST PORTB.1
#define CS  PORTB.2


void main(void)
{

// Input/Output Ports initialization
DDRB=(0<<DDB7) | (0<<DDB6) | (1<<DDB5) | (0<<DDB4) | (1<<DDB3) | (1<<DDB2) | (0<<DDB1) | (0<<DDB0);
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// SPI initialization Clock Rate: 4000,000 kHz MSB First
SPCR=(0<<SPIE) | (1<<SPE) | (0<<DORD) | (1<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);
SPSR=(0<<SPI2X);

while (1)
      {


      }
}
