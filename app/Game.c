/*
 * Game.c
 *
 *  Created on: Mar 28, 2020
 *      Author: H
 */
#include "Game.h"

/*__________________________________________LOCAL_MACROS______________________________________________*/ 
#define YES 1
#define NO 2
#define SKIP 3
#define INIT 0
#define Q1_DISPLAY 1
#define Q1_OPTIONS_DISPLAY 2
#define Q1_KEYPAD 3
#define Q1_CLEAR 4
#define Q2_DISPLAY 5
#define Q2_OPTIONS_DISPLAY 6
#define Q2_KEYPAD 7
#define Q2_CLEAR 8
#define Q3_DISPLAY 9
#define Q3_OPTIONS_DISPLAY 10
#define Q3_KEYPAD 11
#define Q3_CLEAR 12
#define Q4_DISPLAY 13
#define Q4_OPTIONS_DISPLAY 14
#define Q4_KEYPAD 15
#define Q4_CLEAR 16
#define Q5_DISPLAY 17
#define Q5_OPTIONS_DISPLAY 18
#define Q5_KEYPAD 19
#define Q5_CLEAR 20
#define Q6_DISPLAY 21
#define Q6_OPTIONS_DISPLAY 22
#define Q6_KEYPAD 23
#define Q6_CLEAR 24
#define Result_DISPLAY 25
#define Score_DISPLAY_1 26
#define Score_DISPLAY_2 27
#define Score_DISPLAY_3 28
#define Clear 29
#define Continue 30
#define Option_KEYPAD 31
#define Exit 32
/*_______________________________________GLOBAL VARIABLES _______________________________________*/
static uint8_t gu8_score=NULL;
/*GLOBAL variable to store the score of the game*/
static uint8_t gu8_Game_Task=NULL;
/*Game_Task is a static global variable that indicate the status of the case*/
static uint8_t gu8_Init_Error=TRUE;
/* static global variable to store in it the return error of the LCD_Init Function*/
static uint8_t gu8_display_1=NULL;
/* A flag passed to check the status of of Lcd_Display string function*/
static uint8_t gu8_display_2=NULL;
/* A flag passed to check the status of of Lcd_Display string function*/
static uint8_t gu8_display_3=NULL;
/* A flag passed to check the status of of Lcd_Display string function*/
static uint8_t gu8_display_4=NULL;
/* A flag passed to check the status of of Lcd_Display string function*/
static uint8_t gu8_display_5=NULL;
/* A flag passed to check the status of of Lcd_Display string function*/
static uint8_t gu8_display_6=NULL;
/* A flag passed to check the status of of Lcd_Display string function*/
static uint8_t gu8_display_7=NULL;
/* A flag passed to check the status of of Lcd_Display string function*/
static uint8_t gu8_display_8=NULL;
/* A flag passed to check the status of of Lcd_Display string function*/

static uint8_t gu8_option_1=NULL;
/*A flag passed to check the status of of Lcd_DisplaystringRowColoumn function */
static uint8_t gu8_option_2=NULL;
/*A flag passed to check the status of of Lcd_DisplaystringRowColoumn function */
static uint8_t gu8_option_3=NULL;
/*A flag passed to check the status of of Lcd_DisplaystringRowColoumn function */
static uint8_t gu8_option_4=NULL;
/*A flag passed to check the status of of Lcd_DisplaystringRowColoumn function */
static uint8_t gu8_option_5=NULL;
/*A flag passed to check the status of of Lcd_DisplaystringRowColoumn function */
static uint8_t gu8_option_6=NULL;
/*A flag passed to check the status of of Lcd_DisplaystringRowColoumn function */
static uint8_t gu8_option_7=NULL;
/*A flag passed to check the status of of Lcd_DisplaystringRowColoumn function */
static uint8_t gu8_option_8=NULL;
/*A flag passed to check the status of of Lcd_DisplaystringRowColoumn function */

static uint8_t gu8_key[NumberOFQUESTIONS];
/* A global variable array to return the value of the keypad pressed value*/
static uint8_t gu8_key_2[NumberOFQUESTIONS]={YES,YES,NO,YES,YES};
/* A global variable array to return the value of the keypad pressed value*/
static uint8_t gu8_clearq1=NULL;
/* A global variable array to return the value of the keypad pressed value*/
static uint8_t gu8_clearq2=NULL;
/* A global variable array to return the value of the keypad pressed value*/
static uint8_t gu8_clearq3=NULL;
/* A global variable array to return the value of the keypad pressed value*/
static uint8_t gu8_clearq4=NULL;
/* A global variable array to return the value of the keypad pressed value*/
static uint8_t gu8_clearq5=NULL;
/* A global variable array to return the value of the keypad pressed value*/
static uint8_t gu8_clearq6=NULL;
/* A global variable array to return the value of the keypad pressed value*/
static uint8_t gu8_clearq7=NULL;
/* A global variable array to return the value of the keypad pressed value*/
static uint8_t gu8_clearq8=NULL;
static uint8_t gu8_final=0;


