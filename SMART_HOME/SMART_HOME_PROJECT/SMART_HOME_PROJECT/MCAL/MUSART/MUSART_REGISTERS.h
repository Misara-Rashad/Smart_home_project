/*
 * MUSART_REGISTERS.h
 *
 * Created: 23/03/2023 8:55:26 PM
 *  Author: Misra
 */ 


#ifndef MUSART_REGISTERS_H_
#define MUSART_REGISTERS_H_

/* USART */
#define   UBRRL        (*((volatile u8*)0x29))   //USART_BAUD_RATE_REGISTER UBRR
#define   UCSRB        (*((volatile u8*)0x2A))
#define   UCSRA        (*((volatile u8*)0x2B))
#define   UDR          (*((volatile u8*)0x2C))



/* USART, Rx Complete */
#define USART_RXC_vect			_VECTOR(13)

/* USART Data Register Empty */
#define USART_UDRE_vect			_VECTOR(14)

/* USART, Tx Complete */
#define USART_TXC_vect			_VECTOR(15)


/* UCSRA */
#define RXC     7
#define TXC     6
#define UDRE    5
#define FE      4
#define DOR     3
#define PE      2
#define U2X     1
#define MPCM    0

/* UCSRB */
#define RXCIE   7
#define TXCIE   6
#define UDRIE   5
#define RXEN    4
#define TXEN    3
#define UCSZ2   2
#define RXB8    1
#define TXB8    0

/* UCSRC */
#define URSEL   7
#define UMSEL   6
#define UPM1    5
#define UPM0    4
#define USBS    3
#define UCSZ1   2
#define UCSZ0   1
#define UCPOL   0

#endif /* MUSART_REGISTERS_H_ */