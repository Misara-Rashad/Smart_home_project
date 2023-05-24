/*
 * HKEYPAD_PROGRAM.c
 *
 * Created: 23/02/2023 4:09:49 PM
 *  Author: Misra
 */ 



/*.........includes section........*/
//libraries
#include "../../Libraries_/LIB_STDTypes.h"

//MCAL
#include "../../MCAL/MDIO/MDIO_INTERFACE.h"

//HAL
#include "HKEYPAD_CONFIG.h"
#include "HKEYPAD_INTERFACE.h"


#define F_CPU 16000000UL
#include <util/delay.h>

u8 keypad[4][4]={	{'7','8','9','/'},
					{'4','5','6','x'},
					{'1','2','3','-'},
					{'C','0','=','+'}	};
	
	
tenumFncErrorState keypad_init(void)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	u8 i;
	for(i=0;i<NUM_OF_KEYPADS;i++)
	{
		pin_direction(&HKEYPAD_arrayofkeypads[i].rows[0]);
		pin_direction(&HKEYPAD_arrayofkeypads[i].rows[1]);
		pin_direction(&HKEYPAD_arrayofkeypads[i].rows[2]);
		pin_direction(&HKEYPAD_arrayofkeypads[i].rows[3]);
		
		pin_value(&HKEYPAD_arrayofkeypads[i].rows[0]);
		pin_value(&HKEYPAD_arrayofkeypads[i].rows[1]);
		pin_value(&HKEYPAD_arrayofkeypads[i].rows[2]);
		pin_value(&HKEYPAD_arrayofkeypads[i].rows[3]);

		pin_direction(&HKEYPAD_arrayofkeypads[i].colums[0]);
		pin_direction(&HKEYPAD_arrayofkeypads[i].colums[1]);
		pin_direction(&HKEYPAD_arrayofkeypads[i].colums[2]);
		pin_direction(&HKEYPAD_arrayofkeypads[i].colums[3]);

		pin_value(&HKEYPAD_arrayofkeypads[i].colums[0]);
		pin_value(&HKEYPAD_arrayofkeypads[i].colums[1]);
		pin_value(&HKEYPAD_arrayofkeypads[i].colums[2]);
		pin_value(&HKEYPAD_arrayofkeypads[i].colums[3]);

	}
	return error;
}



tenumFncErrorState keypadgetnumber(KEYPAD_T* pstructcpy,pu8 pu8cpy_value)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==pstructcpy || NULL==pu8cpy_value)
	{
		error=LSTY_NULL_POINTER;
	}
	else
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
						pin_value(&pstructcpy->colums[colum]);
						for (row=0;row<NUM_OF_ROWS_KEYPAD;row++)
						{
							pin_get_value(&HKEYPAD_arrayofkeypads->rows[row],&x);
							if (x == MDIO_LOW)
							{
								*pu8cpy_value =keypad[row][colum];
								while(!(x)) //while pressed
								{
									pin_get_value(&pstructcpy->rows[row], &x);
								}
								_delay_ms(15); //debouncing
							}
						}
						pstructcpy->colums[colum].enumoutputlevel=MDIO_HIGH;
						pin_value(&pstructcpy->colums[colum]);
					}
					
					return LSTY_EXECUTED_SUCCESSFULLY;
				}

	}
	return error;

}
