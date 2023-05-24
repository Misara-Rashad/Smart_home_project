/*
 * HDC_MOTOR_INTERFACE.h
 *
 * Created: 22/05/2023 9:39:43 AM
 *  Author: Misra
 */ 


#ifndef HDC_MOTOR_INTERFACE_H_
#define HDC_MOTOR_INTERFACE_H_

//includes
#include "../../Libraries_/LIB_STDTypes.h"

#include "../../MCAL/MDIO/MDIO_INTERFACE.h"

//data types
typedef struct{
	DIO_PIN ENABLE;
	DIO_PIN IN1;
	DIO_PIN IN2;
}MOTOR_T;

//functions declaration
tenumFncErrorState Motor_init(MOTOR_T* ptomotor_structs);
tenumFncErrorState Motor_right(MOTOR_T* ptomotor_structs);
tenumFncErrorState Motor_left(MOTOR_T* ptomotor_structs);
tenumFncErrorState Motor_stop(MOTOR_T* ptomotor_structs);
tenumFncErrorState Motor_control_speed(MOTOR_T* ptomotor_structs);


#endif /* HDC_MOTOR_INTERFACE_H_ */