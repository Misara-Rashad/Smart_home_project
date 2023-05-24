/*
 * MTWI_INTERFACE.h
 *
 * Created: 27/03/2023 5:59:41 AM
 *  Author: Misra
 */ 


#ifndef MTWI_INTERFACE_H_
#define MTWI_INTERFACE_H_

#include "MTWI_REGISTERS.h"
#include "MTWI_CONFIG.h"



//functions prototype
//TWI functions
tenumFncErrorState TWI_INIT(void);
tenumFncErrorState TWI_START_CONDITION(void);
tenumFncErrorState TWI_REPEATED_START_CONDITION(void);
tenumFncErrorState TWI_STOP_CONDITION(void);
tenumFncErrorState TWI_SEND_SLAVE_ADDRESS_AND_RW_BIT(u8 u8dslave_address_7bit,u8 u8W0_R1);
tenumFncErrorState TWI_SEND_BYTE_AFTER_SENDING_ADDRESS(u8 u8data);
tenumFncErrorState TWI_RECEIVE_BYTE_AFTER_SENDING_ADDRESS(pu8 pu8received_data);
tenumFncErrorState TWI_CHECK_STATUS_REGISTER(pu8 pu8status_register);

//master functions
tenumFncErrorState TWI_MASTER_TRANSMIT_BYTE(u8 u8dslave_address,u8 u8data_transmitted);
tenumFncErrorState TWI_MASTER_RECEIVE_BYTE(u8 u8dslave_address,pu8 pu8received_data);

//slave
tenumFncErrorState TWI_SLAVE_TRANSMIT_BYTE(u8 u8dslave_address,u8 u8data_transmitted); //not defined
tenumFncErrorState TWI_SLAVE_RECEIVE_BYTE(u8 u8dslave_address,pu8 pu8received_data);


#endif /* MTWI_INTERFACE_H_ */