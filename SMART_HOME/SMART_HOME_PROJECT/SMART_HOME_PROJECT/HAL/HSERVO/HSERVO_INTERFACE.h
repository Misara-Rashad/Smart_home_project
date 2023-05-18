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
f32 f32initservo_HSERVO(u8 u8angle);
void voidservo_start_HSERVO(f32 f32on_time);


#endif /* HSERVO_INTERFACE_H_ */