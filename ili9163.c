/*******************************************************
*******************************************************/

#include <mega328p.h>
#include <spi.h>
#include <delay.h>
#include <ili9163.h>

unsigned int i;

void main(void)
{
CS=1;
RST=1;

// Input/Output Ports initialization
DDRB=(0<<DDB7) | (0<<DDB6) | (1<<DDB5) | (0<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (1<<PORTB1) | (0<<PORTB0);

DDRD.7=1;

// SPI initialization Clock Rate: 4000,000 kHz MSB First
SPCR=(0<<SPIE) | (1<<SPE) | (0<<DORD) | (1<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);
SPSR=(0<<SPI2X);

//аппаратный сброс
RST=0;
delay_ms(10);
RST=1;
delay_ms(10);

//display-on
CS=0;
spi(0x29);
CS=1;

//sleep-out
CS=0;
spi(0x11);
CS=1;

//настройка режима направления заполнения экрана и порядка R-G-B
lcd_com(0x36);
lcd_send(0b11001000);

lcd_com(0x3A);
lcd_send(0b01100110);
  
  DC=0;
  CS=0;
  spi(0x2C);                                                                                              
  CS=1;  
  DC=1;
  CS=0;
  for (i=0; i<16384; i++){
  spi(0b00000100); //Red
  spi(0b00000100); //Green
  spi(0b00000100); //Blue
  }
  DC=0;
  CS=1;
  //lcd_com(0x21);
  
delay_us(10);

while (1)
 {
 //lcd_com(0x10);
 lcd_fill(4, 4, 4);
 //lcd_com(0x11);
 delay_ms(1000);
 lcd_fill(56, 56, 56);
 delay_ms(1000);
 lcd_fill(56, 0, 0);
 delay_ms(1000);
 }
}
