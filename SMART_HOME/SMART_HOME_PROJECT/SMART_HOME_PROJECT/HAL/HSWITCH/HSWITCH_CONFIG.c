/*
 * HSWITCH_CONFIG.c
 *
 * Created: 19/02/2023 6:30:51 PM
 *  Author: Misra
 */ 


/*...............includes section..........*/
//libraries
#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"
#include "../../Libraries_/ATMega32_Registers.h"

//MCAL
#include "../../MCAL/MDIO/MDIO_CONFIG.h"
#include "../../MCAL/MDIO/MDIO_INTERFACE.h"
#include "../../MCAL/MDIO/MDIO_REGISTERS.h"


//HAL
#include "HSWITCH_CONFIG.h"
#include "HSWITCH_INTERFACE.h"



SWITCH_T HSWITCHES_arrayofswitches[NUM_OF_SWITCHES]=
{
	[HSWITCH_NUM0]={ .structpin={MDIO_PIN0,MDIO_PORTB,MDIO_INPUT,MDIO_LOW},
					.enummode=ACTIVE_HIGH_SWITCH
					},
	[HSWITCH_NUM1]={ .structpin={MDIO_PIN6,MDIO_PORTD,MDIO_INPUT,MDIO_LOW},
					.enummode=ACTIVE_HIGH_SWITCH
					},	
	[HSWITCH_NUM2]={ .structpin={MDIO_PIN2,MDIO_PORTD,MDIO_INPUT,MDIO_LOW},
				.enummode=ACTIVE_HIGH_SWITCH
				}		
		
};

