#ifndef LIB_BMNP_H_INCLUDED
#define LIB_BMNP_H_INCLUDED  
      
	  
//bit manipulation 
#define GET_BIT(VAR,Bitno)            (((VAR) >> (Bitno)) & 0x01)

#define Toggle_BIT( VAR, Bitno)       (VAR) ^= (1 << (Bitno))

#define CLR_BIT(VAR,Bitno)            (VAR) &=~(1 << (Bitno))

#define SET_BIT(VAR,Bitno)            (VAR) |= (1 << (Bitno))

#define Conc(b0,b1,b2,b3,b4,b5,b6,b7) 0b##b7##b6##b5##b4##b3##b2##b1##b0

//that macro function only works with integers
#define SWAP_INT(a,b)	do{\
							a ^= b;\
							b ^= a;\
							a ^= b;\
						  }while(0)

typedef union
{
    struct
    {
        u8 B0:1;
        u8 B1:1;
        u8 B2:1;
        u8 B3:1;
        u8 B4:1;
        u8 B5:1;
        u8 B6:1;
        u8 B7:1;
    }Bit;
    u8 Byte;
}Register;

#include "ATMega32_Registers.h"
#endif // LIB_BMNP_H_INCLUDED
