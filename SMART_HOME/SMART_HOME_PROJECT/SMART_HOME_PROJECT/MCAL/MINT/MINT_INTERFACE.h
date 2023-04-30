/*
 * MINT_INTERFACE.h
 *
 * Created: 02/03/2023 12:03:43 AM
 *  Author: Misra
 */ 


#ifndef MINT_INTERFACE_H_
#define MINT_INTERFACE_H_

#include "MINT_REGISTERS.h"
#include "MINT_CONFIG.h"

#define MINT_DISABLE 0
#define MINT_ENABLE 1

typedef enum{
	MINT_ISC_LOW_LEVEL,MINT_ISC_ANY_LOGIC,MINT_ISC_FALLING_EDGE,MINT_ISC_RISING_EDGE
}MINT_RESPONSE_LEVEL;

typedef enum{
	MINT_EXINT0,MINT_EXINT1,MINT_EXINT2
}MINT_EXINTS;

typedef enum{
	MINT_FLAG_CLEAR,MINT_FLAG_SET
}MINT_INTFLAGVALUE;


void voidinitinterrupt_MINT(void);
void voidINTExitCriticalSection_MINT(void);
void voidINTEnterCriticalSection_MINT(void);
void voidINTGETFlag_MINT(MINT_EXINTS enumCpy_ExInt, pu8 pu8Cpy_INTFlag);
void voidINTSETFlag_MINT(MINT_EXINTS enumCpy_ExInt, MINT_INTFLAGVALUE enumCpy_INTFlagValue);
void voidINTENABLEHandler_MINT(MINT_EXINTS enumCpy_ExInt,MINT_RESPONSE_LEVEL enumcpy_response_level);
void voidINTDISABLEHandler_MINT(MINT_EXINTS enumCpy_ExInt);
void voidINTSetCallBack_MINT(void (*ptr) (void), MINT_EXINTS enumCpy_ExInt);

#endif /* MINT_INTERFACE_H_ */