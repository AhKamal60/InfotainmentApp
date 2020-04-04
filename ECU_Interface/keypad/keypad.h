/*
 * keypad.h
 *
 *  Created on: Jan 4, 2020
 *      Author: H
 */

#ifndef MCAL_KEYPAD_KEYPAD_H_
#define MCAL_KEYPAD_KEYPAD_H_

#include "infra_structure/std_types.h"
#include "infra_structure/avr.h"
#include "infra_structure/common_macros.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define N_col 3
#define N_row 4

/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT PORTC
#define KEYPAD_PORT_IN  PINC
#define KEYPAD_PORT_DIR DDRC


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Function responsible for getting the pressed keypad key
 */
uint8_t KeyPad_getPressedKey(void);


#endif /* MCAL_KEYPAD_KEYPAD_H_ */
