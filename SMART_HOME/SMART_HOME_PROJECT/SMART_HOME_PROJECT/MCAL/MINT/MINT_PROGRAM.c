/*
 * MINT_PROGRAM.c
 *
 * Created: 02/03/2023 12:05:09 AM
 *  Author: Misra
 */ 

/*..........includes sections..........*/
//libraries
#include <avr/interrupt.h>   //this include is for ISR(interrupt service routine)
#include "../../Libraries_/LIB_STDTypes.h"
#include "MINT_INTERFACE.h"



//pointer to function
static void (* EXINT_CALLBACK[3]) (void); //static to only be used in this file .c


tenumFncErrorState interrupt_initT(void)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	SET_BIT(SREG,I);  //enable global interrupt	
	return error;
}

tenumFncErrorState INTExitCriticalSection(void)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	CLR_BIT(SREG,I);
	return error;	
}


tenumFncErrorState INTEnterCriticalSection(void)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;	
	SET_BIT(SREG,I);
	return error;	
}


tenumFncErrorState INTGETFlag(MINT_EXINTS enumCpy_ExInt, pu8 pu8Cpy_INTFlag)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==pu8Cpy_INTFlag)
	{
		error=LSTY_NULL_POINTER;
	}
	else if(enumCpy_ExInt<MINT_EXINT0 || enumCpy_ExInt>MINT_EXINT2)
	{
		error=LSTY_OUT_OF_RANGE;	
	}
	else
	{
			switch(enumCpy_ExInt)
			{
				case MINT_EXINT0:
				*pu8Cpy_INTFlag=GET_BIT(GIFR,INTF0);
				break;
				
				case MINT_EXINT1:
				*pu8Cpy_INTFlag=GET_BIT(GIFR,INTF1);
				break;
				
				case MINT_EXINT2:
				*pu8Cpy_INTFlag=GET_BIT(GIFR,INTF2);
				break;
				
				default:
				break;
			}
	}
	return error;

}


tenumFncErrorState INTSETFlag(MINT_EXINTS enumCpy_ExInt, MINT_INTFLAGVALUE enumCpy_INTFlagValue)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (	enumCpy_ExInt<MINT_EXINT0 || enumCpy_ExInt>MINT_EXINT2 
		||enumCpy_INTFlagValue<MINT_FLAG_CLEAR ||enumCpy_INTFlagValue>MINT_FLAG_SET)
	{
		error=LSTY_OUT_OF_RANGE;
	}
	else
	{
	switch(enumCpy_ExInt)
	{
		case MINT_EXINT0:
		if (enumCpy_INTFlagValue == MINT_FLAG_SET)
		{
			SET_BIT(GIFR,INTF0);
		}
		else
		{
			CLR_BIT(GIFR,INTF0);
		}
		break;
		
		case MINT_EXINT1:
		if (enumCpy_INTFlagValue == MINT_FLAG_SET)
		{
			SET_BIT(GIFR,INTF1);
		}
		else
		{
			CLR_BIT(GIFR,INTF1);
		}
		break;
		
		case MINT_EXINT2:
		if (enumCpy_INTFlagValue == MINT_FLAG_SET)
		{
			SET_BIT(GIFR,INTF2);
		}
		else
		{
			CLR_BIT(GIFR,INTF2);
		}
		break;
		
		default:
		break;
	}	
	}
	return error;
	
}


