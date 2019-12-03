#ifndef PLAYERMOVEMENT_H
#define PLAYERMOVEMENT_H

#include "customChar.h"
#include "io.h" 

#define R (~PINA & 0x10) 
#define D (~PINA & 0x04) 
#define ROW1_BEGIN 1
#define ROW2_BEGIN 17

unsigned char inMenu;

unsigned long playerMovementPeriod = 50;
unsigned long ms250 = 5;

enum MovementFlag
{
    FALSE,
    TRUE
} ducking;

enum PlayerMovementStates
{
    WAIT,
    DUCK 
};

void spriteUpdate(unsigned char currSprite)
{
    LCD_Cursor(ROW1_BEGIN);
    LCD_WriteData(currSprite);
}

int playerMovementTick(int state)
{
    static unsigned long count = 0;
    static unsigned char sprite = 0; 

    switch(state)
    {
        case WAIT:
        {
            if(inMenu == 0)
            {
                if(D)
                {
                    state = DUCK; 

                    LCD_Cursor(ROW1_BEGIN);
                    LCD_WriteData(' ');
                }
                else
                {
                    state = WAIT; 
                }
            }
            break;
        }

        case DUCK:
        {
            if(D) 
            {
                state = DUCK; 
            }
            else
            {
                state = WAIT;
           
                LCD_Cursor(ROW2_BEGIN);
                LCD_WriteData(' ');
                LCD_Cursor(ROW1_BEGIN);
                LCD_WriteData(PL_STATIONARY);
            }

            break;
        }
    }

    switch(state)
    {
        case WAIT: 
        {
            count = 0; 
            ducking = FALSE;
            
            break;
        }

        case DUCK:
        {
            ducking = TRUE;
            
            LCD_Cursor(ROW2_BEGIN);
            LCD_WriteData(PL_KNEEL);

            break;
        }
    }

    return state;
}

#endif
