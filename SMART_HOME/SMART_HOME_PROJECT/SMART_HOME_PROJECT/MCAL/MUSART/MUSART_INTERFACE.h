/*
 * MUSART_INTERFACE.h
 *
 * Created: 23/03/2023 8:55:06 PM
 *  Author: Misra
 */ 


#ifndef MUSART_INTERFACE_H_
#define MUSART_INTERFACE_H_


#include "MUSART_REGISTERS.h"
#include "MUSART_CONFIG.h"


#define SYNC_MODE    0
#define ASYNC_MODE   1


#define MASTER_MODE  2
#define SLAVE_MODE   3


#define NORMAL_SPEED 4
#define DOUBLE_SPEED 5



#define WRITE_RISING_EDGE_READ_FALLING_EDGE  9   //@ UCPOL=0
#define READ_RISING_EDGE_WRITE_FALLING_EDGE  10  //@ UCPOL=1


#define FIVE_BIT_DATA   11
#define SIX_BIT_DATA	12
#define SEVEN_BIT_DATA	13
#define EIGHT_BIT_DATA	14
#define NINE_BIT_DATA	15


#define ODD_PARITY		16
#define EVEN_PARITY		17
#define NO_PARITY_CHECK	18

#define ONE_STOP_BIT	19
#define TWO_STOP_BIT	20



//functions prototype
tenumFncErrorState UART_INIT(void);
tenumFncErrorState UART_send_byte(u8 u8data_to_be_send);
tenumFncErrorState UART_receive_byte(pu8 pu8variable);


#endif /* MUSART_INTERFACE_H_ */