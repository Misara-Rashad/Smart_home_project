/*
 * MEEPROM_INTERFACE.h
 *
 * Created: 13/04/2023 11:47:48 PM
 *  Author: Misra
 */ 


#ifndef MEEPROM_INTERFACE_H_
#define MEEPROM_INTERFACE_H_

#include "MEEPROM_REGISTERS.h"

//functions interface
tenumFncErrorState EEPROM_WRITE_BYTE(u8 data,u16 address_in_eeprom);    //address from 0 to 1023 each can carry 1 byte
tenumFncErrorState EEPROM_READ_BYTE_MEEPROM(u16 address_in_eeprom,pu8 pu8_byte_read);


#endif /* MEEPROM_INTERFACE_H_ */