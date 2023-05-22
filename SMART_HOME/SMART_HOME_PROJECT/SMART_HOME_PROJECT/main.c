/*
 * main.c
 *
 * Created: 16/04/2023 12:45:02 PM
 *  Author: Misra
 */ 

#define F_CPU	16000000UL
#include <util/delay.h>
#define no_of_trials		3
#include <avr/interrupt.h>

//MCAL
#include "MCAL/MDIO/MDIO_INTERFACE.h"
#include "MCAL/MINT/MINT_INTERFACE.h"
#include "MCAL/MTIMER/MTIMER_INTERFACE.h"
#include "MCAL/MEEPROM/MEEPROM_INTERFACE.h"
#include "MCAL/MSPI/MSPI_INTERFACE.h"

//HAL
#include "HAL/HLED/HLED_INTERFACE.h"
#include "HAL/HKEYPAD/HKEYPAD_INTERFACE.h"
#include "HAL/HLCD/HLCD_INTERFACE.h"
#include "HAL/HSERVO/HSERVO_INTERFACE.h"

f32 x=0;


/*//MASTER CODE
//functions declaration 
u8 u8check_if_admin_set_pass();	//return 0
u8 u8set_admin_pass(void);		//return 1
u8 u8enter_admin_pass(void);	//return 2
u8 u8check_admin_pass(void);	//return 3
u8 u8admin_control(void);		//return 4



//data types 
typedef struct
{
	u8 state_of_led0:1 ;
	u8 state_of_led1:1 ;
	u8 state_of_led2:1 ;
	u8 state_of_led3:1 ;
	u8 state_of_led4:1 ;
	u8 state_of_led5:1 ;
	u8 state_of_led6:1 ;
	u8 state_of_led7:1 ;
}loads;


//global variables
loads loads_status;

u8 value_in_keypad = 1;

u8 counter_in_eeprom=0;
u16 address_in_eeprom=0;

u8 saved_pass=0;
u8 entered_pass=0;

u8 sequence=0;
u8 lcd_flag=0;

u8 counter_for_wrong_pass_entered=0;
u8 wrong_pass_flag=0;

u8 enter_password_message[]="password:";
u8 error_massage[]= "wrong password";
u8 right_pass[]="welcome";
u8 choose[]="Room 1 to 9:";
u8 set_admin_pass[]="set_admin_pass:";
u8 on[]="ON";
u8 off[]="OFF";


int main(void)
{
	voidtimer1_ctc_interrupt_call_back(voidservo_start_HSERVO);
	voidinitkeypad_HKEYPAD();
	voidinitlcd_HLCD();
	//voidinitspi_master_MSPI();
	
	sequence=u8check_if_admin_set_pass();
	while (1)
	{
			switch(sequence)
			{
				case 0:
				sequence=u8set_admin_pass();
				break;
				
				case 1:
				sequence=u8enter_admin_pass();
				break;
				
				case 2:
				sequence=u8check_admin_pass();
				break;
				
				case 3:
				sequence=u8admin_control();
				break;
				
				default:
				break;													
			}
	}
	return 0;
}



u8 u8check_if_admin_set_pass()
{
	u8 data=0,local_variable=0;
	data=u8EEPROM_READ_BYTE_MEEPROM(3);
	if (0xff==data)
	{
		local_variable=0;	//admin has not set a pass
	}
	else
	{
		local_variable=1;	//admin had set pass before
		counter_in_eeprom=4;
		address_in_eeprom=4;
	}
	return local_variable;
}


u8 u8set_admin_pass(void)
{
	u8 local_variable=0;
	voidLCDstring_HLCD(set_admin_pass,16,HLCD_NUM0);
	
	while (4!=counter_in_eeprom)
	{
			enumkeypadgetnumber_HKEYPAD(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
			if (1!=value_in_keypad)
			{
				voidLCDwrite_data_HLCD(DATA,value_in_keypad,HLCD_NUM0);
				voidEEPROM_WRITE_BYTE(value_in_keypad,address_in_eeprom);
				address_in_eeprom++;
				counter_in_eeprom++;
				value_in_keypad=1;
			}
	}
	
	voidlcdclear();
	local_variable=1;
	return local_variable;
}


u8 u8enter_admin_pass(void)
{
	u8 local_variable=1;
	voidLCDstring_HLCD(enter_password_message,9,HLCD_NUM0);
	while (8!=counter_in_eeprom)
	{
			enumkeypadgetnumber_HKEYPAD(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
			if (1!=value_in_keypad)
			{
				voidLCDwrite_data_HLCD(DATA,value_in_keypad,HLCD_NUM0);
				voidEEPROM_WRITE_BYTE(value_in_keypad,address_in_eeprom);
				address_in_eeprom++;
				counter_in_eeprom++;
				value_in_keypad=1;
			}
	}
	
	voidlcdclear();
	local_variable=2;
	return local_variable;

}


u8 u8check_admin_pass(void)	//return 3
{
	u8 local_variable=2;
	while (no_of_trials>counter_for_wrong_pass_entered)
	{
		for (int i=0;i<4;i++)
		{
			saved_pass=u8EEPROM_READ_BYTE_MEEPROM(i);
			entered_pass=u8EEPROM_READ_BYTE_MEEPROM(i+4);
			if (saved_pass!=entered_pass)
			{
				wrong_pass_flag=1;
				counter_for_wrong_pass_entered++;
				voidLCDstring_HLCD(error_massage,14,HLCD_NUM0);
				voidlcdclear();
				break;
			}
		}
		
		if (1!=wrong_pass_flag)		//right pass
		{
			voidLCDstring_HLCD(right_pass,7,HLCD_NUM0);
			voidlcdclear();
			local_variable=3;
			break;
		}
		else						//wrong pass
		{
			local_variable=1;
			address_in_eeprom=4;
			counter_in_eeprom=4;
			wrong_pass_flag=0;
			break;
		}

	}
	return local_variable;
}


u8 u8admin_control(void)		//return 4
{
	u8 local_variable=3;
	voidLCDstring_HLCD(choose,12,HLCD_NUM0);
	while (3==local_variable)
	{
			enumkeypadgetnumber_HKEYPAD(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
			if (1!=value_in_keypad)
			{
				voidLCDwrite_data_HLCD(DATA,value_in_keypad,HLCD_NUM0);
				voidinitspi_master_MSPI();
				switch(value_in_keypad)
				{
					case '0':
					value_in_keypad=1;
					voidspi_master_transmit_byte_MSPI(0);
					_delay_ms(100);
					loads_status.state_of_led0=u8spi_master_receive_byte_MSPI();
					voidlcdclear();
					loads_status.state_of_led0 ?voidLCDstring_HLCD(on,2,HLCD_NUM0) :
												voidLCDstring_HLCD(off,3,HLCD_NUM0);
					while (value_in_keypad==1)
					{
						enumkeypadgetnumber_HKEYPAD(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
						if (1!=value_in_keypad)
						{
							voidLCDwrite_data_HLCD(DATA,value_in_keypad,HLCD_NUM0);
							voidspi_master_transmit_byte_MSPI(value_in_keypad);
						}
					}
					local_variable=4;
					break	;
					
					case '1':
					value_in_keypad=1;
					voidspi_master_transmit_byte_MSPI(1);
					_delay_ms(100);
					loads_status.state_of_led1=u8spi_master_receive_byte_MSPI();
					voidlcdclear();
					loads_status.state_of_led1 ?voidLCDstring_HLCD(on,2,HLCD_NUM0) :
												voidLCDstring_HLCD(off,3,HLCD_NUM0);
					while (value_in_keypad==1)
					{
						enumkeypadgetnumber_HKEYPAD(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
						if (1!=value_in_keypad)
						{
							voidLCDwrite_data_HLCD(DATA,value_in_keypad,HLCD_NUM0);
							voidspi_master_transmit_byte_MSPI(value_in_keypad);					
						}
					}
					local_variable=4;
					break	;
					
					case '2':
					value_in_keypad=1;
					voidspi_master_transmit_byte_MSPI(2);
					_delay_ms(100);
					loads_status.state_of_led2=u8spi_master_receive_byte_MSPI();
					voidlcdclear();
					loads_status.state_of_led2 ?voidLCDstring_HLCD(on,2,HLCD_NUM0) :
												voidLCDstring_HLCD(off,3,HLCD_NUM0);
					while (value_in_keypad==1)
					{
						enumkeypadgetnumber_HKEYPAD(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
						if (1!=value_in_keypad)
						{
							voidLCDwrite_data_HLCD(DATA,value_in_keypad,HLCD_NUM0);
							voidspi_master_transmit_byte_MSPI(value_in_keypad);
						}
					}
					local_variable=4;
					break	;
					
					case '3':
					value_in_keypad=1;
					voidspi_master_transmit_byte_MSPI(3);
					_delay_ms(100);
					loads_status.state_of_led3=u8spi_master_receive_byte_MSPI();
					voidlcdclear();
					loads_status.state_of_led3 ?voidLCDstring_HLCD(on,2,HLCD_NUM0) :
												voidLCDstring_HLCD(off,3,HLCD_NUM0);
					while (value_in_keypad==1)
					{
						enumkeypadgetnumber_HKEYPAD(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
						if (1!=value_in_keypad)
						{
							voidLCDwrite_data_HLCD(DATA,value_in_keypad,HLCD_NUM0);
							voidspi_master_transmit_byte_MSPI(value_in_keypad);
						}
					}
					local_variable=4;					
					break	;
					
					case '4':
					value_in_keypad=1;
					voidspi_master_transmit_byte_MSPI(4);
					_delay_ms(100);
					loads_status.state_of_led4=u8spi_master_receive_byte_MSPI();
					voidlcdclear();
					loads_status.state_of_led4 ?voidLCDstring_HLCD(on,2,HLCD_NUM0) :
												voidLCDstring_HLCD(off,3,HLCD_NUM0);
					while (value_in_keypad==1)
					{
						enumkeypadgetnumber_HKEYPAD(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
						if (1!=value_in_keypad)
						{
							voidLCDwrite_data_HLCD(DATA,value_in_keypad,HLCD_NUM0);
							voidspi_master_transmit_byte_MSPI(value_in_keypad);
						}
					}				
					local_variable=4;
					break	;
					
					case '5':
					value_in_keypad=1;
					voidspi_master_transmit_byte_MSPI(5);
					_delay_ms(100);
					loads_status.state_of_led5=u8spi_master_receive_byte_MSPI();
					voidlcdclear();
					loads_status.state_of_led5 ?voidLCDstring_HLCD(on,2,HLCD_NUM0) :
												voidLCDstring_HLCD(off,3,HLCD_NUM0);
					while (value_in_keypad==1)
					{
						enumkeypadgetnumber_HKEYPAD(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
						if (1!=value_in_keypad)
						{
							voidLCDwrite_data_HLCD(DATA,value_in_keypad,HLCD_NUM0);
							voidspi_master_transmit_byte_MSPI(value_in_keypad);
						}
					}					
					local_variable=4;
					break	;
					
					case '6':
					value_in_keypad=1;
					voidspi_master_transmit_byte_MSPI(6);
					_delay_ms(100);
					loads_status.state_of_led6=u8spi_master_receive_byte_MSPI();
					voidlcdclear();
					loads_status.state_of_led6 ?voidLCDstring_HLCD(on,2,HLCD_NUM0) :
												voidLCDstring_HLCD(off,3,HLCD_NUM0);
					while (value_in_keypad==1)
					{
						enumkeypadgetnumber_HKEYPAD(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
						if (1!=value_in_keypad)
						{
							voidLCDwrite_data_HLCD(DATA,value_in_keypad,HLCD_NUM0);
							voidspi_master_transmit_byte_MSPI(value_in_keypad);
						}
					}				
					local_variable=4;
					break	;
					
					case '7':
					value_in_keypad=1;
					voidspi_master_transmit_byte_MSPI(7);
					_delay_ms(100);
					loads_status.state_of_led7=u8spi_master_receive_byte_MSPI();
					voidlcdclear();
					loads_status.state_of_led7 ?voidLCDstring_HLCD(on,2,HLCD_NUM0) :
												voidLCDstring_HLCD(off,3,HLCD_NUM0);
					while (value_in_keypad==1)
					{
						enumkeypadgetnumber_HKEYPAD(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
						if (1!=value_in_keypad)
						{
							voidLCDwrite_data_HLCD(DATA,value_in_keypad,HLCD_NUM0);
							voidspi_master_transmit_byte_MSPI(value_in_keypad);
						}
					}					
					local_variable=4;
					break	;
					
					default:
					break	;
					
				}
				value_in_keypad=1;
			}
	}

		
		return local_variable;	
}*/





