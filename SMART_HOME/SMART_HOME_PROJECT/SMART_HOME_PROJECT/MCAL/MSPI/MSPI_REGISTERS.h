/*
 * MSPI_REGISTERS.h
 *
 * Created: 13/04/2023 4:38:07 PM
 *  Author: Misra
 */ 


#ifndef MSPI_REGISTERS_H_
#define MSPI_REGISTERS_H_


/* SPI */
#define   SPCR         (*((volatile u8*)0x2D))
#define   SPSR         (*((volatile u8*)0x2E))
#define   SPDR         (*((volatile u8*)0x2F))


/* Serial Transfer Complete */
#define SPI_STC_vect			_VECTOR(12)


/* SPSR */
#define SPIF    7
#define WCOL    6
/* bits 5-1 reserved */
#define SPI2X   0

/* SPCR */
#define SPIE    7
#define SPE     6
#define DORD    5
#define MSTR    4
#define CPOL    3
#define CPHA    2
#define SPR1    1
#define SPR0    0


#endif /* MSPI_REGISTERS_H_ */