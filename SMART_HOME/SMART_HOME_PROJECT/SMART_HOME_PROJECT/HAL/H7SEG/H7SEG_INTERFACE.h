/*
 * H7SEG_INTERFACE.h
 *
 * Created: 21/02/2023 1:28:08 AM
 *  Author: Misra
 */ 


#ifndef H7SEG_INTERFACE_H_
#define H7SEG_INTERFACE_H_

#include "H7SEG_CONFIG.h"

typedef enum
{
COMMON_ANODE,COMMON_CATHODE	
}MODES_OF_7SEG;

//COMMON_ANODE means that common pin is connected to vcc(+) and it needs 0 to be active
//COMMON_ANODE means that common pin is connected to GND(-) and it needs 1 to be active

typedef struct
{
DIO_PIN A;
DIO_PIN B;
DIO_PIN C;
DIO_PIN D;
DIO_PIN DOT;
DIO_PIN ENABLE;
MODES_OF_7SEG enummode;
}SSD_T;


SSD_T H7SEGarrayof7seg_H7SEG[NUM_OF_7SEG];



//functions declartion
tenumFncErrorState seven_segment_init(void);
tenumFncErrorState seven_segment_enable_one(SSD_T* pstructcpy_pin);
tenumFncErrorState seven_segment_disable_one(SSD_T* pstructcpy_pin);
tenumFncErrorState seven_segment_sendnumber(SSD_T* pstructcpy_pin,Register regcpy_num);
tenumFncErrorState seven_segment_clear(SSD_T* pstructcpy_pin);		//not defined
tenumFncErrorState seven_segment_enable_one_disable_all(SSD_T* pstructcpy_pin);	//not defined
#endif /* H7SEG_INTERFACE_H_ */