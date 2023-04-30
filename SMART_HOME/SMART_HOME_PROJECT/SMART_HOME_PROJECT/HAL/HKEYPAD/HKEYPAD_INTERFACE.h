/*
 * HKEYPAD_INTERFACE.h
 *
 * Created: 23/02/2023 4:10:29 PM
 *  Author: Misra
 */ 


#ifndef HKEYPAD_INTERFACE_H_
#define HKEYPAD_INTERFACE_H_


//includes
#include "../../Libraries_/LIB_STDTypes.h"

#include "HKEYPAD_CONFIG.h"

typedef struct{
DIO_PIN rows[NUM_OF_ROWS_KEYPAD]; 
DIO_PIN colums[NUM_OF_COLUMS_KEYPAD];

}KEYPAD_T;


KEYPAD_T HKEYPAD_arrayofkeypads[NUM_OF_KEYPADS];


//functions prototype
void voidinitkeypad_HKEYPAD(void);
tenumFncErrorState enumkeypadgetnumber_HKEYPAD(KEYPAD_T* pstructcpy,pu8 pu8cpy_value);

#endif /* HKEYPAD_INTERFACE_H_ */