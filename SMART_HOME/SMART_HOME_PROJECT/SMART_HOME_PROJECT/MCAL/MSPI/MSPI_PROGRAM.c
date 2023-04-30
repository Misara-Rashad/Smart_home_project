/*
 * MSPI_PROGRAM.c
 *
 * Created: 13/04/2023 4:37:13 PM
 *  Author: Misra
 */ 




//includes
#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"

#include "../MDIO/MDIO_INTERFACE.h"

#include "MSPI_REGISTERS.h"
#include "MSPI_CONFIG.h"
#include "MSPI_INTERFACE.h"


//global variable declarations
DIO_PIN SS_PIN={
	.enumpin= MDIO_PIN4,
	.enumport= MDIO_PORTB,
	.enummode= MDIO_OUTPUT,
	.enumoutputlevel= MDIO_LOW
};


DIO_PIN MOSI_PIN={
	.enumpin= MDIO_PIN5,
	.enumport= MDIO_PORTB,
	.enummode= MDIO_OUTPUT,
	.enumoutputlevel= MDIO_HIGH
};

DIO_PIN MISO_PIN={
	.enumpin= MDIO_PIN6,
	.enumport= MDIO_PORTB,
	.enummode= MDIO_OUTPUT,
	.enumoutputlevel= MDIO_HIGH
};


DIO_PIN SCK_PIN={
	.enumpin= MDIO_PIN7,
	.enumport= MDIO_PORTB,
	.enummode= MDIO_OUTPUT,
	.enumoutputlevel= MDIO_HIGH
};



//functions implementation
//master init
void voidinitspi_master_MSPI(void)
{
	/* Set MOSI and SCK output, all others input */
	MOSI_PIN.enummode=MDIO_OUTPUT;
	SCK_PIN.enummode=MDIO_OUTPUT;
	MISO_PIN.enummode=MDIO_INPUT;
	enumpindirection_MDIO(&MOSI_PIN);
	enumpindirection_MDIO(&MISO_PIN);
	enumpindirection_MDIO(&SCK_PIN);
	//set ss to output & high
	SS_PIN.enummode=MDIO_OUTPUT;
	SS_PIN.enumoutputlevel=MDIO_HIGH;
	enumpindirection_MDIO(&SS_PIN);
	enumpinvalue_MDIO(&SS_PIN);
	
	/* Enable SPI, Master, set clock rate  */
	SET_BIT(SPCR,SPE);
	
	//When the DORD bit is written to zero, the MSB of the data word is transmitted first
	CLR_BIT(SPCR,DORD);
	
	//This bit selects Master SPI mode when written to one
	SET_BIT(SPCR,MSTR);
	
	//When this bit is written to one, SCK is high when idle.
	SET_BIT(SPCR,CPOL); //leading edge is falling edge
	SET_BIT(SPCR,CPHA); //reads on leading edge
	
	//sck=fck/16
	SET_BIT(SPCR,SPR0);
	CLR_BIT(SPCR,SPR1);
	SET_BIT(SPSR,SPI2X);


}
/*..................*/
//slave init
void voidinitspi_slave_MSPI(void)
{
	/* Set MISO output, all others input */
	MOSI_PIN.enummode=MDIO_INPUT;
	SCK_PIN.enummode=MDIO_INPUT;
	MISO_PIN.enummode=MDIO_OUTPUT;
	SS_PIN.enummode=MDIO_INPUT;
	enumpindirection_MDIO(&MOSI_PIN);
	enumpindirection_MDIO(&MISO_PIN);
	enumpindirection_MDIO(&SCK_PIN);
	enumpindirection_MDIO(&SS_PIN);
	
	//enable spi
	SET_BIT(SPCR,SPE);
	
	//This bit selects slave SPI mode when written to zero
	CLR_BIT(SPCR,MSTR);
	
	//When the DORD bit is written to zero, the MSB of the data word is transmitted first
	CLR_BIT(SPCR,DORD);
	
	//When this bit is written to one, SCK is high when idle.
	SET_BIT(SPCR,CPOL); //leading edge is falling edge
	SET_BIT(SPCR,CPHA); //reads on leading edge
}
/*..................*/

void voidspi_master_transmit_byte_MSPI(u8 data)
{
	//ss  low
	SS_PIN.enumoutputlevel=MDIO_LOW;
	enumpinvalue_MDIO(&SS_PIN);
	
	/* Start transmission */
	SPDR=data;
	
	/* Wait for transmission complete */
	while (!(GET_BIT(SPSR,SPIF)));
	
	//ss  high again
	SS_PIN.enumoutputlevel=MDIO_HIGH;
	enumpinvalue_MDIO(&SS_PIN);
}


u8 u8spi_master_receive_byte_MSPI(void)
{
	u8 x=0;
	//ss  low
	SS_PIN.enumoutputlevel=MDIO_LOW;
	enumpinvalue_MDIO(&SS_PIN);
	
	SPDR=x;				//dummy data
	
	/* Wait for transmission complete */
	while (!(GET_BIT(SPSR,SPIF)));
	x=SPDR;
	
	//ss  high again
	SS_PIN.enumoutputlevel=MDIO_HIGH;
	enumpinvalue_MDIO(&SS_PIN);
	
	return x;
}



void voidspi_slave_transmit_byte_MSPI(u8 data)
{
	SPDR=data;
}



u8	 u8spi_slave_receive_byte_MSPI(void)
{
	while (!(GET_BIT(SPSR,SPIF)));
	return SPDR;
}