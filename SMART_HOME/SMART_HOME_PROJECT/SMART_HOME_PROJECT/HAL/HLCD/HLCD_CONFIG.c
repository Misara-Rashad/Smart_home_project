/*
 * HLCD_CONFIG.c
 *
 * Created: 21/02/2023 11:12:43 PM
 *  Author: Misra
 */ 

/*...........includes section.........*/
//libraries
#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"
#include "../../Libraries_/ATMega32_Registers.h"


//MCAL
#include "../../MCAL/MDIO/MDIO_CONFIG.h"
#include "../../MCAL/MDIO/MDIO_INTERFACE.h"
#include "../../MCAL/MDIO/MDIO_REGISTERS.h"

//HAL
#include "HLCD_CONFIG.h"
#include "HLCD_INTERFACE.h"





LCD_T HLCD_arrayoflcds[NUM_OF_LCDS]={
	
	[HLCD_NUM0]={
				.D0={MDIO_PIN0,MDIO_PORTA,MDIO_OUTPUT,MDIO_HIGH},
				.D1={MDIO_PIN1,MDIO_PORTA,MDIO_OUTPUT,MDIO_HIGH},
				.D2={MDIO_PIN2,MDIO_PORTA,MDIO_OUTPUT,MDIO_HIGH},
				.D3={MDIO_PIN3,MDIO_PORTA,MDIO_OUTPUT,MDIO_HIGH},
					
				.D4={MDIO_PIN4,MDIO_PORTA,MDIO_OUTPUT,MDIO_HIGH},
				.D5={MDIO_PIN5,MDIO_PORTA,MDIO_OUTPUT,MDIO_HIGH},
				.D6={MDIO_PIN6,MDIO_PORTA,MDIO_OUTPUT,MDIO_HIGH},
				.D7={MDIO_PIN7,MDIO_PORTA,MDIO_OUTPUT,MDIO_HIGH},
					
				.RS={MDIO_PIN1,MDIO_PORTB,MDIO_OUTPUT,MDIO_HIGH},
				.RW={MDIO_PIN2,MDIO_PORTB,MDIO_OUTPUT,MDIO_HIGH},
				.ENABLE={MDIO_PIN3,MDIO_PORTB,MDIO_OUTPUT,MDIO_HIGH},
				.enummode=four_BIT_MODE
					
	}
	};
