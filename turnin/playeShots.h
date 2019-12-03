#ifndef PLAYERSHOTS_H
#define PLAYERSHOTS_H

#include "string.h"
#include "playerMovement.h"

#define shoot (~PINA & 0x02)

#define BULLET_SPACE 15

unsigned char activeBulletSpace = BULLET_SPACE; 

unsigned char playerBullets[BULLET_SPACE + 1] = "               ";
unsigned char shot;
unsigned char potentialHit; 

enum PlayerShootStates
{
    WAIT_SHOT,
    SHOT_HELD,
    PLAYER_SHOT
};

int playerShootTick(int state)
{
    switch(state)
    {
        case WAIT_SHOT: 
        {
            if(shoot)
            {
                if(ducking == TRUE)
                {
                    state = WAIT_SHOT; 
                }
                else
                {
                    state = SHOT_HELD;
                }
            }
            else
            {
                state = WAIT_SHOT; 
            }

            break;
        }
        case SHOT_HELD:
        {
            if(shoot) 
            {
                state = SHOT_HELD; 
            }
            else
            {
                state = PLAYER_SHOT; 
            }

            break;
        }
        case PLAYER_SHOT:
        {
            state = shoot ? PLAYER_SHOT : WAIT_SHOT; 
            break;
        }
    }

    switch(state)
    {
        case WAIT_SHOT: shot = 0; break;
        case PLAYER_SHOT: shot = 1; potentialHit = 1; break;
    }

    return state;
}

enum UpdateShotsStates
{
    UPDATE_SHOTS,
    SHOT_FIRED,
    SHOT_BTN_HELD
};

int updateShotsTick(int state)
{
    switch(state)
    {
        case UPDATE_SHOTS: 
        {
            if(shot)
            {
                state = SHOT_FIRED;
            }
            else
            {
                state = UPDATE_SHOTS; 
            }

            break;
        }
        case SHOT_FIRED: 
        {
            if(shot) 
            {
                state = SHOT_BTN_HELD; 
            }
            else
            {
                state = UPDATE_SHOTS; 
            }

            break;
        }
        case SHOT_BTN_HELD: state = shot ? SHOT_BTN_HELD : UPDATE_SHOTS; break;
    }

    switch(state)
    {
        case UPDATE_SHOTS:
        {
            if(inMenu == 0)
            {
                memmove(playerBullets + 1, playerBullets, 14);
                playerBullets[0] = ' ';
                for(int i = 0; i < activeBulletSpace; ++i)
                {
                    LCD_Cursor(i + 2);
                    LCD_WriteData(playerBullets[i]);
                }
            }

            break;
        }
        case SHOT_FIRED:
        {
            playerBullets[0] = '-';

            break;
        }
        case SHOT_BTN_HELD:
        {
            memmove(playerBullets + 1, playerBullets, 14);
            playerBullets[0] = ' ';
            for(int i = 0; i < activeBulletSpace; ++i)
            {
                LCD_Cursor(i + 2);
                LCD_WriteData(playerBullets[i]);
            }

            break;
        }
    }

    return state;
}

#endif
