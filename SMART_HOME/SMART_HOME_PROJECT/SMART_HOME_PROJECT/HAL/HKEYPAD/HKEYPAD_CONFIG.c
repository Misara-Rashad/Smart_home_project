/*
 * HKEYPAD_CONFIG.c
 *
 * Created: 23/02/2023 4:09:27 PM
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


KEYPAD_T HKEYPAD_arrayofkeypads[NUM_OF_KEYPADS]={
	
	[HKEYPAD_NUM0]={
						.rows[0]={MDIO_PIN0,MDIO_PORTC,MDIO_INPUT,MDIO_HIGH}, //internal pull up resistor on
						.rows[1]={MDIO_PIN1,MDIO_PORTC,MDIO_INPUT,MDIO_HIGH}, //internal pull up resistor on
						.rows[2]={MDIO_PIN2,MDIO_PORTC,MDIO_INPUT,MDIO_HIGH}, //internal pull up resistor on
						.rows[3]={MDIO_PIN3,MDIO_PORTC,MDIO_INPUT,MDIO_HIGH}, //internal pull up resistor on

						.colums[0]={MDIO_PIN4,MDIO_PORTC,MDIO_HIGH,MDIO_HIGH},
						.colums[1]={MDIO_PIN5,MDIO_PORTC,MDIO_HIGH,MDIO_HIGH},
						.colums[2]={MDIO_PIN6,MDIO_PORTC,MDIO_HIGH,MDIO_HIGH},
						.colums[3]={MDIO_PIN7,MDIO_PORTC,MDIO_HIGH,MDIO_HIGH},
		
		
	}
	};