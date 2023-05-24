/*
 * MDIO_PROGRAM.c
 *
 * Created: 19/02/2023 12:41:46 AM
 *  Author: Misra
 */ 


/*...........includes section..........*/
//libraries
#include "../../Libraries_/LIB_STDTypes.h"


//MCAL
#include "MDIO_INTERFACE.h"
// i got errors that u8 & tenumFncErrorState undeclared so i included the STDTYPES file
// i got errors that MDIO_PORTA undeclared so i included MDIO_INTERFACE

/*........................................*/

//functions implementation
//1.init func
/*void voidinitMDIO_MDIO(void)
{
	// 3led in AMit Board

		enumpindirection_MDIO(&led0); //led0
		enumpindirection_MDIO(&led1); //led1
		enumpindirection_MDIO(&led2); //led2	
}*/


//2.direction of port or pin
tenumFncErrorState pin_direction(DIO_PIN* pstructcpy_pin)
{
	if(pstructcpy_pin->enumport <MDIO_PORTA || pstructcpy_pin->enumport> MDIO_PORTD
	 || pstructcpy_pin->enumpin <MDIO_PIN0 || pstructcpy_pin->enumpin >MDIO_PIN7
	||pstructcpy_pin->enummode <MDIO_INPUT || pstructcpy_pin->enummode >MDIO_OUTPUT)
	{
		return 	LSTY_OUT_OF_RANGE ;

	}
	
	else
	{
		switch(pstructcpy_pin->enumport)
		{
			case MDIO_PORTA:
			if(pstructcpy_pin->enummode==MDIO_INPUT)
			{
				CLR_BIT(DDRA_REGISTER,pstructcpy_pin->enumpin);
			}
			else
			{
				SET_BIT(DDRA_REGISTER,pstructcpy_pin->enumpin);
			}
			break;

			case MDIO_PORTB:
			if(pstructcpy_pin->enummode==MDIO_INPUT)
			{
				CLR_BIT(DDRB_REGISTER,pstructcpy_pin->enumpin);
			}
			else
			{
				SET_BIT(DDRB_REGISTER,pstructcpy_pin->enumpin);
			}
			break;			

			case MDIO_PORTC:
			if(pstructcpy_pin->enummode==MDIO_INPUT)
			{
				CLR_BIT(DDRC_REGISTER,pstructcpy_pin->enumpin);
			}
			else
			{
				SET_BIT(DDRC_REGISTER,pstructcpy_pin->enumpin);
			}
			break;
			
			case MDIO_PORTD:
			if(pstructcpy_pin->enummode==MDIO_INPUT)
			{
				CLR_BIT(DDRD_REGISTER,pstructcpy_pin->enumpin);
			}
			else
			{
				SET_BIT(DDRD_REGISTER,pstructcpy_pin->enumpin);
			}			
			break;			
		}
		return LSTY_EXECUTED_SUCCESSFULLY;
	}
}

//2.direction of port or pin
tenumFncErrorState port_direction(DIO_PORT* pstructcpy_port)
{
	if(pstructcpy_port->enumport <MDIO_PORTA || pstructcpy_port->enumport >MDIO_PORTD 
	||pstructcpy_port->enummode <MDIO_INPUT || pstructcpy_port->enummode >MDIO_OUTPUT)
	{
		return 	LSTY_OUT_OF_RANGE ;

	}
	
	else
	{
		switch(pstructcpy_port->enumport)
		{
			case MDIO_PORTA:
			if(pstructcpy_port->enummode ==MDIO_INPUT)
			{
				DDRA_REGISTER=0x00;
			}
			else
			{
				DDRA_REGISTER=0xff;
			}
			break;

			case MDIO_PORTB:
			if(pstructcpy_port->enummode ==MDIO_INPUT)
			{
				DDRB_REGISTER=0x00;
			}
			else
			{
				DDRB_REGISTER=0xff;
			}
			break;

			case MDIO_PORTC:
			if(pstructcpy_port->enummode ==MDIO_INPUT)
			{
				DDRC_REGISTER=0x00;
			}
			else
			{
				DDRC_REGISTER=0xff;
			}
			break;
			
			case MDIO_PORTD:
			if(pstructcpy_port->enummode ==MDIO_INPUT)
			{
				DDRD_REGISTER=0x00;
			}
			else
			{
				DDRA_REGISTER=0xff;
			}
			break;
		}
		return LSTY_EXECUTED_SUCCESSFULLY;
	}
}


