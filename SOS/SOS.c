/*
 * SOS.c
 *
 *  Created on: Dec 31, 2019
 *      Author: H
 */
#include "sos.h"


/***********************LOCAL_MACROS*********************************/
#define Buffer_Task_Ready (1u)
#define Buffer_Task_NOTReady (0u)
#define Buffer_Task_Done (3u)

#define T_PRESCALER (1024U)

#define SOS_Execute_Tasks (0u)
#define SOS_No_Tasks_TO_EXECUTE (1u)

/***********************TYPEDEF************************************/
/*
 * BUFFER STRUCTURE TO HANDLE THE SOS TASKS
 */
typedef struct{
	Ptr_Func au32_PtrToFunc;
	uint32_t au32_Periodicity;
	uint32_t au32_Periodicity_New;
	uint8_t au8_Buffer_ID;
	uint8_t au8_Task_Status;
	uint8_t au8_Functionality;
}str_SOSBuffer;


/**************************global variables*****************************************/
static Str_TimerConfiguration_t gstr_Confg_Timer;
static uint8_t gu8_SOS_resolution=NULL;
static uint8_t gu8_Init_Flag=NULL;
static str_SOSBuffer gastr_SOSBuffer[TASKS_MAX_NUMBER];
static uint8_t gu8_TMU_BUFFER_NUMBER=NULL;
static uint8_t gu8_SOS_Status=NULL;
static uint32_t gu8_ISR_Flag=NULL;

/*************************FUNCTIONS_IMPLEMENTATION***********************************/

ERROR_SOS_TYPE SOS_Init(uint8_t au8_SystemResolution)
{
	uint8_t au8_error;
	if(au8_SystemResolution>=SOS_RESOLUTION)
	{
		if(au8_SystemResolution!=NULL)
		{
			/*initializing timer channel*/
			gstr_Confg_Timer.Timer_Channel=TIMER0;
			gstr_Confg_Timer.Timer_Psc= F_CPU_CLOCK_1024_TIMER_0;
			gstr_Confg_Timer.Interrupt_Mode=INTERRUPT;
			gstr_Confg_Timer.Timer_Mode= TIMER_MODE;
			gu8_SOS_resolution= au8_SystemResolution;
			Timer_Init(&gstr_Confg_Timer); /*calling function timer_init to initialize the timer*/
			au8_error=SOS_INIT_IS_INITIALIZED;
			gu8_Init_Flag++;
		}
		else
		{
			au8_error=SOS_INIT_RESOLUTION_NOT_DEFINED;
		}
	}
	else
	{
		au8_error=SOS_INIT_RESOLUTION_NOT_DEFINED;
	}
	return au8_error;
}