/*__________________________________Function Implementation_______________________________________*/ 
void GameRoll (void)
{
	uint8_t u8_roll=NULL;
	switch (gu8_Game_Task)
	{
	uint8_t x;
	case INIT:
		gu8_Init_Error=LCD_init(); /*Initializing the LCD*/
		if(gu8_Init_Error==INIT_LCD_OK)
		{
			for (x=0; x<NumberOFQUESTIONS; x++ ) /*Initializing the Buffer that will store the answers*/
			{
				gu8_key[x]=NULL;
			}
			gu8_Game_Task++;
		}
		break;
	case Q1_DISPLAY:  /*Display The First Statement*/
		LCD_displayString("       WLECOME TO THE COVID19 GAME ", &gu8_display_1);
		if(TRUE==gu8_display_1)
		{
			gu8_display_1=NULL;
			gu8_Game_Task++;
		}
		break;
	case Q1_OPTIONS_DISPLAY: /*Display the Second Statement*/
		LCD_displayStringRowColumn(1,0,"               LET'S PLAY! ",&gu8_option_1);
		if(TRUE==gu8_option_1)
		{
			gu8_option_1=NULL;
			gu8_Game_Task++;
		}
		break;
	case Q1_KEYPAD: /*Delay */
		for (int i=0; i<1000;i++)
		{
			if(999==i)
			{
				gu8_Game_Task++;
			}
		}
		break;
	case Q1_CLEAR: /*Clear the LCD*/
		LCD_sendCommand(CLEAR_COMMAND);
		gu8_clearq1++;
		if(gu8_clearq1==8)
		{
			gu8_clearq1=NULL;
			gu8_Game_Task++;
			gu8_score=NULL; /*Initializing the Score of the GAME variable */
		}
		break;
	case Q2_DISPLAY: /*Display Q1*/
		LCD_displayString("      COVID19 IS A GLOBAL Pandemic?", &gu8_display_2);
		if(TRUE==gu8_display_2)
		{
			gu8_display_2=NULL;
			gu8_Game_Task++;
		}
		break;
	case Q2_OPTIONS_DISPLAY: /*DISPLAY Answer Option 1*/
		LCD_displayStringRowColumn(1,0,"            1-YES 2-NO 3-SKIP",&gu8_option_2);
		if(TRUE==gu8_option_2)
		{
			gu8_option_2=NULL;
			gu8_Game_Task++;
		}
		break;
	case Q2_KEYPAD: /*KeyPad for Q1*/
		gu8_key[0]=KeyPad_getPressedKey();
		if(gu8_key[0]!=NULL)
		{
			gu8_Game_Task++;
		}
		break;
	case Q2_CLEAR: /*Clear Q2*/
		LCD_sendCommand(CLEAR_COMMAND);
		gu8_clearq2++;
		if(gu8_clearq2==8)
		{
			gu8_clearq2=NULL;
			gu8_Game_Task++;
		}
		break;
	case Q3_DISPLAY:  /*Display Q2*/
		LCD_displayString("  Wash your hands frequently for 20sec?", &gu8_display_3);
		if(TRUE==gu8_display_3)
		{
			gu8_display_3=NULL;
			gu8_Game_Task++;
		}
		break;
	case Q3_OPTIONS_DISPLAY: /*DISPLAY Answer Option 2*/
		LCD_displayStringRowColumn(1,0,"            1-YES 2-NO 3-SKIP",&gu8_option_3);
		if(TRUE==gu8_option_3)
		{
			gu8_option_3=NULL;
			gu8_Game_Task++;
		}
		break;
	case Q3_KEYPAD:
		gu8_key[1]=KeyPad_getPressedKey();
		if(gu8_key[1]!=NULL)
		{
			gu8_Game_Task++;
		}
		break;
	case Q3_CLEAR:
		LCD_sendCommand(CLEAR_COMMAND);
		gu8_clearq3++;
		if(gu8_clearq3==8)
		{
			gu8_clearq3=NULL;
			gu8_Game_Task++;
		}
		break;
	case Q4_DISPLAY:
		LCD_displayString("No need to stay home when you have fever", &gu8_display_4);
		if(TRUE==gu8_display_4)
		{
			gu8_display_4=NULL;
			gu8_Game_Task++;
		}
		break;
	case Q4_OPTIONS_DISPLAY:
		LCD_displayStringRowColumn(1,0,"symptoms? 1-YES 2-NO 3-SKIP",&gu8_option_4);
		if(TRUE==gu8_option_4)
		{
			gu8_option_4=NULL;
			gu8_Game_Task++;
		}
		break;
	case Q4_KEYPAD:
		gu8_key[2]=KeyPad_getPressedKey();
		if(gu8_key[2]!=NULL)
		{
			gu8_Game_Task++;
		}
		break;
	case Q4_CLEAR:
		LCD_sendCommand(CLEAR_COMMAND);
		gu8_clearq4++;
		if(gu8_clearq4==8)
		{
			gu8_clearq4=NULL;
			gu8_Game_Task++;
		}
		break;
	case Q5_DISPLAY:
		LCD_displayString("Don't touch nose, eyes or mouth with", &gu8_display_5);
		if(TRUE==gu8_display_5)
		{
			gu8_display_5=NULL;
			gu8_Game_Task++;
		}
		break;
	case Q5_OPTIONS_DISPLAY:
		LCD_displayStringRowColumn(1,0,"your hands? 1-YES 2-NO 3-SKIP",&gu8_option_5);
		if(TRUE==gu8_option_5)
		{
			gu8_option_5=NULL;
			gu8_Game_Task++;
		}
		break;
	case Q5_KEYPAD:
		gu8_key[3]=KeyPad_getPressedKey();
		if(gu8_key[3]!=NULL)
		{
			gu8_Game_Task++;
		}
		break;
	case Q5_CLEAR:
		LCD_sendCommand(CLEAR_COMMAND);
		gu8_clearq5++;
		if(gu8_clearq5==8)
		{
			gu8_clearq5=NULL;
			gu8_Game_Task++;
		}
		break;
	case Q6_DISPLAY:
		LCD_displayString("Avoid close contact with people who have", &gu8_display_6);
		if(TRUE==gu8_display_6)
		{
			gu8_display_6=NULL;
			gu8_Game_Task++;
		}
		break;
	case Q6_OPTIONS_DISPLAY:
		LCD_displayStringRowColumn(1,0,"symptoms? 1-YES 2-NO 3-SKIP",&gu8_option_6);
		if(TRUE==gu8_option_6)
		{
			gu8_option_6=NULL;
			gu8_Game_Task++;
		}
		break;
	case Q6_KEYPAD:
		gu8_key[4]=KeyPad_getPressedKey();
		if(gu8_key[4]!=NULL)
		{
			gu8_Game_Task++;
		}
		break;
	case Q6_CLEAR:
		LCD_sendCommand(CLEAR_COMMAND);
		gu8_clearq6++;
		if(gu8_clearq6==8)
		{
			gu8_clearq6=NULL;
			gu8_Game_Task++;
		}
		break;
	case Result_DISPLAY:
		for(u8_roll=0; u8_roll<NumberOFQUESTIONS; u8_roll++)
		{
			if(gu8_key[u8_roll]==gu8_key_2[u8_roll])
			{
				gu8_score+=1;
			}
		}
		gu8_Game_Task++;
		break;
	case Score_DISPLAY_1:
		LCD_displayString("              CONGRATULATIONS!", &gu8_display_7);
		if(TRUE==gu8_display_7)
		{
			gu8_display_7=NULL;
			gu8_Game_Task++;
		}
		break;
	case Score_DISPLAY_2:
		LCD_displayStringRowColumn(1,0,"            YOUR SCORE IS ",&gu8_option_7);
		if(TRUE==gu8_option_7)
		{
			gu8_option_7=NULL;
			gu8_Game_Task++;
		}
		break;
	case Score_DISPLAY_3:
		LCD_intgerToString(gu8_score,&gu8_display_8);
		if(TRUE==gu8_display_8)
		{
			for(int j=0; j<10000; j++)
			{
				if(j==9999)
				{
					gu8_Game_Task++;
					gu8_display_8=NULL;
				}
			}
		}
		break;
	case Clear:
		LCD_sendCommand(CLEAR_COMMAND);
		gu8_clearq7++;
		if(gu8_clearq7==8)
		{
			gu8_Game_Task++;
			gu8_clearq7=NULL;
		}
		break;
	case Continue:
		LCD_displayString("To Play Again Press:1, To Exit Press:2", &gu8_option_8);
		if(TRUE==gu8_option_8)
		{
			gu8_Game_Task++;
			gu8_option_8=NULL;
		}
		break;
	case Option_KEYPAD:
		gu8_final=KeyPad_getPressedKey();
		if(gu8_final==TRUE)
		{
			gu8_Game_Task=4;
		}
		else if(gu8_final==2)
		{
			gu8_Game_Task++;
		}
		else
		{
			gu8_Game_Task=Option_KEYPAD;
		}
		break;
	case Exit:
		LCD_sendCommand(CLEAR_COMMAND);
		gu8_clearq8++;
		if(gu8_clearq8==8)
		{
			gu8_Game_Task++;
			gu8_clearq8=NULL;
		}
		break;
	default :
		break;
	}
}

