/*
 * Timer_Driver.c
 *
 *  Created on: Dec 14, 2019
 *      Author: H
 */


#include"Timer_Driver.h"
static uint8_t Prescaler_Timer[NO_OF_CHANNELS]={'\0','\0' ,'\0'};  /*Array to Copy Prescaler for each Timer Channel from Init to Start*/
static uint8_t Mode_Timer[NO_OF_CHANNELS]={'\0','\0' ,'\0'};       /*Array to Copy Mode for each Timer Channel from Init to Start*/
uint8_t Timer_Init(Str_TimerConfiguration_t* Confg_S)
{
	uint8_t u8_error=NULL;
	switch(Confg_S->Timer_Channel)
	{
	case TIMER0:
		switch(Confg_S->Timer_Mode)
		{
		case TIMER_MODE:
		case COUNTER_MODE:
			SET_BIT(TCCR0,7);
			SET_BIT(TCCR0,3);
			CLEAR_BIT(TCCR0,6);
			CLEAR_BIT(TCCR0,4); /*configuring timer0 output compare mode and non pwm*/
			CLEAR_BIT(TCCR0,5);
			Prescaler_Timer[TIMER0]= Confg_S->Timer_Psc;
			break;
		default:
			u8_error=ERROR_NOK;
			break;
		}
		switch(Confg_S->Interrupt_Mode)
		{
		case POLLING:
			Mode_Timer[TIMER0]= Confg_S->Interrupt_Mode;
			SET_BIT(TIMSK,1);
			break;
		case INTERRUPT:
			SET_BIT(TIMSK,1); /*enable output compare interrupt oc timer 0*/
			Mode_Timer[TIMER0]= Confg_S->Interrupt_Mode;
			break;
		default:
			u8_error= ERROR_NOK;
			break;
		}
		break;
	case TIMER1:
		switch(Confg_S->Timer_Mode)
		{
		case TIMER_MODE:
		case COUNTER_MODE:
			CLEAR_BIT(TCCR1A,6); /*Setting COMPA Channel  IN TIMER 1 as Output Compare Match mode*/
			CLEAR_BIT(TCCR1A,7);
			Prescaler_Timer[TIMER1]= Confg_S->Timer_Psc; /*moving prescaler to global variable*/
			break;
		default:
			u8_error=ERROR_NOK;
			break;
		}
		switch(Confg_S->Interrupt_Mode)
		{
		case POLLING:
			Mode_Timer[TIMER1]= Confg_S->Interrupt_Mode; /*moving Interrupt Mode to global variable*/
			SET_BIT(TIMSK,4); /*OC1A INTEERUPT Enable*/
			break;
		case INTERRUPT:
			SET_BIT(TIMSK,4); /*OC1A INTEERUPT Enable*/
			Mode_Timer[TIMER1]= Confg_S->Interrupt_Mode;  /*moving Interrupt Mode to global variable*/
			break;
		default:
			u8_error= ERROR_NOK;
			break;
		}
		break;
	default:
		u8_error= ERROR_NOK;
		break;
	}
	return u8_error;
}
uint8_t Timer_Start(uint8_t Copy_uint8_TimerChannel,uint32_t Copy_uint32_TickCounts)
{
	volatile uint8_t Error_Check_TickCounts;
	switch (Copy_uint8_TimerChannel)
	{
	case TIMER0:
		TCCR0 &= 0XF8;
		TCCR0|= Prescaler_Timer[TIMER0];
		if((Copy_uint32_TickCounts<=255) && (Copy_uint32_TickCounts>0))
		{
			TCNT0 =0;
			OCR0=Copy_uint32_TickCounts;
			Error_Check_TickCounts=ERROR_OK;
		}
		else
		{
			Error_Check_TickCounts=ERROR_NOK;
		}
		if(Mode_Timer[TIMER0]==POLLING)
		{
			while(BIT_IS_CLEAR(TIFR,1));
			SET_BIT(TIFR,1);
			Error_Check_TickCounts=ERROR_OK;
		}
		else if(Mode_Timer[TIMER0]==INTERRUPT)
		{
			SET_BIT(SREG,7); /*enable global interrupt*/
			Error_Check_TickCounts=ERROR_OK;
		}
		else
		{
			Error_Check_TickCounts=ERROR_NOK;
		}
		break;
	case TIMER1:
		TCCR1B &= 0XF8;
		TCCR1B |= Prescaler_Timer[TIMER1];
		if((Copy_uint32_TickCounts<=65000) && (Copy_uint32_TickCounts>0))
		{
			TCNT1 =0;
			OCR1A=Copy_uint32_TickCounts;
			Error_Check_TickCounts=ERROR_OK;
		}
		else
		{
			Error_Check_TickCounts=ERROR_NOK;
		}
		if(Mode_Timer[TIMER1]==POLLING)
		{
			while(BIT_IS_CLEAR(TIFR,4));
			SET_BIT(TIFR,4);
			Error_Check_TickCounts=ERROR_OK;
		}
		else if(Mode_Timer[TIMER1]==INTERRUPT)
		{
			SET_BIT(SREG,7); /*enable global interrupt*/
			Error_Check_TickCounts=ERROR_OK;
		}
		else
		{
			Error_Check_TickCounts=ERROR_NOK;
		}
		break;

	}
	return Error_Check_TickCounts;
}


uint8_t Timer_Stop(uint8_t Copy_uint8_TimerChannel)
{
	switch(Copy_uint8_TimerChannel)
	{
	case TIMER0:
		TCCR0 &= 0XF8;
		TCCR0|=NO_CLOCK_TIMER_0;
		return ERROR_OK;
		break;
	case TIMER1:
		TCCR1B &= 0XF8;
		TCCR1B|=NO_CLOCK_TIMER_0;
		return ERROR_OK;
	default:
	return ERROR_NOK;
	break;
	}
}

uint8_t Timer_Reset(uint8_t Copy_uint8_TimerChannel)
{
	switch(Copy_uint8_TimerChannel)
	{
	case TIMER0:
		TCNT0=0;
		return ERROR_OK;
	case TIMER1:
		TCNT1=0;
		return ERROR_OK;
	default:
		return ERROR_NOK;
	}
}
uint8_t Timer_Get_FlagStatus(uint8_t Copy_uint8_TimerChannel, uint8_t *Copy_uint8Ptr_FlagStatus)
{
	switch(Copy_uint8_TimerChannel)
	{
	case TIMER0:
		*Copy_uint8Ptr_FlagStatus= GET_BIT(TIFR,1);
		return ERROR_OK;
		break;
	case TIMER1:
		*Copy_uint8Ptr_FlagStatus= GET_BIT(TIFR,4);
		return ERROR_OK;
		break;
	default:
	return ERROR_NOK;
	break;
	}
}