ERROR_SOS_TYPE SOS_Create(uint32_t au8_SOS_Periodicity, uint8_t au8_SOS_Functionality,Ptr_Func CallBack, uint8_t au8_periority)
{
	uint8_t au8_error=NULL;
	uint8_t au8_timer_counts=NULL;
	if(gu8_Init_Flag==TRUE)
	{
		if(gu8_TMU_BUFFER_NUMBER<TASKS_MAX_NUMBER)
		{
			if(gastr_SOSBuffer[au8_periority].au8_Task_Status==Buffer_Task_NOTReady)
			{
				if(au8_SOS_Functionality==TASK_FUNCTIONALITY_ONESHOT)
				{
					gastr_SOSBuffer[au8_periority].au8_Buffer_ID=au8_periority;
					gastr_SOSBuffer[au8_periority].au32_PtrToFunc=CallBack;
					gastr_SOSBuffer[au8_periority].au8_Functionality=TASK_FUNCTIONALITY_ONESHOT;
					gastr_SOSBuffer[au8_periority].au8_Task_Status=Buffer_Task_Ready;
					gastr_SOSBuffer[au8_periority].au32_Periodicity=au8_SOS_Periodicity;
					gastr_SOSBuffer[au8_periority].au32_Periodicity_New=au8_SOS_Periodicity;
					if(gu8_TMU_BUFFER_NUMBER==NULL)
					{
						au8_timer_counts=gu8_SOS_resolution;
						Timer_Start(TIMER0,au8_timer_counts);
					}
					gu8_TMU_BUFFER_NUMBER++;
					au8_error=SOS_CREATE_OK;
				}
				else if(au8_SOS_Functionality==TASK_FUNCTIONALITY_PERIODIC)
				{
					gastr_SOSBuffer[au8_periority].au8_Buffer_ID=au8_periority;
					gastr_SOSBuffer[au8_periority].au32_PtrToFunc=CallBack;
					gastr_SOSBuffer[au8_periority].au8_Functionality=TASK_FUNCTIONALITY_PERIODIC;
					gastr_SOSBuffer[au8_periority].au8_Task_Status=Buffer_Task_Ready;
					gastr_SOSBuffer[au8_periority].au32_Periodicity=au8_SOS_Periodicity;
					if(gu8_TMU_BUFFER_NUMBER==NULL)
					{
						au8_timer_counts=gu8_SOS_resolution;
						Timer_Start(TIMER0,au8_timer_counts);
					}
					gu8_TMU_BUFFER_NUMBER++;
					au8_error=SOS_CREATE_OK;
				}
				else
				{
					au8_error=SOS_CREATE_FUNCTIONALITY_NDEFINED;
				}
			}
			else
			{
				au8_error=SOS_CREATE_PRIORITY_IS_REDFEINED;
			}
		}
		else
		{
			au8_error=SOS_CREATE_BUFFER_FULL;
		}
	}
	return au8_error;
}
ERROR_SOS_TYPE SOS_Stop(Ptr_Func CallBack)
{
	uint8_t au8_loop=NULL;
	uint8_t au8_error=NULL;
	if(CallBack!=NULL)
	{
		for(au8_loop=0; au8_loop<TASKS_MAX_NUMBER; au8_loop++)
		{
			if(gastr_SOSBuffer[au8_loop].au32_PtrToFunc==CallBack)
			{
				if(gastr_SOSBuffer[au8_loop].au8_Task_Status==Buffer_Task_Done)
				{
					if(gastr_SOSBuffer[au8_loop].au8_Functionality==TASK_FUNCTIONALITY_PERIODIC)
					{
						gastr_SOSBuffer[au8_loop].au32_PtrToFunc=NULL;
						gastr_SOSBuffer[au8_loop].au8_Functionality=NULL;
						gastr_SOSBuffer[au8_loop].au8_Task_Status=Buffer_Task_NOTReady;
						gastr_SOSBuffer[au8_loop].au32_Periodicity=NULL;
						gastr_SOSBuffer[au8_loop].au32_Periodicity_New=NULL;
						gastr_SOSBuffer[au8_loop].au8_Buffer_ID=NULL;
						gu8_TMU_BUFFER_NUMBER--;
						au8_error=SOS_STOP_OK;
					}
					else
					{
						au8_error=SOS_STOP_TASK_IS_ONE_SHOT;
					}
				}
			}
			else
			{
				au8_error=SOS_STOP_TASK_NOT_FOUND;
			}
		}
	}
	else
	{
		au8_error=SOS_SOP_FUNC_NULL;
	}
	return au8_error;
}

void SOS_Schedular (void)
{
	uint8_t au8_loop;
	switch(gu8_SOS_Status)
	{
	case SOS_Execute_Tasks:
		for(au8_loop=0; au8_loop<TASKS_MAX_NUMBER; au8_loop++)
		{
			if(gastr_SOSBuffer[au8_loop].au8_Task_Status!=((Buffer_Task_NOTReady)))
			{
				if(gu8_ISR_Flag==(gastr_SOSBuffer[au8_loop].au32_Periodicity_New))
				{
						if(gastr_SOSBuffer[au8_loop].au8_Functionality==TASK_FUNCTIONALITY_PERIODIC)
						{
							gastr_SOSBuffer[au8_loop].au32_PtrToFunc();
							gastr_SOSBuffer[au8_loop].au8_Task_Status=Buffer_Task_Done;
							gastr_SOSBuffer[au8_loop].au32_Periodicity_New+=gastr_SOSBuffer[au8_loop].au32_Periodicity;
						}
						else if(gastr_SOSBuffer[au8_loop].au8_Functionality==TASK_FUNCTIONALITY_ONESHOT)
						{
							gastr_SOSBuffer[au8_loop].au32_PtrToFunc();
							gastr_SOSBuffer[au8_loop].au8_Functionality=NULL;
							gastr_SOSBuffer[au8_loop].au8_Buffer_ID=NULL;
							gastr_SOSBuffer[au8_loop].au8_Task_Status=Buffer_Task_NOTReady;
							gu8_TMU_BUFFER_NUMBER--;
						}
						else
						{

						}
				}
				else
				{

				}
			}
			else
			{

			}
		}
		gu8_SOS_Status=SOS_No_Tasks_TO_EXECUTE;
		break;
	case SOS_No_Tasks_TO_EXECUTE:
		break;
	}
}


ISR(TIMER0_COMP_vect)
{
	gu8_ISR_Flag++;
	gu8_SOS_Status=SOS_Execute_Tasks;
	if(gu8_ISR_Flag==255)
	{
		gu8_ISR_Flag=0;
		for(int au8_loop=0; au8_loop<TASKS_MAX_NUMBER; au8_loop++)
		{
			gastr_SOSBuffer[au8_loop].au32_Periodicity_New=0;
		}
	}
}
