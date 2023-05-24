/*
 * MSPI_PROGRAM.c
 *
 * Created: 13/04/2023 4:37:13 PM
 *  Author: Misra
 */ 




//includes
#include "../../Libraries_/LIB_STDTypes.h"

#include "../MDIO/MDIO_INTERFACE.h"

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
tenumFncErrorState spi_master_init(void)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	/* Set MOSI and SCK output, all others input */
	MOSI_PIN.enummode=MDIO_OUTPUT;
	SCK_PIN.enummode=MDIO_OUTPUT;
	MISO_PIN.enummode=MDIO_INPUT;
	pin_direction(&MOSI_PIN);
	pin_direction(&MISO_PIN);
	pin_direction(&SCK_PIN);
	//set ss to output & high
	SS_PIN.enummode=MDIO_OUTPUT;
	SS_PIN.enumoutputlevel=MDIO_HIGH;
	pin_direction(&SS_PIN);
	pin_value(&SS_PIN);
	
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
	return error;

}
/*..................*/
//slave init
tenumFncErrorState spi_slave_init(void)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	/* Set MISO output, all others input */
	MOSI_PIN.enummode=MDIO_INPUT;
	SCK_PIN.enummode=MDIO_INPUT;
	MISO_PIN.enummode=MDIO_OUTPUT;
	SS_PIN.enummode=MDIO_INPUT;
	pin_direction(&MOSI_PIN);
	pin_direction(&MISO_PIN);
	pin_direction(&SCK_PIN);
	pin_direction(&SS_PIN);
	
	//enable spi
	SET_BIT(SPCR,SPE);
	
	//This bit selects slave SPI mode when written to zero
	CLR_BIT(SPCR,MSTR);
	
	//When the DORD bit is written to zero, the MSB of the data word is transmitted first
	CLR_BIT(SPCR,DORD);
	
	//When this bit is written to one, SCK is high when idle.
	SET_BIT(SPCR,CPOL); //leading edge is falling edge
	SET_BIT(SPCR,CPHA); //reads on leading edge
	return error;
}
/*..................*/

tenumFncErrorState spi_master_transmit_byte(u8 data)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	//ss  low
	SS_PIN.enumoutputlevel=MDIO_LOW;
	pin_value(&SS_PIN);
	
	/* Start transmission */
	SPDR=data;
	
	/* Wait for transmission complete */
	while (!(GET_BIT(SPSR,SPIF)));
	
	//ss  high again
	SS_PIN.enumoutputlevel=MDIO_HIGH;
	pin_value(&SS_PIN);
	return error;
}


tenumFncErrorState spi_master_receive_byte(pu8 pu8variable)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==pu8variable)
	{
		error=LSTY_NULL_POINTER;
	}
	else
	{
			u8 x=0;
			//ss  low
			SS_PIN.enumoutputlevel=MDIO_LOW;
			pin_value(&SS_PIN);
			
			SPDR=x;				//dummy data
			
			/* Wait for transmission complete */
			while (!(GET_BIT(SPSR,SPIF)));
			*pu8variable=SPDR;
			
			//ss  high again
			SS_PIN.enumoutputlevel=MDIO_HIGH;
			pin_value(&SS_PIN);
	}
	return error;

}



tenumFncErrorState spi_slave_transmit_byte(u8 data)
{
	SPDR=data;
}



tenumFncErrorState spi_slave_receive_byte(pu8 pu8variable)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==pu8variable)
	{
	}
	else
	{
		while (!(GET_BIT(SPSR,SPIF)));
		*pu8variable=SPDR;	
	}
	return error;
	
}