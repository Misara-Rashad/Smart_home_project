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
void voidEEPROM_WRITE_BYTE(u8 data,u16 address_in_eeprom);    //address from 0 to 1023 each can carry 1 byte
u8	u8EEPROM_READ_BYTE_MEEPROM(u16 address_in_eeprom);


#endif /* MEEPROM_INTERFACE_H_ */