//3.pin
tenumFncErrorState pin_value(DIO_PIN* pstructcpy_pin)
{
	if(pstructcpy_pin->enumport <MDIO_PORTA || pstructcpy_pin->enumport >MDIO_PORTD 
	|| pstructcpy_pin->enumpin <MDIO_PIN0 || pstructcpy_pin->enumpin >MDIO_PIN7
	||pstructcpy_pin->enumoutputlevel <MDIO_LOW || pstructcpy_pin->enumoutputlevel >MDIO_HIGH)
	{
		return 	LSTY_OUT_OF_RANGE ;

	}
	
	else
	{
		switch(pstructcpy_pin->enumport)
		{
			case MDIO_PORTA:
			if(pstructcpy_pin->enumoutputlevel==MDIO_LOW)
			{
				CLR_BIT(PORTA_REGISTER,pstructcpy_pin->enumpin);
			}
			else
			{
				SET_BIT(PORTA_REGISTER,pstructcpy_pin->enumpin);
			}
			break;

			case MDIO_PORTB:
			if(pstructcpy_pin->enumoutputlevel ==MDIO_LOW)
			{
				CLR_BIT(PORTB_REGISTER,pstructcpy_pin->enumpin);
			}
			else
			{
				SET_BIT(PORTB_REGISTER,pstructcpy_pin->enumpin);
			}
			break;

			case MDIO_PORTC:
			if(pstructcpy_pin->enumoutputlevel ==MDIO_LOW)
			{
				CLR_BIT(PORTC_REGISTER,pstructcpy_pin->enumpin);
			}
			else
			{
				SET_BIT(PORTC_REGISTER,pstructcpy_pin->enumpin);
			}
			break;
			
			case MDIO_PORTD:
			if(pstructcpy_pin->enumoutputlevel ==MDIO_LOW)
			{
				CLR_BIT(PORTD_REGISTER,pstructcpy_pin->enumpin);
			}
			else
			{
				SET_BIT(PORTD_REGISTER,pstructcpy_pin->enumpin);
			}
			break;
		}
		return LSTY_EXECUTED_SUCCESSFULLY;
	}
}



tenumFncErrorState pin_value_selection(DIO_PIN* pstructcpy_pin,OUTPUT_LEVEL enumoutputlevel)
{
	if(pstructcpy_pin->enumport <MDIO_PORTA || pstructcpy_pin->enumport >MDIO_PORTD
	|| pstructcpy_pin->enumpin <MDIO_PIN0 || pstructcpy_pin->enumpin >MDIO_PIN7
	||pstructcpy_pin->enumoutputlevel <MDIO_LOW || pstructcpy_pin->enumoutputlevel >MDIO_HIGH)
	{
		return 	LSTY_OUT_OF_RANGE ;

	}
	
	else
	{
		switch(pstructcpy_pin->enumport)
		{
			case MDIO_PORTA:
			if(enumoutputlevel==MDIO_LOW)
			{
				CLR_BIT(PORTA_REGISTER,pstructcpy_pin->enumpin);
			}
			else
			{
				SET_BIT(PORTA_REGISTER,pstructcpy_pin->enumpin);
			}
			break;

			case MDIO_PORTB:
			if(enumoutputlevel==MDIO_LOW)
			{
				CLR_BIT(PORTB_REGISTER,pstructcpy_pin->enumpin);
			}
			else
			{
				SET_BIT(PORTB_REGISTER,pstructcpy_pin->enumpin);
			}
			break;

			case MDIO_PORTC:
			if(enumoutputlevel==MDIO_LOW)
			{
				CLR_BIT(PORTC_REGISTER,pstructcpy_pin->enumpin);
			}
			else
			{
				SET_BIT(PORTC_REGISTER,pstructcpy_pin->enumpin);
			}
			break;
			
			case MDIO_PORTD:
			if(enumoutputlevel==MDIO_LOW)
			{
				CLR_BIT(PORTD_REGISTER,pstructcpy_pin->enumpin);
			}
			else
			{
				SET_BIT(PORTD_REGISTER,pstructcpy_pin->enumpin);
			}
			break;
		}
		return LSTY_EXECUTED_SUCCESSFULLY;
	}	
}



