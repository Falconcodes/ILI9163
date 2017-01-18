
//according of lcd PINs to MCU PINs
#define DC   PORTB.0  // A0 pin
#define RST  PORTB.1
#define CS   PORTD.7

unsigned int text_color_1=0xFF, text_color_2=0xFF, bg_color_1=0x0, bg_color_2=0x0;

//отправить SPI-комманду модулю, список команд см. выше в строках #define 
void lcd_com(unsigned char command){
  CS=0;
  spi(command);                                                                                              
  CS=1;
}

//отправить очередной байт после предшествующей команды lcd_com
lcd_send(unsigned char byte){
  DC=1;
  CS=0;
  spi(byte);
  CS=1;
  DC=0;
}

text_color(unsigned char red, unsigned char green, unsigned char blue){
text_color_1 = (red<<3) + (green>>3);
text_color_2 = (green & 0b00011111)<<5 + blue;
}

bg_color(unsigned char red, unsigned char green, unsigned char blue){
bg_color_1 = (red<<3) + (green>>3);
bg_color_2 = (green & 0b00011111)<<5 + blue;
}

//залить экран цветом 65к
void lcd_fill(unsigned char red, unsigned char green, unsigned char blue) { 
  unsigned int i;
  unsigned char spi_1, spi_2;
  spi_1 = (red<<3) + (green>>3);
  spi_2 = ((green & 0b00011111)<<5) + blue; 
   
  CS=0;
  spi(0x2C);                                                                                                
  DC=1;
     
  for (i=0; i<16384; i++){
  spi(spi_1); //first byte
  spi(spi_2); //second byte
  }
  DC=0;
  CS=1;
}

//задать диапазон по Y дл€ вывода (номера строк начала и конца)
void lcd_y_band (unsigned char start, unsigned char end){
  lcd_com(0x2B);
  lcd_send(0);
  lcd_send(start);
  lcd_send(0);
  lcd_send(end);
}

//задать диапазон по X дл€ вывода (номера строк начала и конца)
void lcd_x_band (unsigned char start, unsigned char end){
  lcd_com(0x2A);
  lcd_send(0);
  lcd_send(start);
  lcd_send(0);
  lcd_send(end);
}

/*
//‘ункци€ - вывод в строку
void lcd_typechar(unsigned char symb, unsigned char y, unsigned char x) {
unsigned char j, step, char_str, char_pix; 
lcd_y_band(8*y, 8*y+7);
lcd_x_band(8*x, 8*x+7);
  CS=0;
  spi(0x2C);                                                                                                
  DC=1;
  for (char_str=0;char_str<8;char_str++) { //инкремент строк отрисовки символа
   for (char_pix=0;char_pix<8;char_pix++) { //инкремент пикселей в пределах одной строки отрисовки символа 
     if((ascii[symb - 0x20][char_str]) & (1<<(7-char_pix))) 
     {
      spi(0xFF);
      spi(0xFF);
     }
     else 
     {
      spi(0x30);
      spi(0x30);
     }
   }
  }

 DC=0;
 CS=1;
} */

//‘ункци€ - вывод в строку
void lcd_type(unsigned char y, unsigned char x, unsigned char text[16]) {
  unsigned char i, posit, char_str, char_pix; 
  lcd_y_band(8*y, 8*y+7);
  lcd_x_band(8*x, 8*x+7);
  
  i=15;
  while (text[i] == 0) i--; //вычисл€ем длину строки, за вычетом нулевых элементов, провер€€ с конца строки наличие первого ненулевого элемента
  
  for (posit=0; posit<(i+1); posit++){
   DC=0;
   lcd_x_band(8*x+8*posit, 8*x+7+8*posit);
   CS=0;
   spi(0x2C);                                                                                                
   DC=1;
   for (char_str=0;char_str<8;char_str++) { //инкремент строк отрисовки символа
     for (char_pix=0;char_pix<8;char_pix++) { //инкремент пикселей в пределах одной строки отрисовки символа 
       if((ascii[text[posit]-0x20][char_str]) & (1<<(7-char_pix))) 
       {
        spi(text_color_1);
        spi(text_color_2);
       }
       else 
       {
        spi(bg_color_1);
        spi(bg_color_2);
       }
     }
   }
   
  }
 DC=0;
 CS=1;
}