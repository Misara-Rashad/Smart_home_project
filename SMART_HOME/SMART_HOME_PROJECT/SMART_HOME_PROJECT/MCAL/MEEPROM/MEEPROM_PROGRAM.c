/*
 * MEEPROM_PROGRAM.c
 *
 * Created: 13/04/2023 11:47:31 PM
 *  Author: Misra
 */ 


//includes
#include "../../Libraries_/LIB_STDTypes.h"

#include "MEEPROM_INTERFACE.h"

//functions implementation
tenumFncErrorState EEPROM_WRITE_BYTE(u8 data,u16 address_in_eeprom)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (address_in_eeprom>1024)
	{
		error=LSTY_OUT_OF_RANGE;
	}
	else
	{
	while((GET_BIT(EECR,EEWE)));

	EEAR=address_in_eeprom;
	EEDR=data;

	SET_BIT(EECR,EEMWE);

	SET_BIT(EECR,EEWE);	
	}
	return error;
	

}


tenumFncErrorState EEPROM_READ_BYTE_MEEPROM(u16 address_in_eeprom,pu8 pu8_byte_read)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==pu8_byte_read)
	{
		error=LSTY_NULL_POINTER;
	}
	else if(address_in_eeprom>1024) 
	{
		error=LSTY_OUT_OF_RANGE;
	}
	else
	{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE));
	/* Set up address register */
	EEAR = address_in_eeprom;
	/* Start eeprom read by writing EERE */
	SET_BIT(EECR,EERE);
	/* Return data from data register */
	*pu8_byte_read=EEDR	;
	}
	return error;
	
}