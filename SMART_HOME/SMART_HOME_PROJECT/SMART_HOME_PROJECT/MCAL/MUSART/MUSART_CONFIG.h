/*
 * MUSART_CONFIG.h
 *
 * Created: 23/03/2023 8:54:33 PM
 *  Author: Misra
 */ 


#ifndef MUSART_CONFIG_H_
#define MUSART_CONFIG_H_

//we have two mode sycn & Async
#define mode_for_UART	 ASYNC_MODE


//here we have 2 types of XCK in sync mode only :master mode and slave mode
#define XCK_IN_SYNC_MODE_ONLY	MASTER_MODE


//here we have normal speed and double_speed
#define speed_of_Async_mode		 DOUBLE_SPEED




#define SIZE_OF_DATA			 EIGHT_BIT_DATA



#endif /* MUSART_CONFIG_H_ */