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
void voidinitLED_HLED(void);
void voidledon_HLED(LED_T* pstructcpy_pin);
void voidledoff_HLED(LED_T* pstructcpy_pin);
void voidledtoggle_HLED(LED_T* pstructcpy_pin);
void voidledcontrolbrightness_HLED(u8 u8cpy_value_to_OCRn);  



#endif /* HLED_INTERFACE_H_ */