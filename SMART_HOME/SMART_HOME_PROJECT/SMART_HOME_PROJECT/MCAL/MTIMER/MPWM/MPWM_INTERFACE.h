/*
 * MPWM_INTERFACE.h
 *
 * Created: 11/03/2023 9:29:07 PM
 *  Author: Misra
 */ 


#ifndef MPWM_INTERFACE_H_
#define MPWM_INTERFACE_H_

//libraries
#include "../../../Libraries_/LIB_STDTypes.h"
#include "../../../Libraries_/LIB_BMNP.h"
#include "../../../Libraries_/ATMega32_Registers.h"


typedef enum{
	MPWM_NUM0,MPWM_NUM1,MPWM_NUM2
	}MPWM_NUM;

typedef enum{
	MPWM_FASTPWM,MPWM_PHASECORRECT,MPWM_PHASE_AND_FREQUENCY_CORRECT
	}MPWM_PWMMODE;
	
typedef enum{
	MPWM_INVERTED,MPWM_NON_INVERTED
}MPWM_OP_FORMAT;



typedef enum{
	MPWM_BUSY,MPWM_FREE
}MPWM_state;


typedef enum{
	EIGHT_BIT,NINE_BIT,TEN_BIT
	}MPWM_NO_OF_BITS;

typedef struct{
	MPWM_NUM		enumpwm_num;
	MPWM_PWMMODE	enumpwm_mode;
	MPWM_OP_FORMAT	enumpwm_op_format;
	MPWM_state		enumstate_of_timer;
	u8 u8output_compare_unit;
	MPWM_NO_OF_BITS enumno_of_bits;	
}MPWM_T;
	
	
MPWM_T HPWM_arrayofpwm[NUM_OF_PWM];





//functions prototype
void voidinitpwm_MPWM(MPWM_T* ptostruct);
void voidpwm_change_duty_cycle_MPWM(u8 u8cpy_value_to_OCRn,MPWM_T* ptostruct);
void voidpwm_disable_MPWM(MPWM_T* ptostruct);


#endif /* MPWM_INTERFACE_H_ */