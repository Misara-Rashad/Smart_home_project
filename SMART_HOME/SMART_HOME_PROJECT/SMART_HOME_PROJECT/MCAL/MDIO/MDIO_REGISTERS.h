/*
 * MDIO_REGISTERS.h
 *
 * Created: 19/02/2023 12:43:47 AM
 *  Author: Misra
 */ 


#ifndef MDIO_REGISTERS_H_
#define MDIO_REGISTERS_H_

//in this file we assign names and addresses for all DIO registers that we will use in ATMEGA32


/*1. we create names for registers in DIO for example PINX_REGISTER,DDRX_REGISTER,PORTX_REGISTER
2. we write commands for this registers to use it easily 
---->the way we assign a value for a register by getting its address from data sheet and make type-casting
then dereference
for example 
PIND_REGISTER has address of 0x30
we make type-casting for this address ---->    (volatile u8*)0x30
we make dereference to add value to this register------>   *(volatile u8*)0x30
*/


//portA registers
#define  PINA_REGISTER   *((volatile u8*)0x39)
#define  DDRA_REGISTER   *((volatile u8*)0x3A)
#define  PORTA_REGISTER  *((volatile u8*)0x3B)


//portB registers
#define  PINB_REGISTER   *((volatile u8*)0x36)
#define  DDRB_REGISTER   *((volatile u8*)0x37)
#define  PORTB_REGISTER  *((volatile u8*)0x38)


//portC registers
#define  PINC_REGISTER   *((volatile u8*)0x33)
#define  DDRC_REGISTER   *((volatile u8*)0x34)
#define  PORTC_REGISTER  *((volatile u8*)0x35)



//portD registers
#define  PIND_REGISTER   *((volatile u8*)0x30)
#define  DDRD_REGISTER   *((volatile u8*)0x31)
#define  PORTD_REGISTER  *((volatile u8*)0x32)

#endif /* MDIO_REGISTERS_H_ */