tenumFncErrorState INTENABLEHandler(MINT_EXINTS enumCpy_ExInt,MINT_RESPONSE_LEVEL enumcpy_response_level)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (enumCpy_ExInt<MINT_EXINT0 || enumCpy_ExInt>MINT_EXINT2
		||enumcpy_response_level<MINT_ISC_LOW_LEVEL || enumcpy_response_level>MINT_ISC_RISING_EDGE)
	{
		error=LSTY_OUT_OF_RANGE;
	}
	else
	{
			switch(enumCpy_ExInt)
	{
		case MINT_EXINT0:
		SET_BIT(GICR,INT0);
		switch(enumcpy_response_level)
		{
			case MINT_ISC_LOW_LEVEL:
			CLR_BIT(MCUCR,ISC00); //low level generates interrupt
			CLR_BIT(MCUCR,ISC01);
			break;
			
			case MINT_ISC_ANY_LOGIC:
			SET_BIT(MCUCR,ISC00); //any logical change generates interrupt
			CLR_BIT(MCUCR,ISC01);
			break;
			
			case MINT_ISC_FALLING_EDGE:
			CLR_BIT(MCUCR,ISC00); //falling edge generates interrupt
			SET_BIT(MCUCR,ISC01);
			break;
			
			case MINT_ISC_RISING_EDGE:
			SET_BIT(MCUCR,ISC00); //rising edge generates interrupt
			SET_BIT(MCUCR,ISC01);
			break;
			
			default:
			break;
		}	
		break;
		
		case MINT_EXINT1:
		SET_BIT(GICR,INT1);
		switch(enumcpy_response_level)
		{
			case MINT_ISC_LOW_LEVEL:
			CLR_BIT(MCUCR,ISC10); //low level generates interrupt
			CLR_BIT(MCUCR,ISC11);
			break;
			
			case MINT_ISC_ANY_LOGIC:
			SET_BIT(MCUCR,ISC10); //any logical change generates interrupt
			CLR_BIT(MCUCR,ISC11);
			break;
			
			case MINT_ISC_FALLING_EDGE:
			CLR_BIT(MCUCR,ISC10); //falling edge generates interrupt
			SET_BIT(MCUCR,ISC11);
			break;
			
			case MINT_ISC_RISING_EDGE:
			SET_BIT(MCUCR,ISC10); //rising edge generates interrupt
			SET_BIT(MCUCR,ISC11);
			break;
			
			default:
			break;
		}		
		break;
		
		case MINT_EXINT2:
		SET_BIT(GICR,INT2);
		switch(enumcpy_response_level)
		{
			case MINT_ISC_LOW_LEVEL:
			#warning "you cannot make an interrupt by setting  low level int .....try falling or rising edge only in EXTERNAL INT2"
			break;
			
			case MINT_ISC_ANY_LOGIC:
			#warning "you cannot make an interrupt by setting any logical change int .....try falling or rising edge only in EXTERNAL INT2"
			break;
			
			case MINT_ISC_FALLING_EDGE:
			CLR_BIT(MCUCSR,ISC2); //falling edge generates interrupt
			break;
			
			case MINT_ISC_RISING_EDGE:
			SET_BIT(MCUCSR,ISC2); //rising edge generates interrupt
			break;
			
			default:
			break;
		}
		/*note that --->When changing the ISC2 bit, an interrupt can occur. Therefore, it is recommended
		to first disable INT2 by clearing its Interrupt Enable bit in the GICR Register. Then,
		the ISC2 bit can be changed. Finally, the INT2 Interrupt Flag should be cleared by writing a logical
		one to its Interrupt Flag bit (INTF2) in the GIFR Register before the interrupt is re-enabled.*/
		break;
		
		default:
		break;
	}	
	}
	return error;

}


tenumFncErrorState INTDISABLEHandler(MINT_EXINTS enumCpy_ExInt)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (enumCpy_ExInt<MINT_EXINT0 || enumCpy_ExInt>MINT_EXINT2)
	{
		error=LSTY_OUT_OF_RANGE;
	}
	else
	{
			switch(enumCpy_ExInt)
			{
				case MINT_EXINT0:
				CLR_BIT(GICR,INT0);
				break;
				
				case MINT_EXINT1:
				CLR_BIT(GICR,INT1);
				break;
				
				case MINT_EXINT2:
				CLR_BIT(GICR,INT2);
				break;
				
				default:
				break;
			}
	}
	return error;
	
}




/* This function is being called in main.c to hold an address of another function that have the ISR written by user */
    /* Since the function is being passed to CB function is local we use the global varible "pointer to function" 
        to assign to it the address of the ISR function passed to CallBack function */
tenumFncErrorState INTSetCallBack(void (*ptr) (void), MINT_EXINTS enumCpy_ExInt)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==ptr)
	{
		error=LSTY_NULL_POINTER;
	}
	else if (enumCpy_ExInt<MINT_EXINT0 || enumCpy_ExInt>MINT_EXINT2)
	{
		error=LSTY_OUT_OF_RANGE;
	}
	else
	{
		switch(enumCpy_ExInt)
		{
			case MINT_EXINT0:
			EXINT_CALLBACK[0]=ptr;
			break;
			
			case MINT_EXINT1:
			EXINT_CALLBACK[1]=ptr;
			break;
			
			case MINT_EXINT2:
			EXINT_CALLBACK[2]=ptr;
			break;
			
			default:
			break;
		}	
	}
	return error;

}



//isr functions to be called using pointer to function in main.c
ISR(INT0_vect)
{
	EXINT_CALLBACK[0]();
}


ISR(INT1_vect)
{
	EXINT_CALLBACK[1]();
}

ISR(INT2_vect)
{
	EXINT_CALLBACK[2]();
}
