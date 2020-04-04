

#include "DIO.h"

uint8_t DIO_INIT_Pin (uint8_t Pin_Number, uint8_t direction)
{
	if((Pin_Number>= A0) && (Pin_Number<= A7))
	{
		if(direction==OUTPUT)
		{
			SET_BIT(DDRA, Pin_Number);
		}
		if(direction==INPUT)
		{
			CLEAR_BIT(DDRA, Pin_Number);
		}
		return ERROR_OK;
	}
	if((Pin_Number>=B0) && (Pin_Number<=B7))
	{
		if(direction==OUTPUT)
		{
			SET_BIT(DDRB, (Pin_Number%8));
		}
		if(direction==INPUT)
		{
			CLEAR_BIT(DDRB, (Pin_Number%8));
		}
		return ERROR_OK;
	}
	if((Pin_Number>=C0) && (Pin_Number<=C7))
	{

		if(direction==OUTPUT)
		{
			SET_BIT(DDRC,(Pin_Number%8));
		}
		if(direction==INPUT)
		{
			CLEAR_BIT(DDRC,(Pin_Number%8));
		}
		return ERROR_OK;
	}
	if((Pin_Number>=D0) && (Pin_Number<=D7))
	{
		if(direction==OUTPUT)
		{
			SET_BIT(DDRD, (Pin_Number%8));
		}
		if(direction==INPUT)
		{
			CLEAR_BIT(DDRD, (Pin_Number%8));
		}
		return ERROR_OK;
	}
	else {
		return ERROR_NOK;
	}
}

uint8_t DIO_INIT_PORT (uint8_t Port_Name, uint8_t direction)
{
	if(Port_Name ==PA)
	{
		if(direction==OUTPUT)
		{
			DDRA=0xFF;
		}
		else if(direction==INPUT)
		{
			DDRA=0x00;
		}
		return ERROR_OK;
	}
	else if(Port_Name ==PB)
	{
		if(direction==OUTPUT)
		{
			DDRB=0xFF;
		}
		else if(direction==INPUT)
		{
			DDRB=0x00;
		}
		return ERROR_OK;
	}
	else if(Port_Name ==PC)
	{
		if(direction==OUTPUT)
		{
			DDRC=0xFF;
		}
		else if(direction==INPUT)
		{
			DDRC=0x00;
		}
		return 	ERROR_OK;
	}
	else if(Port_Name ==PD)
	{
		if(direction==OUTPUT)
		{
			DDRD=0xFF;
		}
		else if(direction==INPUT)
		{
			DDRD=0x00;
		}
		return ERROR_OK;
	}
	else
	{
		return ERROR_NOK;
	}
}
uint8_t DIO_Write_pin (uint8_t Pin_Number, uint8_t Data)
{
	if((Pin_Number>=A0) && (Pin_Number<=A7))
	{
		if(Data == HIGH)
		{
			SET_BIT(PORTA,Pin_Number);
		}
		if(Data == LOW)
		{
			CLEAR_BIT(PORTA, Pin_Number);
		}
		return ERROR_OK;
	}
	if((Pin_Number>=B0) && (Pin_Number<=B7))
	{
		if(Data==HIGH)
		{
			SET_BIT(PORTB,(Pin_Number%8));
		}
		if(Data==LOW)
		{
			CLEAR_BIT(PORTB, (Pin_Number%8));
		}
		return ERROR_OK;
	}
	if((Pin_Number>=C0) && (Pin_Number<=C7))
	{

		if(Data==HIGH)
		{
			SET_BIT(PORTC,Pin_Number%8);
		}
		if(Data==LOW)
		{
			CLEAR_BIT(PORTC,Pin_Number%8);
		}
		return ERROR_OK;
	}
	if((Pin_Number>=D0) && (Pin_Number<=D7))
	{
		if(Data==HIGH)
		{
			SET_BIT(PORTD,(Pin_Number%8));
		}
		if(Data==LOW)
		{
			CLEAR_BIT(PORTD, (Pin_Number%8));
		}
		return ERROR_OK;
	}
	else
	{
		return ERROR_NOK;
	}
}

