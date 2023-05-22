/*
 * MEEPROM_PROGRAM.c
 *
 * Created: 13/04/2023 11:47:31 PM
 *  Author: Misra
 */ 


//includes
#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"
#include "../../Libraries_/ATMega32_Registers.h"


#include "MEEPROM_REGISTERS.h"
#include "MEEPROM_INTERFACE.h"

//functions implementation
void voidEEPROM_WRITE_BYTE(u8 data,u16 address_in_eeprom)
{
	while((GET_BIT(EECR,EEWE)));

	EEAR=address_in_eeprom;
	EEDR=data;

	SET_BIT(EECR,EEMWE);

	SET_BIT(EECR,EEWE);

}


u8	u8EEPROM_READ_BYTE_MEEPROM(u16 address_in_eeprom)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
	;
	/* Set up address register */
	EEAR = address_in_eeprom;
	/* Start eeprom read by writing EERE */
	SET_BIT(EECR,EERE);
	/* Return data from data register */
	return EEDR;
}