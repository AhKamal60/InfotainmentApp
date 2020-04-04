/*
 * LCD_cfg.h
 *
 *  Created on: Jan 3, 2020
 *      Author: H
 */

#ifndef MCAL_LCD_LCD_H_
#define MCAL_LCD_LCD_H_

/***********************INCLUDES***************************************/
#include "infra_structure/std_types.h"
#include "infra_structure/common_macros.h"
#include "infra_structure/avr.h"
#include "MCAL/DIO/DIO.h"
#include"lcd_ret_val.h"

/****************************TYPE_DEF*****************************************/

//typedef uint8_t ERROR_TYPE_t;

/*********************************Config_MACROS************************************/
/* LCD HW Pins */
#define RS 1
#define RW 2
#define E  3
#define LCD_CTRL_PORT PORTA
#define LCD_CTRL_PORT_DIR DDRA
#define LCD_DATA_PORT PORTA
#define LCD_DATA_PORT_DIR DDRA
/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80

/* LCD Data bits mode configuration */
#define DATA_BITS_MODE 4

/* Use higher 4 bits in the data port */
#define UPPER_PORT_PINS


/***************************FUNCTION_PROTOTYPES*****************************/
ERROR_TYPE_t LCD_init(void);
ERROR_TYPE_t LCD_sendCommand(uint8_t u8_command);
ERROR_TYPE_t LCD_displayCharacter(uint8_t u8_data);
ERROR_TYPE_t LCD_displayString(const uint8_t * ptr_String,uint8_t * u8_dummy);
void LCD_clearScreen(void);
void LCD_displayStringRowColumn(uint8_t row,uint8_t col,const uint8_t *Str, uint8_t * u8_flag);
void LCD_goToRowColumn(uint8_t u8_row,uint8_t u8_col);
void LCD_intgerToString(uint8_t u8_data, uint8_t * u8_flag);

#endif /* MCAL_LCD_LCD_H_ */
