/*
 * MEEPROM_REGISTERS.h
 *
 * Created: 13/04/2023 11:48:04 PM
 *  Author: Misra
 */ 


#ifndef MEEPROM_REGISTERS_H_
#define MEEPROM_REGISTERS_H_

/* EEPROM Control Register */
#define   EECR         (*((volatile u8*)0x3C))

/* EEPROM Data Register */
#define   EEDR         (*((volatile u8*)0x3D))

/* EEPROM Address Register */
#define   EEAR         (*((volatile u16*)0x3E))
#define   EEARL        (*((volatile u8*)0x3E))
#define   EEARH        (*((volatile u8*)0x3F))

#define   UBRRH        (*((volatile u8*)0x40))
#define   UCSRC        UBRRH

#define   WDTCR        (*((volatile u8*)0x41))

#define   ASSR         (*((volatile u8*)0x42))



#endif /* MEEPROM_REGISTERS_H_ */