/*******************************************************
*******************************************************/

#define CHAR_ARRAY_NAME verd_14
#define BYTES_PER_CHAR 29  //ширина массива с растровым шрифтом, подключаемого ниже include-ом
#define CHAR_HEIGHT 14//высота символа в пикселях...
#define CHAR_WIGHT 14  // ... и его ширина

#include <mega328p.h>
#include <spi.h>
#include <delay.h>
#include <stdio.h>
#include <verd_14.h>

#include <ili9163.h>


unsigned int i;
unsigned char string[16];

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

text_color(20,20,5);
bg_color(1,1,2);

////lcd_test_typechar(5);
//sprintf(string, "                ");
////while(1);
//sprintf(string, "Уст. pH = 5.24");
//lcd_test_typechar(string[0]-30);
//lcd_type(3, 0, string);


sprintf(string, "Уст. рН=");
lcd_type(0, 0, string);
sprintf(string, "Тек. pH=");
lcd_type(1, 0, string);
sprintf(string, "Уст. t'=      *С");
lcd_type(2, 0, string);
sprintf(string, "Тек. t'=      *С");
lcd_type(3, 0, string);
sprintf(string, "Время:");
lcd_type(4, 0, string);
sprintf(string, "Прогр.:");
lcd_type(5, 0, string);
sprintf(string, "Еще 1:");
lcd_type(6, 0, string);
sprintf(string, "Еще 2:");
lcd_type(7, 0, string);
sprintf(string, "Еще 3:");
lcd_type(8, 0, string);

while(1){
sprintf(string, "%i ", time);
lcd_type(0, 9, string);
//sprintf(string, "%i ", time);
lcd_type(1, 9, string);
//sprintf(string, "%i ", time);
lcd_type(2, 8, string);
//sprintf(string, "%i ", time);
lcd_type(3, 8, string);
//sprintf(string, "%i ", time);
lcd_type(4, 7, string);
//sprintf(string, "%i ", time);
lcd_type(5, 7, string);
//sprintf(string, "%i ", time);
lcd_type(6, 7, string);
//sprintf(string, "%i ", time);
lcd_type(7, 7, string);
//sprintf(string, "%i ", time);
lcd_type(8, 7, string);

//pH++;
time++;
//delay_ms(100);
};

while (1)
 {

 }
}
