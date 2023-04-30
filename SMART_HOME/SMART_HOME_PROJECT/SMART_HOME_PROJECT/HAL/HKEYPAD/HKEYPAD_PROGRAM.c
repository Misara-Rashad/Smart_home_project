/*
 * HKEYPAD_PROGRAM.c
 *
 * Created: 23/02/2023 4:09:49 PM
 *  Author: Misra
 */ 



/*.........includes section........*/
//libraries
#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"
#include "../../Libraries_/ATMega32_Registers.h"



//MCAL
#include "../../MCAL/MDIO/MDIO_CONFIG.h"
#include "../../MCAL/MDIO/MDIO_INTERFACE.h"
#include "../../MCAL/MDIO/MDIO_REGISTERS.h"



//HAL
#include "HKEYPAD_CONFIG.h"
#include "HKEYPAD_INTERFACE.h"


#define F_CPU 16000000UL
#include <util/delay.h>

u8 keypad[4][4]={	{'7','8','9','/'},
					{'4','5','6','x'},
					{'1','2','3','-'},
					{'C','0','=','+'}	};
	
	
void voidinitkeypad_HKEYPAD(void)
{
	u8 i;
	for(i=0;i<NUM_OF_KEYPADS;i++)
	{
		enumpindirection_MDIO(&HKEYPAD_arrayofkeypads[i].rows[0]);
		enumpindirection_MDIO(&HKEYPAD_arrayofkeypads[i].rows[1]);
		enumpindirection_MDIO(&HKEYPAD_arrayofkeypads[i].rows[2]);
		enumpindirection_MDIO(&HKEYPAD_arrayofkeypads[i].rows[3]);
		
		enumpinvalue_MDIO(&HKEYPAD_arrayofkeypads[i].rows[0]);
		enumpinvalue_MDIO(&HKEYPAD_arrayofkeypads[i].rows[1]);
		enumpinvalue_MDIO(&HKEYPAD_arrayofkeypads[i].rows[2]);
		enumpinvalue_MDIO(&HKEYPAD_arrayofkeypads[i].rows[3]);

		enumpindirection_MDIO(&HKEYPAD_arrayofkeypads[i].colums[0]);
		enumpindirection_MDIO(&HKEYPAD_arrayofkeypads[i].colums[1]);
		enumpindirection_MDIO(&HKEYPAD_arrayofkeypads[i].colums[2]);
		enumpindirection_MDIO(&HKEYPAD_arrayofkeypads[i].colums[3]);

		enumpinvalue_MDIO(&HKEYPAD_arrayofkeypads[i].colums[0]);
		enumpinvalue_MDIO(&HKEYPAD_arrayofkeypads[i].colums[1]);
		enumpinvalue_MDIO(&HKEYPAD_arrayofkeypads[i].colums[2]);
		enumpinvalue_MDIO(&HKEYPAD_arrayofkeypads[i].colums[3]);

	}

}



tenumFncErrorState enumkeypadgetnumber_HKEYPAD(KEYPAD_T* pstructcpy,pu8 pu8cpy_value)
{
	
		u8 row,colum,x=1;

	if(pu8cpy_value == NULL)
	{
		return LSTY_NULL_POINTER;
	}
	
	else
	{
		for(colum=0;colum<NUM_OF_COLUMS_KEYPAD;colum++)
		{
		
		pstructcpy->colums[colum].enumoutputlevel=MDIO_LOW;	
		enumpinvalue_MDIO(&pstructcpy->colums[colum]);	
			for (row=0;row<NUM_OF_ROWS_KEYPAD;row++)
			{
				enumpingetvalue_MDIO(&HKEYPAD_arrayofkeypads->rows[row],&x);
				   if (x == MDIO_LOW)
					   {
						    *pu8cpy_value =keypad[row][colum];
				       while(!(x)) //while pressed
						   {
					       enumpingetvalue_MDIO(&pstructcpy->rows[row], &x);
						   }
				       _delay_ms(15); //debouncing
					   }
			}
		pstructcpy->colums[colum].enumoutputlevel=MDIO_HIGH;
		enumpinvalue_MDIO(&pstructcpy->colums[colum]);
		}	
		
		return LSTY_EXECUTED_SUCCESSFULLY;
	}

}
