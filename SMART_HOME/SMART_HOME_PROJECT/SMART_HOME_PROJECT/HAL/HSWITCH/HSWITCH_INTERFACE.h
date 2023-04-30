/*
 * HSWITCH_INTERFACE.h
 *
 * Created: 19/02/2023 6:31:29 PM
 *  Author: Misra
 */ 


#ifndef HSWITCH_INTERFACE_H_
#define HSWITCH_INTERFACE_H_

#include "HSWITCH_CONFIG.h"

typedef enum
{
	ACTIVE_LOW_SWITCH,ACTIVE_HIGH_SWITCH
	}MODES_OF_OPERATION_SWITCH;

//active_LOW means it needs 0 logic to be active........ connected to pull up resistor
//active_HIGH means it needs 1 logic to be active........ connected to pull down resistor --->in AMIT KIT


typedef enum{
	NOT_PRESSED,PRESSED
}SWITCH_STATUS;

typedef struct
{
	DIO_PIN structpin;
	MODES_OF_OPERATION_SWITCH enummode;
	SWITCH_STATUS enumstatus_of_switch;
}SWITCH_T;


SWITCH_T HSWITCHES_arrayofswitches[NUM_OF_SWITCHES];




//functions prototype
void voidinitSWITCH_HSWITCH(void);
tenumFncErrorState enumswitchgetvalue_HSWITCH(SWITCH_T* pstruct_cpy,pu8 pu8cpy_pin);

#endif /* HSWITCH_INTERFACE_H_ */