uint8_t DIO_Read_Pin (uint8_t Pin_Number, volatile uint8_t * ReadData)
{
	if((Pin_Number>=A0) && (Pin_Number<=A7))
	{
		if (BIT_IS_SET(PINA,Pin_Number))
		{
			*ReadData=1;
		}
		if (BIT_IS_CLEAR(PINA, Pin_Number))
		{
			*ReadData=0;
		}
		return ERROR_OK;
	}
	if((Pin_Number>=B0) && (Pin_Number<=B7))
	{
		if (BIT_IS_SET(PINB, (Pin_Number%8)))
		{
			*ReadData=1;
		}
		if (BIT_IS_CLEAR(PINB, (Pin_Number%8)))
		{
			*ReadData=0;
		}
		return ERROR_OK;
	}
	if((Pin_Number>=C0) && (Pin_Number<=C7))
	{
		if (BIT_IS_SET(PINC,(Pin_Number%8)))
		{
			*ReadData=1;
		}
		if (BIT_IS_CLEAR(PINC, (Pin_Number%8)))
		{
			*ReadData=0;
		}
		return ERROR_OK;
	}
	if((Pin_Number>=D0) && (Pin_Number<=D7))
	{
		if (BIT_IS_SET(PIND,(Pin_Number%8)))
		{
			*ReadData=1;
		}
		if (BIT_IS_CLEAR(PIND, (Pin_Number%8)) )
		{
			*ReadData=0;
		}
		return ERROR_OK;
	}
	else
	{
		return ERROR_NOK;
	}

}
uint8_t DIO_Write_Port (uint8_t Port_Name, uint8_t Data)
{
	if(Port_Name ==PA)
	{
		PORTA= Data;
		return ERROR_OK;
	}
	if(Port_Name ==PB)
	{
		PORTB= Data;
		return ERROR_OK;
	}
	if(Port_Name ==PC)
	{
		PORTC= Data;
		return ERROR_OK;
	}
	if(Port_Name ==PD)
	{
		PORTD= Data;
		return ERROR_OK;
	}
	else{
		return ERROR_NOK;
	}
}

uint8_t DIO_Read_Port (uint8_t Port_Name, volatile uint8_t * ReadData)
{
	if(Port_Name ==PA)
	{
		*ReadData= PINA;
		return ERROR_OK;
	}
	else if(Port_Name ==PB)
	{
		*ReadData= PINB;
		return ERROR_OK;
	}
	else if(Port_Name ==PC)
	{
		*ReadData= PINC;
		return ERROR_OK;
	}
	else if(Port_Name ==PD)
	{
		*ReadData= PIND;
		return ERROR_OK;
	}
	else
	{
		return ERROR_NOK;
	}
}

uint8_t DIO_Activate_Pullup (uint8_t Pin_Number)
{
	if((Pin_Number>=A0) && (Pin_Number<=A7))
	{
		SET_BIT(PORTA, Pin_Number);
		return ERROR_OK;
	}
	if((Pin_Number>=B0) && (Pin_Number<=B7))
	{
		SET_BIT(PORTB, ((Pin_Number%8)-1));
		return ERROR_OK;
	}
	if((Pin_Number>=C0) && (Pin_Number<=C7))
	{
		SET_BIT(PORTC, ((Pin_Number%8)-1));
		return ERROR_OK;
	}
	if((Pin_Number>=D0) && (Pin_Number<=D7))
	{
		SET_BIT(PORTD,((Pin_Number%8)-1));
		return ERROR_OK;
	}
	else
	{
		return ERROR_NOK;
	}
}
uint8_t DIO_Diactivate_Pullup (uint8_t Pin_Number)
{
	if((Pin_Number>=A0) && (Pin_Number<A7))
	{
		CLEAR_BIT(PORTA, Pin_Number);
		return ERROR_OK;
	}
	if((Pin_Number>=B0) && (Pin_Number<=B7))
	{
		CLEAR_BIT(PORTB, ((Pin_Number%8)-1));
		return ERROR_OK;
	}
	if((Pin_Number>=C0) && (Pin_Number<=C7))
	{
		CLEAR_BIT(PORTC, ((Pin_Number%8)-1));
		return ERROR_OK;
	}
	if((Pin_Number>=D0) && (Pin_Number<=D7))
	{
		CLEAR_BIT(PORTD, ((Pin_Number%8)-1));
		return ERROR_OK;
	}
	else
	{
		return ERROR_NOK;
	}
}
