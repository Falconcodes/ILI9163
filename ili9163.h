
//according of lcd PINs to MCU PINs
#define DC  PORTB.0  // A0 pin
#define RST PORTB.1
#define CS  PORTD.7

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

//залить экран цветом, каждый цвет в диапазоне 0..63
lcd_fill(unsigned char red, unsigned char green, unsigned char blue) { 
  unsigned int i;
  CS=0;
  spi(0x2C);                                                                                                
  DC=1;
  for (i=0; i<16384; i++){
  spi(red<<2); //Red
  spi(green<<2); //Green
  spi(blue<<2); //Blue
  }
  DC=0;
  CS=1;
}

