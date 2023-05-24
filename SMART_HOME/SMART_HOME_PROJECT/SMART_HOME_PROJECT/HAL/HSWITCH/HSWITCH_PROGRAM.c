/*
 * HSWITCH_PROGRAM.c
 *
 * Created: 19/02/2023 6:31:09 PM
 *  Author: Misra
 */ 



/*...............includes section..........*/
//libraries
#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"
#include "../../Libraries_/ATMega32_Registers.h"

//MCAL
#include "../../MCAL/MDIO/MDIO_INTERFACE.h"

#include "HSWITCH_INTERFACE.h"


//functions implementation
tenumFncErrorState SWITCH_INIT(void)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	for(u8 i=0;i<NUM_OF_SWITCHES;i++)
	{
	pin_direction(&HSWITCHES_arrayofswitches[i].structpin);
	}
	return error;
}


tenumFncErrorState switch_get_value(SWITCH_T* pstruct_cpy,pu8 pu8cpy_pin)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==pstruct_cpy || NULL==pu8cpy_pin)
	{
		error=LSTY_NULL_POINTER;
	}
	else
	{
			u8 status_of_switch=NOT_PRESSED;
			if(pstruct_cpy->enummode == ACTIVE_HIGH_SWITCH )
			{
				pin_get_value(&pstruct_cpy->structpin,&status_of_switch);
				if(status_of_switch == PRESSED)
				{
					*(pu8cpy_pin)=PRESSED;
				}
				else if(status_of_switch == NOT_PRESSED)
				{
					*(pu8cpy_pin)=NOT_PRESSED;
				}
				else
				{
				}
			}
			
			else if(pstruct_cpy->enummode == ACTIVE_LOW_SWITCH )
			{
				pin_get_value(&pstruct_cpy->structpin,&status_of_switch);
				if(status_of_switch == PRESSED)
				{
					*(pu8cpy_pin)=NOT_PRESSED;
				}
				else if(status_of_switch == NOT_PRESSED)
				{
					*(pu8cpy_pin)=PRESSED;
				}
				else
				{
				}
				
			}
			

	}
	return error;

}
