
lcd_ccs.c - PICC_CCS LCD manipulation library for microcontrollers
------------------------------------------------------------------

This library allows you to init, write and set cursor position on a standard LCD display when writing a PICC_CCS software for microcontrollers.


Usage example:
--------------

```c
 
#include "lcd_ccs.c"
 
void main(void){

   lcd_ini();
   delay_ms(250);
   lcd_write('\f');
   delay_ms(250);

   
   lcd_pos_xy(2,1);
   printf(lcd_write,"LCD");
   lcd_pos_xy(2,2);
   printf(lcd_write,"Testing");
   delay_ms(2000);
      
   while(true){
   }
}

```

