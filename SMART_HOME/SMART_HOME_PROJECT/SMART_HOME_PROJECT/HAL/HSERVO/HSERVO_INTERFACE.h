/*
 * HSERVO_INTERFACE.h
 *
 * Created: 16/05/2023 12:33:42 AM
 *  Author: Misra
 */ 


#ifndef HSERVO_INTERFACE_H_
#define HSERVO_INTERFACE_H_

//timer 2 will control all servo motors

//functions declaration
tenumFncErrorState servo_init(u8 u8angle,pf32 pf32variable);
tenumFncErrorState servo_start(f32 f32on_time);


#endif /* HSERVO_INTERFACE_H_ */