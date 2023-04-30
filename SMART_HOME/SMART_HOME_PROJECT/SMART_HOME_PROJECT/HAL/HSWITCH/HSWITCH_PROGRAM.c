/*
 * HSWITCH_PROGRAM.c
 *
 * Created: 19/02/2023 6:31:09 PM
 *  Author: Misra
 */ 


/*............includes section.............*/

//libraries
#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/ATMega32_Registers.h"
#include "../../Libraries_/LIB_BMNP.h"

//MCAL
#include "../../MCAL/MDIO/MDIO_CONFIG.h"
#include "../../MCAL/MDIO/MDIO_INTERFACE.h"
#include "../../MCAL/MDIO/MDIO_REGISTERS.h"

/*...............includes section..........*/
//libraries
#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"
#include "../../Libraries_/ATMega32_Registers.h"

//MCAL
#include "../../MCAL/MDIO/MDIO_CONFIG.h"
#include "../../MCAL/MDIO/MDIO_INTERFACE.h"
#include "../../MCAL/MDIO/MDIO_REGISTERS.h"



#include "HSWITCH_CONFIG.h"
#include "HSWITCH_INTERFACE.h"


//functions implementation
void voidinitSWITCH_HSWITCH(void)
{
for(u8 i=0;i<NUM_OF_SWITCHES;i++)
	{
	enumpindirection_MDIO(&HSWITCHES_arrayofswitches[i].structpin);
	}

}


tenumFncErrorState enumswitchgetvalue_HSWITCH(SWITCH_T* pstruct_cpy,pu8 pu8cpy_pin)
{
	u8 status_of_switch=NOT_PRESSED;
	if(pu8cpy_pin ==NULL)
	{
		return LSTY_NULL_POINTER;
	}
	else
	{
		if(pstruct_cpy->enummode == ACTIVE_HIGH_SWITCH )
		{
			enumpingetvalue_MDIO(&pstruct_cpy->structpin,&status_of_switch);
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
			enumpingetvalue_MDIO(&pstruct_cpy->structpin,&status_of_switch);
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
		return LSTY_EXECUTED_SUCCESSFULLY;
	}

}