//3.pin
tenumFncErrorState pin_toggle(DIO_PIN* pstructcpy_pin)
{
		if(pstructcpy_pin->enumport <MDIO_PORTA || pstructcpy_pin->enumport >MDIO_PORTD
		|| pstructcpy_pin->enumpin <MDIO_PIN0 || pstructcpy_pin->enumpin >MDIO_PIN7)
	{
			return LSTY_OUT_OF_RANGE;
	}
	else
	{
		switch(pstructcpy_pin->enumport)
		{
			case MDIO_PORTA:
			Toggle_BIT(PORTA_REGISTER,pstructcpy_pin->enumpin);
			break;
			
			case MDIO_PORTB:
			Toggle_BIT(PORTB_REGISTER,pstructcpy_pin->enumpin);
			break;
			
			case MDIO_PORTC:
			Toggle_BIT(PORTC_REGISTER,pstructcpy_pin->enumpin);		
			break;
			
			case MDIO_PORTD:
			Toggle_BIT(PORTD_REGISTER,pstructcpy_pin->enumpin);
			break;									
		}
		return LSTY_EXECUTED_SUCCESSFULLY;
	}
}

//3.pin
tenumFncErrorState pin_get_value(DIO_PIN* pstructcpy_pin,pu8 pu8cpy_pin_value)
{
	if(pu8cpy_pin_value==NULL)
	{
		return LSTY_NULL_POINTER;
	}
	else if (pstructcpy_pin->enumport <MDIO_PORTA || pstructcpy_pin->enumport >MDIO_PORTD 
	|| pstructcpy_pin->enumpin <MDIO_PIN0 || pstructcpy_pin->enumpin >MDIO_PIN7)
	{
		return LSTY_OUT_OF_RANGE;
	}
	else
	{
		switch(pstructcpy_pin->enumport)
		{
		case MDIO_PORTA:
		*pu8cpy_pin_value=GET_BIT(PINA_REGISTER,pstructcpy_pin->enumpin);
		
		break;
		
		case MDIO_PORTB:
		*pu8cpy_pin_value=GET_BIT(PINB_REGISTER,pstructcpy_pin->enumpin);
		break;
		
		case MDIO_PORTC:
		*pu8cpy_pin_value=GET_BIT(PINC_REGISTER,pstructcpy_pin->enumpin);
		break;
		
		case MDIO_PORTD:
		*pu8cpy_pin_value=GET_BIT(PIND_REGISTER,pstructcpy_pin->enumpin);
		break;					
		}
	}
	return LSTY_EXECUTED_SUCCESSFULLY;
}



//4.port
tenumFncErrorState port_value(DIO_PORT* pstructcpy_port,u8 u8cpy_value )
{
	if(pstructcpy_port->enumport <MDIO_PORTA || pstructcpy_port->enumport >MDIO_PORTD 
	||pstructcpy_port->enumoutputlevel<MDIO_LOW || pstructcpy_port->enumoutputlevel>MDIO_HIGH)
	{
		return 	LSTY_OUT_OF_RANGE ;

	}
	
	else
	{
		switch(pstructcpy_port->enumport)
		{
			case MDIO_PORTA:
			PORTA_REGISTER=u8cpy_value;
			break;

			case MDIO_PORTB:
			PORTB_REGISTER=u8cpy_value;
			break;

			case MDIO_PORTC:
			PORTC_REGISTER=u8cpy_value;
			break;
			
			case MDIO_PORTD:
			PORTD_REGISTER=u8cpy_value;
			break;
		}
		return LSTY_EXECUTED_SUCCESSFULLY;
	}	
}