/*
 * HLED_PROGRAM.c
 *
 * Created: 20/02/2023 9:50:05 PM
 *  Author: Misra
 */ 


/*............includes section........*/
//libraries
#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"
#include "../../Libraries_/ATMega32_Registers.h"

//MCAL
#include "../../MCAL/MDIO/MDIO_CONFIG.h"
#include "../../MCAL/MDIO/MDIO_INTERFACE.h"
#include "../../MCAL/MDIO/MDIO_REGISTERS.h"



//HAL
#include "HLED_CONFIG.h"
#include "HLED_INTERFACE.h"




//include pwm to enable led control brightness
#include "../../MCAL/MTIMER/MPWM/MPWM_CONFIG.h"
#include "../../MCAL/MTIMER/MPWM/MPWM_INTERFACE.h"


//functions implementation
void voidinitLED_HLED(void)
{	
	u8 i;
	for(i=0;i<NUM_OF_LEDS;i++)
	{
			enumpindirection_MDIO(&HLED_arrayofleds[i].structpin);
	}
}


void voidledon_HLED(LED_T* pstructcpy_pin)
{
	if((pstructcpy_pin->enumoutputlevel=ACTIVE_HIGH_LED))
	{
		pstructcpy_pin->structpin.enumoutputlevel=MDIO_HIGH;
		enumpinvalue_MDIO(&pstructcpy_pin->structpin);
	}
else //ACTIVE_LOW_LED
	{
		pstructcpy_pin->structpin.enumoutputlevel=MDIO_LOW;
		enumpinvalue_MDIO(&pstructcpy_pin->structpin);
	}
}


void voidledoff_HLED(LED_T* pstructcpy_pin)
{
	if((pstructcpy_pin->enumoutputlevel=ACTIVE_HIGH_LED))
	{
	pstructcpy_pin->structpin.enumoutputlevel=MDIO_LOW;
	enumpinvalue_MDIO(&pstructcpy_pin->structpin);
	}
else //ACTIVE_LOW_LED
{
	pstructcpy_pin->structpin.enumoutputlevel=MDIO_HIGH;
	enumpinvalue_MDIO(&pstructcpy_pin->structpin);
}
}



void voidledtoggle_HLED(LED_T* pstructcpy_pin)
{
	enumpintoggle_MDIO(&pstructcpy_pin->structpin);
}




void voidledcontrolbrightness_HLED(u8 u8cpy_value_to_OCRn)   //set OC0 for example
{
	
	voidinitpwm_MPWM(&HPWM_arrayofpwm[0]);
		
	voidpwm_change_duty_cycle_MPWM(u8cpy_value_to_OCRn,&HPWM_arrayofpwm[0]);

}
