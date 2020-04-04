/*
 * lcd.c
 *
 *  Created on: Jan 3, 2020
 *      Author: H
 */
/***************************Includes*****************************************/
#include "lcd.h"

/******************************LOCAL_MACROS**************************************/
#define INIT_CASE_0 0u
#define INIT_CASE_1 1u
#define INIT_CASE_2 2u
#define INIT_CASE_3 3u

#define COMMAND_CASE_0 0u
#define COMMAND_CASE_1 1u
#define COMMAND_CASE_2 2u
#define COMMAND_CASE_3 3u
#define COMMAND_CASE_4 4u
#define COMMAND_CASE_5 5u
#define COMMAND_CASE_6 6u
#define COMMAND_CASE_7 7u


#define DISPLAY_CHAR_CASE_0 0u
#define DISPLAY_CHAR_CASE_1 1u
#define DISPLAY_CHAR_CASE_2 2u
#define DISPLAY_CHAR_CASE_3 3u
#define DISPLAY_CHAR_CASE_4 4u
#define DISPLAY_CHAR_CASE_5 5u
#define DISPLAY_CHAR_CASE_6 6u
#define DISPLAY_CHAR_CASE_7 7u

/***********************************Global_Variable*****************************************/
static uint8_t gu8_INIT_Cases= NULL;
static uint8_t gu8_INIT_flag= NULL;
static uint8_t gu8_Send_Command_Cases=NULL;
static uint8_t gu8_display_char_case=NULL;
static uint8_t gu8_display_string_flag_arr=NULL;
static uint8_t gu8_display_string_flag=NULL;
static uint8_t gu8_display_row_col=NULL;

static uint8_t u8_buff[16]; /* String to hold the ascii result */
static uint8_t gu8_int_flag=NULL;

ERROR_TYPE_t LCD_init(void)
{
	uint8_t au8_error=NULL;
	switch(gu8_INIT_Cases)
	{
	case INIT_CASE_0:
		LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW);
#if (DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_PINS
		LCD_DATA_PORT_DIR |= 0xF0; /* Configure the highest 4 bits of the data port as output pins */
		LCD_sendCommand(FOUR_BITS_DATA_MODE); /* initialize LCD in 4-bit mode */
#else
		LCD_DATA_PORT_DIR |= 0x0F; /* Configure the lowest 4 bits of the data port*/
		LCD_sendCommand(FOUR_BITS_DATA_MODE);
#endif
#elif (DATA_BITS_MODE == 8)
		LCD_DATA_PORT_DIR = 0xFF; /* Configure the data port as output port */
		LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
#endif
		gu8_INIT_flag++;
		if(gu8_INIT_flag==8)
		{
			gu8_INIT_flag=NULL;
			gu8_INIT_Cases=INIT_CASE_1;
		}
		au8_error=INIT_MODE_BITS_COMMAND;
		break;
	case INIT_CASE_1:
		LCD_sendCommand(CURSOR_OFF); /* cursor off */
		gu8_INIT_flag++;
		if(gu8_INIT_flag==8)
		{
			gu8_INIT_flag=NULL;
			gu8_INIT_Cases=INIT_CASE_2;
		}
		au8_error=INIT_CURSOR_OFF_COMMAND;
		break;
	case INIT_CASE_2:
		LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);
		gu8_INIT_flag++;
		if(gu8_INIT_flag==8)
		{
			gu8_INIT_flag=NULL;
			gu8_INIT_Cases=INIT_CASE_3;
		}
		au8_error=INIT_CLEAR_COMMAND_OK;
		break;
	case INIT_CASE_3:
		au8_error=INIT_LCD_OK;
		gu8_INIT_Cases=INIT_CASE_3;
		break; ;
	default:
		au8_error=INIT_LCD_NOK;
		break;
	}
	return au8_error;
}


