/*
 * SOS.h
 *
 *  Created on: Dec 31, 2019
 *      Author: H
 */

#ifndef SOS_SOS_H_
#define SOS_SOS_H_
/***********************INCLUDES*************************/
#include "infra_structure/std_types.h"
#include "infra_structure/common_macros.h"
#include "infra_structure/avr.h"
#include "MCAL/DIO/DIO.h"
#include "MCAL/TIMER/TIMER_Driver.h"
#include "sos_ret_val.h"
#include "avr/interrupt.h"
#include "app/game.h"
/**************TYPE_DEF*********************************/

typedef uint8_t ERROR_SOS_TYPE; /*defining a return error type*/

typedef void (*Ptr_Func)(void); /*ptr to function type definition*/

/******************************MACROS*********************************************************/
#define SOS_RESOLUTION (1u)
#define TASK_FUNCTIONALITY_ONESHOT 2u
#define TASK_FUNCTIONALITY_PERIODIC 1u
#define FREQ 8000u
#define TASKS_MAX_NUMBER 15


/******************************Function_Prototype***********************************************/

/*Description: Small Operating System Initialization
 * Input     : The tick of the system that you will build the tasks on
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern ERROR_SOS_TYPE SOS_Init(uint8_t au8_SystemResolution);

/*Description: SOS Create task Function
 * Input     :  (TMU_Periodicity (IN Millie Seconds), TMU_Functionaity(One_shot,Periodic), Callback Function Written by the user)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern ERROR_SOS_TYPE SOS_Create (uint32_t au8_SOS_Periodicity, uint8_t au8_SOS_Functionality,Ptr_Func CallBack, uint8_t au8_periority);

/* Description: Function to stop the task
* Input  : CALL_BACK Function
* Output : Error Checking
*/
extern ERROR_SOS_TYPE SOS_Stop(Ptr_Func CallBack);

/*
 * Description: Tasks Scheduling for execution
 */
extern void SOS_Schedular (void);


#endif /* SOS_SOS_H_ */
