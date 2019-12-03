#ifndef SHIFTREGISTER_H
#define SHIFTREGISTER_H

#include <avr/io.h>
#include <util/delay.h>

#define PORT PORTB  
#define DDR DDRB
#define DATA PB0            
#define SHIFT_CLK PB1      
#define STORE_CLK PB2     

void shiftInit()
{
    DDR |= ((1 << SHIFT_CLK) | (1 << STORE_CLK) | (1 << DATA));
}

void shiftHigh()
{
    PORT |= (1 << DATA);
}

void shiftLow()
{
    PORT &= (~(1 << DATA));
}

void shiftPulse()
{
    PORT |= (1 << SHIFT_CLK);
    PORT &= (~(1 << SHIFT_CLK));
}

void shiftLatch()
{
    PORT |= (1 << STORE_CLK);
    _delay_loop_1(1); 
    PORT &= (~(1 << STORE_CLK));
    _delay_loop_1(1);
}

void shiftWrite(uint8_t data)
{

    for(uint8_t i = 0; i < 8; i++)
    {

        if(data & 0b10000000)
        {
           
            shiftHigh();
        }
        else
        {              
          
            shiftLow();
        }

        shiftPulse();  
        data = data << 1;  
    }


    shiftLatch();
}

void Wait()
{
    for(uint8_t i=0;i<50;i++)
    {
        _delay_loop_2(0);
    }
}

#endif
