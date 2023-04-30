/*
 * MUSART_PROGRAM.c
 *
 * Created: 23/03/2023 8:54:05 PM
 *  Author: Misra
 */ 

//includes section
#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"
#include "../../Libraries_/ATMega32_Registers.h"

#include "MUSART_INTERFACE.h"
#include "MUSART_CONFIG.h"
#include "MUSART_REGISTERS.h"




//functions implementation
void voidinitUART_MUSART(void)
{
	#if speed_of_Async_mode == NORMAL_SPEED   
	CLR_BIT(UCSRA,U2X);
	SET_BIT(UCSRA,MPCM);
	
			#if SIZE_OF_DATA == EIGHT_BIT_DATA
			CLR_BIT(UCSRB,UCSZ2);
			
			SET_BIT(UCSRC,URSEL);
			UCSRC=0b10111110;		//ASYNC  -8_bit_data	-ODD_PARITY		-2stop_bits
			
			//to set 9600 BAUD rate and U2X=0
			CLR_BIT(UCSRC,URSEL);
			UBRRH=0  ;  //contains the four most significant bits
			UBRRL=103 ; //contains the eight least significant bits
			#endif	

	#elif speed_of_Async_mode == DOUBLE_SPEED
	SET_BIT(UCSRA,U2X);
	SET_BIT(UCSRA,MPCM);
	
			#if SIZE_OF_DATA == EIGHT_BIT_DATA
			CLR_BIT(UCSRB,UCSZ2);
			
			SET_BIT(UCSRC,URSEL);
			UCSRC=0b10111110;		//ASYNC  -8_bit_data	-ODD_PARITY		-2stop_bits
			
			//to set 9600 BAUD rate and U2X=1
			CLR_BIT(UCSRC,URSEL);
			UBRRH=0   ;  //contains the four most significant bits 
			UBRRL=207 ; //contains the eight least significant bits 
			#endif



	#endif	
}



void voidUART_send_byte(u8 u8data_to_be_send)
{
	SET_BIT(UCSRB,TXEN);
	
	while (!GET_BIT(UCSRA,UDRE));
	
	UDR=u8data_to_be_send;
}




u8 u8UART_receive_byte(void)
{
	SET_BIT(UCSRB,RXEN);
	
	while (!GET_BIT(UCSRA,RXC));
	
	return UDR;
}