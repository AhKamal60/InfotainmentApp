/*
 * DIO.h
 *
 *  Created on: Nov 1, 2019
 *      Author: Kamal
 */


#ifndef DIO_DRIVER_DIO_H_
#define DIO_DRIVER_DIO_H_

#include"infra_structure/std_types.h"
#include "infra_structure/AVR.h"
/* _________________DIO PINS_______________________*/
#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 7
#define B0 8
#define B1 9
#define B2 10
#define B3 11
#define B4 12
#define B5 13
#define B6 14
#define B7 15
#define C0 16
#define C1 17
#define C2 18
#define C3 19
#define C4 20
#define C5 21
#define C6 22
#define C7 23
#define D0 24
#define D1 25
#define D2 26
#define D3 27
#define D4 28
#define D5 29
#define D6 30
#define D7 31

/*_____________________________AVR_PORTS________________________________*/
#define PA 0
#define PB 1
#define PC 2
#define PD 3

/*_____________________________DIO_DIRECTION________________________________*/
#define OUTPUT 1
#define INPUT 0

#define ERROR_OK 0
#define ERROR_NOK 1

/*_____________________________Common_Macros____________________________*/


/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )


extern uint8_t DIO_INIT_Pin(uint8_t Pin_Number, uint8_t direction);
extern uint8_t DIO_INIT_PORT (uint8_t Port_Name, uint8_t direction);
extern uint8_t DIO_Write_pin(uint8_t Pin_Number, uint8_t Data);
extern uint8_t DIO_Read_Pin (uint8_t Pin_Number, volatile uint8_t * ReadData);
extern uint8_t DIO_Write_Port (uint8_t Port_Name, uint8_t Data);
extern uint8_t DIO_Read_Port (uint8_t Port_Name, volatile uint8_t * ReadData);
extern uint8_t DIO_Activate_Pullup (uint8_t Pin_Number);

#endif /* DIO_DRIVER_DIO_H_ */
