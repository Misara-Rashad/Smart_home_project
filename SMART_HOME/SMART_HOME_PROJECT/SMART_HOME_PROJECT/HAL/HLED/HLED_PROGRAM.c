/*
 * HLED_PROGRAM.c
 *
 * Created: 20/02/2023 9:50:05 PM
 *  Author: Misra
 */ 


/*............includes section........*/
//libraries
#include "../../Libraries_/LIB_STDTypes.h"

//MCAL
#include "../../MCAL/MDIO/MDIO_INTERFACE.h"

//HAL
#include "HLED_INTERFACE.h"




//include pwm to enable led control brightness
#include "../../MCAL/MTIMER/MPWM/MPWM_INTERFACE.h"


//functions implementation
tenumFncErrorState led_init(void)
{	
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	u8 i;
	for(i=0;i<NUM_OF_LEDS;i++)
	{
			pin_direction(&HLED_arrayofleds[i].structpin);
	}
	return error;
}


tenumFncErrorState led_on(LED_T* pstructcpy_pin)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==pstructcpy_pin)
	{
		error=LSTY_NULL_POINTER;
	}
	else
	{
		if((pstructcpy_pin->enumoutputlevel=ACTIVE_HIGH_LED))
		{
			pstructcpy_pin->structpin.enumoutputlevel=MDIO_HIGH;
			pin_value(&pstructcpy_pin->structpin);
		}
		else //ACTIVE_LOW_LED
		{
			pstructcpy_pin->structpin.enumoutputlevel=MDIO_LOW;
			pin_value(&pstructcpy_pin->structpin);
		}
	}
	return error;
	
}


tenumFncErrorState led_off(LED_T* pstructcpy_pin)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==pstructcpy_pin)
	{
		error=LSTY_NULL_POINTER;
	}
	else
	{
		if((pstructcpy_pin->enumoutputlevel=ACTIVE_HIGH_LED))
		{
			pstructcpy_pin->structpin.enumoutputlevel=MDIO_LOW;
			pin_value(&pstructcpy_pin->structpin);
		}
		else //ACTIVE_LOW_LED
		{
			pstructcpy_pin->structpin.enumoutputlevel=MDIO_HIGH;
			pin_value(&pstructcpy_pin->structpin);
		}
	}
	return error;
	
}



tenumFncErrorState led_toggle(LED_T* pstructcpy_pin)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==pstructcpy_pin)
	{
		error=LSTY_NULL_POINTER;
	}
	else
	{
		pin_toggle(&pstructcpy_pin->structpin);
	}
	return error;

}




tenumFncErrorState led_control_brightness(u8 u8cpy_value_to_OCRn)   //set OC0 for example
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	PWM_init_MPWM(&HPWM_arrayofpwm[0]);
		
	pwm_change_duty_cycle_MPWM(u8cpy_value_to_OCRn,&HPWM_arrayofpwm[0]);
	return error;
}
