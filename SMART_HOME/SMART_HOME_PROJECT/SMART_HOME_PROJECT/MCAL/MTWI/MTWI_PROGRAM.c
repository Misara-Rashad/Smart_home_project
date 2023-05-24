/*
 * MTWI_PROGRAM.c
 *
 * Created: 27/03/2023 5:59:21 AM
 *  Author: Misra
 */ 


#include "../../Libraries_/LIB_STDTypes.h"



#include "MTWI_INTERFACE.h"



//functions implementation
tenumFncErrorState TWI_INIT(void)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	//select baud rate
	CLR_BIT(TWSR,TWPS0);
	CLR_BIT(TWSR,TWPS1);
	TWBR=18;
	return error;
}


tenumFncErrorState TWI_START_CONDITION(void)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;	
	//start condition
	TWCR=(SET_BIT(TWCR,TWINT))|(SET_BIT(TWCR,TWSTA)) |(CLR_BIT(TWCR,TWSTO)) |(SET_BIT(TWCR,TWEN));
	while (!GET_BIT(TWCR,TWINT));
	return error;
}


tenumFncErrorState TWI_REPEATED_START_CONDITION(void)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	//repeated start
	TWCR=(SET_BIT(TWCR,TWINT))|(SET_BIT(TWCR,TWSTA)) |(CLR_BIT(TWCR,TWSTO)) |(SET_BIT(TWCR,TWEN));
	while (!GET_BIT(TWCR,TWINT));
	return error;
}


tenumFncErrorState TWI_STOP_CONDITION(void)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	//stop condition
	TWCR=(SET_BIT(TWCR,TWINT))|(CLR_BIT(TWCR,TWSTA)) |(SET_BIT(TWCR,TWSTO)) |(SET_BIT(TWCR,TWEN));
	return error;	
}


tenumFncErrorState TWI_SEND_SLAVE_ADDRESS_AND_RW_BIT(u8 u8dslave_address_7bit,u8 u8W0_R1)
{
		tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
		//SLA+W/R
		//after writing address of the slave clear TWINT
		u8 address_only,address_includesRW_bit;
		address_only=u8dslave_address_7bit<<1;
		address_includesRW_bit=address_only|u8W0_R1;
		TWDR=address_includesRW_bit; //slave address + w  (SLA+W)
		TWCR=(SET_BIT(TWCR,TWINT))|(CLR_BIT(TWCR,TWSTA)) |(CLR_BIT(TWCR,TWSTO)) |(SET_BIT(TWCR,TWEN));
		while (!GET_BIT(TWCR,TWINT));
		return error;			
}


tenumFncErrorState TWI_SEND_BYTE_AFTER_SENDING_ADDRESS(u8 u8data)
{
		tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
		TWDR=u8data;
		TWCR=(SET_BIT(TWCR,TWINT))|(CLR_BIT(TWCR,TWSTA)) |(CLR_BIT(TWCR,TWSTO)) |(SET_BIT(TWCR,TWEN));
		while (!GET_BIT(TWCR,TWINT));
		return error;
}



tenumFncErrorState TWI_RECEIVE_BYTE_AFTER_SENDING_ADDRESS(pu8 pu8received_data)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==pu8received_data)
	{
		error=LSTY_NULL_POINTER;
	}
	else
	{
		*pu8received_data = TWDR;	
	}
	return error;

}


tenumFncErrorState TWI_CHECK_STATUS_REGISTER(pu8 pu8status_register)
{
		tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
		if (NULL==pu8status_register)
		{
			error=LSTY_NULL_POINTER;
		}
		else
		{
			while ( !GET_BIT(TWCR,TWINT));
			*pu8status_register=TWSR & 0xF8;
		}
		return error;

}



//master functions

tenumFncErrorState TWI_MASTER_TRANSMIT_BYTE(u8 u8dslave_address,u8 u8data_transmitted)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	TWI_START_CONDITION();
	TWI_SEND_SLAVE_ADDRESS_AND_RW_BIT(u8dslave_address,0); //0 as master writes data to slave
	TWI_SEND_BYTE_AFTER_SENDING_ADDRESS(u8data_transmitted);
	TWI_STOP_CONDITION();
	return error;
}


tenumFncErrorState TWI_MASTER_RECEIVE_BYTE(u8 u8dslave_address,pu8 pu8received_data)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==pu8received_data)
	{
		error=LSTY_NULL_POINTER;
	}
	else
	{
		TWI_START_CONDITION();
		TWI_SEND_SLAVE_ADDRESS_AND_RW_BIT(u8dslave_address,1); //1 as master reads data to slave
		TWI_RECEIVE_BYTE_AFTER_SENDING_ADDRESS(pu8received_data);
		TWI_STOP_CONDITION();
	}
	return error;
	
}



//slave functions
tenumFncErrorState TWI_SLAVE_RECEIVE_BYTE(u8 u8dslave_address,pu8 pu8received_data)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==pu8received_data)
	{
		error=LSTY_NULL_POINTER;
	}
	else
	{
		TWAR = u8dslave_address << 1 ;		//to be in most significant 7 bit of TwAR
		TWCR=(SET_BIT(TWCR,TWEA))|(CLR_BIT(TWCR,TWSTA)) |(CLR_BIT(TWCR,TWSTO)) |(SET_BIT(TWCR,TWEN));
		*pu8received_data=TWDR;
	}
	return error;

}


