/*
 * MTWI_PROGRAM.c
 *
 * Created: 27/03/2023 5:59:21 AM
 *  Author: Misra
 */ 


#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"
#include "../../Libraries_/ATMega32_Registers.h"


#include "MTWI_CONFIG.h"
#include "MTWI_INTERFACE.h"
#include "MTWI_REGISTERS.h"



//functions implementation
void voidinitTWI_MTWI(void)
{
	//select baud rate
	CLR_BIT(TWSR,TWPS0);
	CLR_BIT(TWSR,TWPS1);
	TWBR=18;
}


void voidTWI_START_CONDITION_MTWI(void)
{
	//start condition
	TWCR=(SET_BIT(TWCR,TWINT))|(SET_BIT(TWCR,TWSTA)) |(CLR_BIT(TWCR,TWSTO)) |(SET_BIT(TWCR,TWEN));
	while (!GET_BIT(TWCR,TWINT));
}


void voidTWI_REPEATED_START_CONDITION(void)
{
	//repeated start
	TWCR=(SET_BIT(TWCR,TWINT))|(SET_BIT(TWCR,TWSTA)) |(CLR_BIT(TWCR,TWSTO)) |(SET_BIT(TWCR,TWEN));
	while (!GET_BIT(TWCR,TWINT));
}


void voidTWI_STOP_CONDITION_MTWI(void)
{
	//stop condition
	TWCR=(SET_BIT(TWCR,TWINT))|(CLR_BIT(TWCR,TWSTA)) |(SET_BIT(TWCR,TWSTO)) |(SET_BIT(TWCR,TWEN));
}


void voidTWI_SEND_SLAVE_ADDRESS_AND_RW_BIT_MTWI(u8 u8dslave_address_7bit,u8 u8W0_R1)
{
		//SLA+W/R
		//after writing address of the slave clear TWINT
		u8 address_only,address_includesRW_bit;
		address_only=u8dslave_address_7bit<<1;
		address_includesRW_bit=address_only|u8W0_R1;
		TWDR=address_includesRW_bit; //slave address + w  (SLA+W)
		TWCR=(SET_BIT(TWCR,TWINT))|(CLR_BIT(TWCR,TWSTA)) |(CLR_BIT(TWCR,TWSTO)) |(SET_BIT(TWCR,TWEN));
		while (!GET_BIT(TWCR,TWINT));
}


void voidTWI_SEND_BYTE_AFTER_SENDING_ADDRESS_MTWI(u8 u8data)
{
		TWDR=u8data;
		TWCR=(SET_BIT(TWCR,TWINT))|(CLR_BIT(TWCR,TWSTA)) |(CLR_BIT(TWCR,TWSTO)) |(SET_BIT(TWCR,TWEN));
		while (!GET_BIT(TWCR,TWINT));
}



void voidTWI_RECEIVE_BYTE_AFTER_SENDING_ADDRESS_MTWI(pu8 pu8received_data)
{
	*pu8received_data = TWDR;
}


void voidTWI_CHECK_STATUS_REGISTER_MTWI(pu8 pu8status_register)
{
	while ( !GET_BIT(TWCR,TWINT));
	*pu8status_register=TWSR & 0xF8;
}



//master functions

void voidTWI_MASTER_TRANSMIT_BYTE(u8 u8dslave_address,u8 u8data_transmitted)
{
	voidTWI_START_CONDITION_MTWI();
	voidTWI_SEND_SLAVE_ADDRESS_AND_RW_BIT_MTWI(u8dslave_address,0); //0 as master writes data to slave
	voidTWI_SEND_BYTE_AFTER_SENDING_ADDRESS_MTWI(u8data_transmitted);
	voidTWI_STOP_CONDITION_MTWI();
}


void voidTWI_MASTER_RECEIVE_BYTE(u8 u8dslave_address,pu8 pu8received_data)
{
	voidTWI_START_CONDITION_MTWI();
	voidTWI_SEND_SLAVE_ADDRESS_AND_RW_BIT_MTWI(u8dslave_address,1); //1 as master reads data to slave
	voidTWI_RECEIVE_BYTE_AFTER_SENDING_ADDRESS_MTWI(pu8received_data);
	voidTWI_STOP_CONDITION_MTWI();	
}



//slave functions
void voidTWI_SLAVE_RECEIVE_BYTE(u8 u8dslave_address,pu8 pu8received_data)
{
	TWAR = u8dslave_address << 1 ;		//to be in most significant 7 bit of TwAR
	TWCR=(SET_BIT(TWCR,TWEA))|(CLR_BIT(TWCR,TWSTA)) |(CLR_BIT(TWCR,TWSTO)) |(SET_BIT(TWCR,TWEN));
	*pu8received_data=TWDR;
}


