/*******************************************************
*******************************************************/

#include <mega328p.h>
#include <spi.h>
#include <delay.h>
#include <ascii_ru.h>
#include <ru1251.h>
#include <ili9163.h>
#include <stdio.h>

unsigned int i;
unsigned char string[STRING_LENGHT];

unsigned int pH=5, time=0;

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
//нормальное положение экрана - стороной со штырьками вверх
lcd_com(0x36);
lcd_send(0b11101000);

//количество цветов (уст.65536 = 16 бит RGB)
lcd_com(0x3A);
lcd_send(0b01100101);

  
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
  
lcd_fill(1,1,1);

text_color(31,55,20);
bg_color(1,1,1);

//lcd_x_band(0,127);
//lcd_y_band(0,127);
//lcd_fill(1,30,1);

//sprintf(string, "Уст.pH=        ");
//lcd_typestring(1, 1, string);

lcd_test_typechar(175);
while(1);

string[1]='\0';
sprintf(string, "Уст.pH=     ");
lcd_type(0, 0, string);
sprintf(string, "Уст.t'=    C");
lcd_type(2, 0, string);
sprintf(string, "Тек.pH=     ");
lcd_type(1, 0, string);
sprintf(string, "Тек.t'=    С");
lcd_type(3, 0, string);
sprintf(string, "Время:      ");
lcd_type(4, 0, string);
sprintf(string, "Прогр.:    %%");
lcd_type(5, 0, string);

while(1){
string[1]='\0';
sprintf(string, "%i", time);
lcd_type(0, 8, string);
string[1]='\0';
sprintf(string, "%i", time);
lcd_type(1, 8, string);
string[1]='\0';
sprintf(string, "%i", time);
lcd_type(2, 8, string);
string[1]='\0';
sprintf(string, "%i", time);
lcd_type(3, 8, string);
string[1]='\0';
sprintf(string, "%i", time);
lcd_type(4, 7, string);
string[1]='\0';
sprintf(string, "%i", 23);
lcd_type(5, 8, string);
//pH++;
time++;
//delay_ms(1);
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
