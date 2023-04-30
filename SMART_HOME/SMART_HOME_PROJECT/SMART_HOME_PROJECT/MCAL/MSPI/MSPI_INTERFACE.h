/*
 * MSPI_INTERFACE.h
 *
 * Created: 13/04/2023 4:37:33 PM
 *  Author: Misra
 */ 


#ifndef MSPI_INTERFACE_H_
#define MSPI_INTERFACE_H_

#include "MSPI_REGISTERS.h"
#include "MSPI_CONFIG.h"


//macros


#define INTERRUPT_DISABLED	0
#define INTERRUPT_ENABLED	1

#define	SPI_DISABLED		0
#define	SPI_ENABLED			1 

#define the_MSB_of_the_data_word_is_transmitted_first	0
#define the_LSB_of_the_data_word_is_transmitted_first	1

#define SPI_MASTER			0
#define SPI_SLAVE 			1

#define CLOCK_POLARITY_SCK_is_low_when_idle			0
#define CLOCK_POLARITY_SCK_is_high_when_idle		1

#define CLOCK_PHASE_SAMPLE_ON_LEADING_SETUP_ON_TRAILING		0
#define CLOCK_PHASE_SETUO_ON_LEADING_SAMPLE_ON_TRAILING		1

#define Fosc_4				4
#define Fosc_16				16
#define Fosc_64				64
#define Fosc_128			128
//double speed
#define Fosc_2				2
#define Fosc_8				8
#define Fosc_32				32
#define Fosc_64				64




//functions interface
//master init
void voidinitspi_master_MSPI(void);
/*..................*/
//slave init
void voidinitspi_slave_MSPI(void);
/*..................*/

void voidspi_master_transmit_byte_MSPI(u8 data);
u8 u8spi_master_receive_byte_MSPI(void);

void voidspi_slave_transmit_byte_MSPI(u8 data);
u8	 u8spi_slave_receive_byte_MSPI(void);

#endif /* MSPI_INTERFACE_H_ */