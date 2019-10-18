/* 
 lcd_ccs.c : LCD manipulation library
 Author    : Rahul M. Juliato
 Original  : 10/dec/2012
 Revision  : mar/2017
 */


/* Define your LCD device pins to the PIC microcontroller */
#define lcd_enable     pin_b1
#define lcd_rs         pin_b0
#define lcd_d4         pin_b2
#define lcd_d5         pin_b3
#define lcd_d6         pin_b4
#define lcd_d7         pin_b5

#define lcd_type 2        // 0=5x7, 1=5x10, 2=2 lines
#define lcd_seg_lin 0x40  // Second line address on lcd ram


/* Inicialization sequence */
byte CONST INI_LCD[4] = {0x20 | (lcd_type << 2), 0xf, 1, 6};


/* Sends a 4 bit data to display */
void lcd_envia_nibble( byte dado ){
   output_bit(lcd_d4,bit_test(dado,0));
   output_bit(lcd_d5,bit_test(dado,1));
   output_bit(lcd_d6,bit_test(dado,2));
   output_bit(lcd_d7,bit_test(dado,3));
   output_high(lcd_enable);
   output_low(lcd_enable);
}


/* Sends an entire byte */
void lcd_envia_byte( boolean endereco, byte dado ){
   output_low(lcd_rs);
   output_bit(lcd_rs,endereco);
   delay_us(100);
   output_low(lcd_enable);
   lcd_envia_nibble(dado >> 4);
   lcd_envia_nibble(dado & 0x0f);
}


/* Init function */
void lcd_ini(){
   byte conta;
   output_low(lcd_d4);
   output_low(lcd_d5);
   output_low(lcd_d6);
   output_low(lcd_d7);
   output_low(lcd_rs);

   output_low(lcd_enable);
   delay_ms(15);
   for(conta=1;conta<=3;++conta){
      lcd_envia_nibble(3);
      delay_ms(5);
   }
   lcd_envia_nibble(2);
   for(conta=0;conta<=3;++conta) lcd_envia_byte(0,INI_LCD[conta]);
}


/* Sets the cursor position */
void lcd_pos_xy( byte x, byte y){
   byte endereco;
   if(y!=1)                     
      endereco = lcd_seg_lin;
   else
      endereco = 0;
   endereco += x-1;
   lcd_envia_byte(0,0x80|endereco);
}


/* Writes a char on display */ 
void lcd_write( char c){
   switch (c){
   case '\f':
     lcd_envia_byte(0,1);
     delay_ms(2);
     break;
   case '\n':
   case '\r':
     lcd_pos_xy(1,2);
     break;
   case '\b':
     lcd_envia_byte(0,0x10);
     break;
   default:
     lcd_envia_byte(1,c);
     break;
   }
}
