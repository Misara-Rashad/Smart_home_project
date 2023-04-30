/*
 * MDIO_INTERFACE.h
 *
 * Created: 19/02/2023 12:42:17 AM
 *  Author: Misra
 */ 


#ifndef MDIO_INTERFACE_H_
#define MDIO_INTERFACE_H_

//includes
#include "../../Libraries_/LIB_STDTypes.h"

#include "MDIO_REGISTERS.h"
#include "MDIO_CONFIG.h"

//4 ports in ATMEGA32
typedef enum
{
	MDIO_PORTA,MDIO_PORTB,MDIO_PORTC,MDIO_PORTD
}PORTS;

//8 pin for each port
typedef enum{
	MDIO_PIN0,MDIO_PIN1,MDIO_PIN2,MDIO_PIN3,MDIO_PIN4,MDIO_PIN5,MDIO_PIN6,MDIO_PIN7
	}PINS;

//modes for pins --->input or output
typedef enum{
	MDIO_INPUT,MDIO_OUTPUT
	}MODE_OF_OPERATION;



//output level ----->high or low 
typedef enum{
	MDIO_LOW,MDIO_HIGH
	}OUTPUT_LEVEL;

typedef struct
{
PINS enumpin;
PORTS enumport;
MODE_OF_OPERATION enummode;
OUTPUT_LEVEL enumoutputlevel;	
}DIO_PIN;

typedef struct
{
	PORTS enumport;
	MODE_OF_OPERATION enummode;
	OUTPUT_LEVEL enumoutputlevel;
}DIO_PORT;


//functions prototype
//2.direction of port or pin
tenumFncErrorState enumpindirection_MDIO(DIO_PIN* pstructcpy_pin);
tenumFncErrorState enumportdirection_MDIO(DIO_PORT* pstructcpy_port);

//3.pin
tenumFncErrorState enumpinvalue_MDIO(DIO_PIN* pstructcpy_pin);
tenumFncErrorState enumpinvalue_selection_MDIO(DIO_PIN* pstructcpy_pin,OUTPUT_LEVEL enumoutputlevel);
tenumFncErrorState enumpintoggle_MDIO(DIO_PIN* pstructcpy_pin);
tenumFncErrorState enumpingetvalue_MDIO(DIO_PIN* pstructcpy_pin,pu8 pu8cpy_pin);


//4.port
tenumFncErrorState enumportvalue_MDIO(DIO_PORT* pstructcpy_port,u8 u8cpy_value );




#endif /* MDIO_INTERFACE_H_ */