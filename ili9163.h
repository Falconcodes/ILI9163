
//according of lcd PINs to MCU PINs
#define DC  PORTB.0  // A0 pin
#define RST PORTB.1
#define CS  PORTD.7

//��������� SPI-�������� ������, ������ ������ ��. ���� � ������� #define 
void lcd_com(unsigned char command){
  CS=0;
  spi(command);                                                                                              
  CS=1;
}

//��������� ��������� ���� ����� �������������� ������� lcd_com
lcd_send(unsigned char byte){
  DC=1;
  CS=0;
  spi(byte);
  CS=1;
  DC=0;
}

//������ ����� ������, ������ ���� � ��������� 0..56
lcd_fill(unsigned char red, unsigned char green, unsigned char blue) { 
  unsigned int i;
  unsigned char red_, green_, blue_;
  red_=(red<<2)+7;     //����������� ���������� �������� 0b00000111
  green_=(green<<2)+7;
  blue_=(blue<<2)+7;
  CS=0;
  spi(0x2C);                                                                                                
  DC=1;
  for (i=0; i<16384; i++){
  spi(red_); //Red
  spi(green_); //Green
  spi(blue_); //Blue
  }
  DC=0;
  CS=1;
}

