#ifndef __io_h__
#define __io_h__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "shiftRegister.h"

#define SET_BIT(p,i) ((p) |= (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) & (1 << (i)))
          


#define DATA_BUS PORTC		
#define CONTROL_BUS PORTD	
#define RS 6			
#define E 7			


void LCD_init();
void LCD_ClearScreen(void);
void LCD_WriteCommand (unsigned char Command);
void LCD_Cursor (unsigned char column);
void LCD_DisplayString(unsigned char column ,const char *string);
void LCD_DisplayInt(uint8_t value);
void delay_ms(int miliSec);

void LCD_ClearScreen(void) {
   LCD_WriteCommand(0x01);
}

void LCD_Init(void) {
    delay_ms(100);
    LCD_WriteCommand(0x38);
    LCD_WriteCommand(0x06);
    LCD_WriteCommand(0x0c);
    LCD_WriteCommand(0x01);
    delay_ms(10);						 
}

void LCD_WriteCommand (unsigned char Command) {
   CLR_BIT(CONTROL_BUS,RS);
   shiftWrite(Command);
   SET_BIT(CONTROL_BUS,E);
   asm("nop");
   CLR_BIT(CONTROL_BUS,E);
   delay_ms(2); 
}

void LCD_WriteData(unsigned char Data) {
   SET_BIT(CONTROL_BUS,RS);
    shiftWrite(Data);
   SET_BIT(CONTROL_BUS,E);
   asm("nop");
   CLR_BIT(CONTROL_BUS,E);
   delay_ms(1);
}

void LCD_DisplayString( unsigned char column, const char* string) {
   unsigned char c = column;
   while(*string) {
      LCD_Cursor(c++);
      LCD_WriteData(*string++);
   }
}

void LCD_Cursor(unsigned char column) {
   if ( column < 17 ) { 
			
      LCD_WriteCommand(0x80 + column - 1);
   } else {
      LCD_WriteCommand(0xB8 + column - 9);	
											
   }
}

void LCD_Custom(unsigned char cgPos, unsigned char* symbol)
{
    if(cgPos < 8)
    {
        LCD_WriteCommand(0x40 + (cgPos * 8));

        unsigned char i;
        for(i = 0; i < 8; ++i)
        {
            LCD_WriteData(symbol[i]);
        }
    }
}

void LCD_DisplayDigit(uint8_t pos, uint8_t value)
{
    unsigned char tens = (value / 10) + '0'; 
    unsigned char ones = (value % 10) + '0';

    LCD_Cursor(pos);
    LCD_WriteData(tens);
    LCD_Cursor(++pos);
    LCD_WriteData(ones);
}

void delay_ms(int miliSec) 

{
    int i,j;
    for(i=0;i<miliSec;i++)
    for(j=0;j<775;j++)
  {
   asm("nop");
  }
}


#endif
