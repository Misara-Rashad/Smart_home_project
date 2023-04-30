/*
 * H7SEG_INTERFACE.h
 *
 * Created: 21/02/2023 1:28:08 AM
 *  Author: Misra
 */ 


#ifndef H7SEG_INTERFACE_H_
#define H7SEG_INTERFACE_H_


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
void voidinit7seg_H7SEG(void);
void void7seg_enable_one_H7SEG(SSD_T* pstructcpy_pin);
void void7seg_disable_one_H7SEG(SSD_T* pstructcpy_pin);
void void7seg_sendnumber_H7SEG(SSD_T* pstructcpy_pin,Register regcpy_num);
void void7seg_clear_H7SEG(SSD_T* pstructcpy_pin);
void void7seg_enable_one_disable_all_H7SEG(SSD_T* pstructcpy_pin);
#endif /* H7SEG_INTERFACE_H_ */