ERROR_TYPE_t LCD_sendCommand(uint8_t u8_command)
{
	uint8_t au8_error;
	switch(gu8_Send_Command_Cases)
	{
	case COMMAND_CASE_0: /************************case_0****************************************/
		CLEAR_BIT(LCD_CTRL_PORT,RS); /* Instruction Mode RS=0 */
		CLEAR_BIT(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
		gu8_Send_Command_Cases=COMMAND_CASE_1;
		//au8_error=COMMAND_CONFIG_OK;
		break;
	case COMMAND_CASE_1: /************************case_1****************************************/
		SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
		gu8_Send_Command_Cases=COMMAND_CASE_2;
	//	au8_error=COMMAND_ENABLE_OK;
		break;
	case COMMAND_CASE_2: /************************case_2****************************************/
#if (DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_PINS
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (u8_command & 0xF0);
#else
		LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((u8_command & 0xF0) >> 4);
#endif
#elif (DATA_BITS_MODE == 8)
		LCD_DATA_PORT = u8_command; /* out the required command to the data bus D0 --> D7 */
#endif
		gu8_Send_Command_Cases=COMMAND_CASE_3;
	//	au8_error=COMMAND_SEND_CURRENTLY;
		break;
	case COMMAND_CASE_3: /************************case_3****************************************/
		CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
		gu8_Send_Command_Cases=COMMAND_CASE_4;
	//	au8_error=COMMAND_SEND_OK;
		break;
	case COMMAND_CASE_4: /************************case_4****************************************/
		SET_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
		gu8_Send_Command_Cases=COMMAND_CASE_5;
	//	au8_error=COMMAND_SEND_OK;
		break;
	case COMMAND_CASE_5: /************************case_5****************************************/
#if (DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_PINS
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((u8_command & 0x0F) << 4);
#else
		LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (u8_command & 0x0F);
#endif
#endif
		gu8_Send_Command_Cases=COMMAND_CASE_6;
	//	au8_error=COMMAND_CONFIG_OK;
		break;
	case COMMAND_CASE_6: /************************case_6****************************************/
		CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
		gu8_Send_Command_Cases=COMMAND_CASE_7;
	//	au8_error=COMMAND_CONFIG_OK;
		break;
	case COMMAND_CASE_7: /************************case_7****************************************/
		gu8_Send_Command_Cases=COMMAND_CASE_0;
		au8_error=100;
		break;
	default:
		au8_error=COMMAND_NOT_DELIEVERED;
		break;
	}
	return au8_error;
}

ERROR_TYPE_t LCD_displayCharacter(uint8_t u8_data)
{
	uint8_t au8_error=NULL;
	if(gu8_INIT_Cases==INIT_CASE_3)
	{
		switch(gu8_display_char_case)
		{
		case DISPLAY_CHAR_CASE_0: /******************CASE_0*********************/
			SET_BIT(LCD_CTRL_PORT,RS); /* Data Mode RS=1 */
			CLEAR_BIT(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
			gu8_display_char_case=DISPLAY_CHAR_CASE_1;
			au8_error=DISPLAY_DATA_INIT_OK;
			break;
		case DISPLAY_CHAR_CASE_1: /******************CASE_1*********************/
			SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
			gu8_display_char_case=DISPLAY_CHAR_CASE_2;
			au8_error=DISBLAY_DATA_ENABLE_OK;
			break;
		case DISPLAY_CHAR_CASE_2: /******************CASE_2*********************/
#if (DATA_BITS_MODE == 4) /* out the highest 4 bits of the required data to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (u8_data & 0xF0);
#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((u8_data & 0xF0) >> 4);
#endif
#elif (DATA_BITS_MODE == 8)
			LCD_DATA_PORT = u8_data; /* out the required command to the data bus D0 --> D7 */
#endif
			gu8_display_char_case=DISPLAY_CHAR_CASE_3;
			break;
		case DISPLAY_CHAR_CASE_3: /******************CASE_3*********************/
			CLEAR_BIT(LCD_CTRL_PORT,E); /* DISABLE LCD E=1 */
			gu8_display_char_case=DISPLAY_CHAR_CASE_4;
			au8_error=DISPLAY_DATA_DISABLE_OK;
			break;
		case DISPLAY_CHAR_CASE_4: /******************CASE_4*********************/
			SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
			gu8_display_char_case=DISPLAY_CHAR_CASE_5;
			au8_error=DISBLAY_DATA_ENABLE_OK;
			break;
		case  DISPLAY_CHAR_CASE_5: /******************CASE_5*********************/
			/* out the lowest 4 bits of the required data to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((u8_data & 0x0F) << 4);
#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (u8_data & 0x0F);
#endif
			au8_error=DISPLAY_DATA_CONFIG_OK;
			gu8_display_char_case=DISPLAY_CHAR_CASE_6;
			break;
		case DISPLAY_CHAR_CASE_6: /******************CASE_6*********************/
			CLEAR_BIT(LCD_CTRL_PORT,E); /* DISABLE LCD E=1 */
			au8_error=DISPLAY_DATA_CONFIG_OK;
			gu8_display_char_case=DISPLAY_CHAR_CASE_7;
			break;
		case DISPLAY_CHAR_CASE_7:
			gu8_display_char_case=DISPLAY_CHAR_CASE_0;
			au8_error=0;
			break;
		default:
			au8_error=DISPLAY_DATA_NOK;
			break;
		}
	}
	return au8_error;
}

ERROR_TYPE_t LCD_displayString(const uint8_t * ptr_String, uint8_t* u8_dumy)
{
	uint8_t au8_error=NULL;
	if(gu8_INIT_Cases==INIT_CASE_3)
	{
		if(*u8_dumy==NULL)
		{
			if (ptr_String[gu8_display_string_flag_arr] != '\0')
			{
				LCD_displayCharacter(ptr_String[gu8_display_string_flag_arr]);
				gu8_display_string_flag++;
				if(gu8_display_string_flag==8)
				{
					gu8_display_string_flag_arr+=1;
					gu8_display_string_flag=NULL;
					au8_error=DISPLAY_STRING_CHAR_DONE;
				}
				else
				{
					au8_error=DISPLAY_STRING_CHAR_NDONE;
				}
			}
			else
			{
				(*u8_dumy)=1;
				gu8_display_string_flag_arr=NULL;
				gu8_display_string_flag=NULL;
				au8_error=DISPLAY_STRING_FINISHED;
			}
		}
	}
	return au8_error;
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); //clear display
}

void LCD_goToRowColumn(uint8_t u8_row,uint8_t u8_col)
{
	uint8_t Address;

		/* first of all calculate the required address */
		switch(u8_row)
		{
			case 0:
					Address=u8_col;
					break;
			case 1:
					Address=u8_col+0x40;
					break;
			case 2:
					Address=u8_col+0x10;
					break;
			case 3:
					Address=u8_col+0x50;
					break;
		}
		/* to write to a specific address in the LCD
		 * we need to apply the corresponding command 0b10000000+Address */
		LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}
void LCD_displayStringRowColumn(uint8_t row,uint8_t col,const uint8_t *Str,uint8_t * u8_flag)
{
	if(*u8_flag==NULL)
	{
		gu8_display_row_col++;
		if(gu8_display_row_col<=8)
		{
			LCD_goToRowColumn(row,col); /* go to to the required LCD position */
		}
		else if(gu8_display_row_col>=8)
		{
			LCD_displayString(Str, u8_flag);
			if(*u8_flag==1)
			{
				gu8_display_row_col=0;
			}
		}
	}
}

void LCD_intgerToString(uint8_t u8_data, uint8_t *u8_flag)
{
	if(gu8_int_flag==NULL)
	{
		itoa(u8_data,u8_buff,10); /* 10 for decimal */
	}
	if(gu8_int_flag<=8)
	{
		 LCD_displayString(&u8_buff, u8_flag);
		 gu8_int_flag++;
		 if(gu8_int_flag==9)
		 {
			 gu8_int_flag=NULL;
			 for(int i=0; i<16;i++)
			 {
				 u8_buff[i]=0;
			 }
		 }
	}
}
