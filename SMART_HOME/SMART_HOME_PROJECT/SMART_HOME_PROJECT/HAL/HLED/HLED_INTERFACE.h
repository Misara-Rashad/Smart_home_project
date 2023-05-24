/*
 * HLED_INTERFACE.h
 *
 * Created: 20/02/2023 9:50:24 PM
 *  Author: Misra
 */ 


#ifndef HLED_INTERFACE_H_
#define HLED_INTERFACE_H_


//includes
#include "../../Libraries_/LIB_STDTypes.h"
#include "HLED_CONFIG.h"

typedef enum{
	ACTIVE_LOW_LED,ACTIVE_HIGH_LED
	}MODE_OF_OPERATION_LED;

typedef struct
{
DIO_PIN structpin;
MODE_OF_OPERATION_LED enumoutputlevel;	
}LED_T;


LED_T HLED_arrayofleds[NUM_OF_LEDS];





//functions prototype
tenumFncErrorState led_init(void);
tenumFncErrorState led_on(LED_T* pstructcpy_pin);
tenumFncErrorState led_off(LED_T* pstructcpy_pin);
tenumFncErrorState led_toggle(LED_T* pstructcpy_pin);
tenumFncErrorState led_control_brightness(u8 u8cpy_value_to_OCRn);  



#endif /* HLED_INTERFACE_H_ */