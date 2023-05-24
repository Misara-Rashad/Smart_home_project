/*
 * HLED_CONFIG.c
 *
 * Created: 20/02/2023 9:49:38 PM
 *  Author: Misra
 */ 


/*............includes section........*/
//libraries
#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"
#include "../../Libraries_/ATMega32_Registers.h"

//MCAL
#include "../../MCAL/MDIO/MDIO_INTERFACE.h"



//HAL
#include "HLED_CONFIG.h"
#include "HLED_INTERFACE.h"

LED_T HLED_arrayofleds[NUM_OF_LEDS]=
{
	[HLED_NUM0]={	 .structpin={MDIO_PIN2,MDIO_PORTC,MDIO_OUTPUT,MDIO_HIGH},
					 .enumoutputlevel=ACTIVE_HIGH_LED },
					 
	[HLED_NUM1]={	 .structpin={MDIO_PIN7,MDIO_PORTC,MDIO_OUTPUT,MDIO_HIGH}, 
					 .enumoutputlevel=ACTIVE_HIGH_LED },
					 
	[HLED_NUM2]={	 .structpin={MDIO_PIN3,MDIO_PORTD,MDIO_OUTPUT,MDIO_HIGH} ,
					 .enumoutputlevel=ACTIVE_HIGH_LED }

};