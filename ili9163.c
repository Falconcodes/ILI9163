/*******************************************************
*******************************************************/

#include <mega328p.h>
#include <spi.h>
#include <delay.h>
#include <ascii.h>
#include <ili9163.h>
#include <stdio.h>

unsigned int i;
unsigned char string[16] = "";

unsigned int pH=5;

void main(void)
{
CS=1;
RST=1;

// Input/Output Ports initialization
DDRB=(0<<DDB7) | (0<<DDB6) | (1<<DDB5) | (0<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (1<<PORTB1) | (0<<PORTB0);

DDRD.7=1;

// spi initialization Clock Rate: 4000,000 kHz MSB First
SPCR=(0<<SPIE) | (1<<SPE) | (0<<DORD) | (1<<MSTR) | (1<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);
SPSR=(1<<SPI2X);

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
lcd_com(0x11);

//настройка режима направления заполнения экрана и порядка R-G-B
lcd_com(0x36);
lcd_send(0b11001000);

lcd_com(0x3A);
lcd_send(0b01100101);

//lcd_com(0x3A);  //битность RGB 12-16-18
//lcd_send(0b00000110);
  
  DC=0;
  CS=0;
  spi(0x2C);                                                                                              
  CS=1;  
  DC=1;
  CS=0;
  for (i=0; i<24576; i++){        //16384 - для 18 бит, 12288 (24576) для 12 бит
  spi(0b00000100); //Red
  spi(0b00010100); //Green
  spi(0b01000100); //Blue
  }
  DC=0;
  CS=1; 
  
lcd_fill(2,0,0);

text_color(31,31,0);
bg_color(0,0,0);

while(1){
sprintf(string, "Hello! pH=%i", pH);
lcd_type(10, 1, string);
pH++;
delay_ms(100);
};

//while (1)
// {
//lcd_y_band(80, 110);
//lcd_fill(31, 1, 1);
// delay_ms(1000);
//lcd_y_band(20, 50);
//lcd_fill(31, 63, 31);
// delay_ms(1000);
//lcd_y_band(50, 80);
//lcd_fill(1, 1, 31);
// delay_ms(1000);
//lcd_x_band(0, 128);
//lcd_y_band(0, 128);
//lcd_fill(1,1,1);
//delay_ms(500);
// }
}
