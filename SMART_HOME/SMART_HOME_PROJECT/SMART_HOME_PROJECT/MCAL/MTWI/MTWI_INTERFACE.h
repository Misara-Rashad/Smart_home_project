/*
 * MTWI_INTERFACE.h
 *
 * Created: 27/03/2023 5:59:41 AM
 *  Author: Misra
 */ 


#ifndef MTWI_INTERFACE_H_
#define MTWI_INTERFACE_H_




//functions prototype
//TWI functions
void voidinitTWI_MTWI(void);
void voidTWI_START_CONDITION_MTWI(void);
void voidTWI_REPEATED_START_CONDITION(void);
void voidTWI_STOP_CONDITION_MTWI(void);
void voidTWI_SEND_SLAVE_ADDRESS_AND_RW_BIT_MTWI(u8 u8dslave_address_7bit,u8 u8W0_R1);
void voidTWI_SEND_BYTE_AFTER_SENDING_ADDRESS_MTWI(u8 u8data);
void voidTWI_RECEIVE_BYTE_AFTER_SENDING_ADDRESS_MTWI(pu8 pu8received_data);
void voidTWI_CHECK_STATUS_REGISTER_MTWI(pu8 pu8status_register);



//master functions
void voidTWI_MASTER_TRANSMIT_BYTE(u8 u8dslave_address,u8 u8data_transmitted);
void voidTWI_MASTER_RECEIVE_BYTE(u8 u8dslave_address,pu8 pu8received_data);




//slave
void voidTWI_SLAVE_TRANSMIT_BYTE(u8 u8dslave_address,u8 u8data_transmitted);
void voidTWI_SLAVE_RECEIVE_BYTE(u8 u8dslave_address,pu8 pu8received_data);


#endif /* MTWI_INTERFACE_H_ */