//SLAVE CODE
u8 data_from_master=0;
u8 data_to_master=0;
int main(void)
{	
	voidinitLED_HLED();

	voidledon_HLED(&HLED_arrayofleds[0]);		//led1
	
	voidledoff_HLED(&HLED_arrayofleds[1]);		//led2

	voidledon_HLED(&HLED_arrayofleds[2]);		//led3

	voidinitlcd_HLCD();	
	
	voidinitspi_slave_MSPI();
	
	while (1)
	{
		
	data_from_master=u8spi_slave_receive_byte_MSPI();
	if(data_from_master !=0)
	{
	voidLCDwrite_data_HLCD(DATA,'0'+data_from_master,HLCD_NUM0);
	switch(data_from_master)
		{
			
		case 0:
		//data_to_master=GET_BIT(PORTC_REGISTER,MDIO_PIN2);
		voidspi_slave_transmit_byte_MSPI(data_to_master);
		data_from_master=0;
		while (0 == data_from_master)
		{
			data_from_master=u8spi_slave_receive_byte_MSPI();
		}
		//(data_from_master-48)>0 ? SET_BIT(PORTC_REGISTER,MDIO_PIN2) : CLR_BIT(PORTC_REGISTER,MDIO_PIN2) ;
		break;
					
		case 1:
		data_to_master=GET_BIT(PORTC_REGISTER,MDIO_PIN2);
		voidspi_slave_transmit_byte_MSPI(data_to_master);
		data_from_master=0;
		while (0 == data_from_master)
		{
			data_from_master=u8spi_slave_receive_byte_MSPI();
		}
		(data_from_master-48)>0 ? SET_BIT(PORTC_REGISTER,MDIO_PIN2) : CLR_BIT(PORTC_REGISTER,MDIO_PIN2) ;
		break;
		
		case 2:
		data_to_master=GET_BIT(PORTC_REGISTER,MDIO_PIN7);
		voidspi_slave_transmit_byte_MSPI(data_to_master);
		data_from_master=0;
		while (0 == data_from_master)
		{
			data_from_master=u8spi_slave_receive_byte_MSPI();
		}
		(data_from_master-48)>0 ? SET_BIT(PORTC_REGISTER,MDIO_PIN7) : CLR_BIT(PORTC_REGISTER,MDIO_PIN7) ;
		break;	
		
		case 3:
		data_to_master=GET_BIT(PORTD_REGISTER,MDIO_PIN3);
		voidspi_slave_transmit_byte_MSPI(data_to_master);
		data_from_master=0;
		while (0 == data_from_master)
		{
			data_from_master=u8spi_slave_receive_byte_MSPI();
		}
		(data_from_master-48)>0 ? SET_BIT(PORTD_REGISTER,MDIO_PIN3) : CLR_BIT(PORTD_REGISTER,MDIO_PIN3) ;
		break;
		
		case 4:
		//data_to_master=GET_BIT(PORTD_REGISTER,MDIO_PIN3);
		voidspi_slave_transmit_byte_MSPI(data_to_master);
		data_from_master=0;
		while (0 == data_from_master)
		{
			data_from_master=u8spi_slave_receive_byte_MSPI();
		}
		//(data_from_master-48)>0 ? SET_BIT(PORTD_REGISTER,MDIO_PIN3) : CLR_BIT(PORTD_REGISTER,MDIO_PIN3);		
		break;
		
		case 5:
		//data_to_master=GET_BIT(PORTD_REGISTER,MDIO_PIN3);
		voidspi_slave_transmit_byte_MSPI(data_to_master);
		data_from_master=0;
		while (0 == data_from_master)
		{
			data_from_master=u8spi_slave_receive_byte_MSPI();
		}
		//(data_from_master-48)>0 ? SET_BIT(PORTD_REGISTER,MDIO_PIN3) : CLR_BIT(PORTD_REGISTER,MDIO_PIN3);
		break;
		
		case 6:
		//data_to_master=GET_BIT(PORTD_REGISTER,MDIO_PIN3);
		voidspi_slave_transmit_byte_MSPI(data_to_master);
		data_from_master=0;
		while (0 == data_from_master)
		{
			data_from_master=u8spi_slave_receive_byte_MSPI();
		}
		//(data_from_master-48)>0 ? SET_BIT(PORTD_REGISTER,MDIO_PIN3) : CLR_BIT(PORTD_REGISTER,MDIO_PIN3);
		break;
		
		case 7:
		//data_to_master=GET_BIT(PORTD_REGISTER,MDIO_PIN3);
		voidspi_slave_transmit_byte_MSPI(data_to_master);
		data_from_master=0;
		while (0 == data_from_master)
		{
			data_from_master=u8spi_slave_receive_byte_MSPI();
		}
		//(data_from_master-48)>0 ? SET_BIT(PORTD_REGISTER,MDIO_PIN3) : CLR_BIT(PORTD_REGISTER,MDIO_PIN3);
		break;
											
		default:
		break;		
		}
	
	}

	}
	return 0;
}

