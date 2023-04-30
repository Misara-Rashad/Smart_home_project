/*
 * MINT_REGISTERS.h
 *
 * Created: 02/03/2023 12:04:45 AM
 *  Author: Misra
 */ 


#ifndef MINT_REGISTERS_H_
#define MINT_REGISTERS_H_


/* Interrupt vectors */
#define _VECTOR(N) __vector_ ## N
/* External Interrupt Request 0 */
#define INT0_vect			_VECTOR(1)
/* External Interrupt Request 1 */
#define INT1_vect			_VECTOR(2)
/* External Interrupt Request 2 */
#define INT2_vect			_VECTOR(3)



//registers used in interrupt
#define SREG   (*( volatile u8*)0x5F)  //to enable Global interrupt 

#define GICR   (*( volatile u8*)0x5B)  // PIE(peripheral interrupt enable)
#define GIFR   (*( volatile u8*)0x5A)  // PIF(peripheral interrupt flag)

#define MCUCR  (*( volatile u8*)0x55)  //MCU control register to control INT0,INT1
#define MCUCSR (*( volatile u8*)0x54)  //MCU Control and Status Register to control INT2




/* SREG */
#define I		7  //global interrupt enable

/* GICR */
#define INT1    7
#define INT0    6
#define INT2    5
#define IVSEL   1
#define IVCE    0

/* GIFR */
#define INTF1   7
#define INTF0   6
#define INTF2   5

/* MCUCR */
#define ISC11   3
#define ISC10   2
#define ISC01   1
#define ISC00   0

/* MCUCSR */
#define ISC2    6




#endif /* MINT_REGISTERS_H_ */