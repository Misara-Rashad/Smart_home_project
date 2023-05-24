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
#include "MCAL/MADC/MADC_INTERFACE.h"

//HAL
#include "HAL/HLED/HLED_INTERFACE.h"
#include "HAL/HKEYPAD/HKEYPAD_INTERFACE.h"
#include "HAL/HLCD/HLCD_INTERFACE.h"
#include "HAL/HSERVO/HSERVO_INTERFACE.h"
#include "HAL/HTEMP_SENSOR_LM35/HTEMP_SENSOR_LM35_INTERFACE.h"
#include "HAL/HDC_MOTOR/HDC_MOTOR_INTERFACE.h"

f32 x=0;


//MASTER CODE
//functions declaration 
u8 u8check_if_admin_set_pass(void);		//return 0
u8 u8set_admin_pass(void);				//return 1
u8 u8enter_admin_pass(void);			//return 2
u8 u8check_admin_pass(void);			//return 3
u8 u8admin_control(void);				//return 4



//data types 
typedef struct
{
	u8 state_of_led0 ;
	u8 state_of_led1 ;
	u8 state_of_led2 ;
	u8 state_of_led3 ;
	u8 state_of_led4 ;
	u8 state_of_led5 ;
	u8 state_of_led6 ;
	u8 state_of_led7 ;
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
u8 error_message[]= "wrong password";
u8 right_pass[]="welcome";
u8 choose[]="Room 0 to 7:";
u8 set_admin_pass[]="set_admin_pass:";
u8 on[]="ON";
u8 off[]="OFF";
u8 status[]="status:";
u8 choose_op_level[]="ON:1-OFF:0";

int main(void)
{
	//timer1_ctc_interrupt_call_back(servo_start);
	keypad_init();
	lcd_init();
	//spi_master_init();
	
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
	EEPROM_READ_BYTE_MEEPROM(3,&data);
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
	LCDstring(set_admin_pass,sizeof(set_admin_pass),HLCD_NUM0);
	
	while (4!=counter_in_eeprom)
	{
			keypadgetnumber(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
			if (1!=value_in_keypad)
			{
				lcd_write_data(DATA,value_in_keypad,HLCD_NUM0);
				EEPROM_WRITE_BYTE(value_in_keypad,address_in_eeprom);
				address_in_eeprom++;
				counter_in_eeprom++;
				value_in_keypad=1;
			}
	}
	
	lcdclear();
	local_variable=1;
	return local_variable;
}


u8 u8enter_admin_pass(void)
{
	u8 local_variable=1;
	LCDstring(enter_password_message,sizeof(enter_password_message)-1,HLCD_NUM0);
	while (8!=counter_in_eeprom)
	{
			keypadgetnumber(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
			if (1!=value_in_keypad)
			{
				lcd_write_data(DATA,value_in_keypad,HLCD_NUM0);
				EEPROM_WRITE_BYTE(value_in_keypad,address_in_eeprom);
				address_in_eeprom++;
				counter_in_eeprom++;
				value_in_keypad=1;
			}
	}
	
	lcdclear();
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
			EEPROM_READ_BYTE_MEEPROM(i,&saved_pass);
			EEPROM_READ_BYTE_MEEPROM(i+4,&entered_pass);
			if (saved_pass!=entered_pass)
			{
				wrong_pass_flag=1;
				counter_for_wrong_pass_entered++;
				LCDstring(error_message,sizeof(error_message)-1,HLCD_NUM0);
				lcdclear();
				break;
			}
		}
		
		if (1!=wrong_pass_flag)		//right pass
		{
			LCDstring(right_pass,sizeof(right_pass)-1,HLCD_NUM0);
			lcdclear();
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
	while (3==local_variable)
	{
			if (0==lcd_flag)
			{
				LCDstring(choose,sizeof(choose)-1,HLCD_NUM0);
				lcd_flag=1;
			}
			keypadgetnumber(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
			if (1!=value_in_keypad)
			{
				lcd_write_data(DATA,value_in_keypad,HLCD_NUM0);
				spi_master_init();
				switch(value_in_keypad)
				{
					case '0':
					value_in_keypad=1;
					spi_master_transmit_byte(0);
					_delay_ms(100);
					spi_master_receive_byte(&(loads_status.state_of_led0));
					lcdclear();
					LCDstring(status,sizeof(status)-1,HLCD_NUM0);
					loads_status.state_of_led0 ?LCDstring(on,sizeof(on)-1,HLCD_NUM0) :
												LCDstring(off,sizeof(off)-1,HLCD_NUM0);
					lcd_write_data(COMMAND,0xc0,HLCD_NUM0);
					LCDstring(choose_op_level,sizeof(choose_op_level)-1,HLCD_NUM0);
					while (value_in_keypad==1)
					{
						keypadgetnumber(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
						if (1!=value_in_keypad)
						{
							lcd_write_data(DATA,value_in_keypad,HLCD_NUM0);
							spi_master_transmit_byte(value_in_keypad);
							lcdclear();
							lcd_flag=0;
						}
					}
					//local_variable=4;
					break	;
					
					case '1':
					value_in_keypad=1;
					spi_master_transmit_byte(1);
					_delay_ms(100);
					spi_master_receive_byte(&(loads_status.state_of_led1));
					lcdclear();
					LCDstring(status,sizeof(status)-1,HLCD_NUM0);
					loads_status.state_of_led1 ?LCDstring(on,sizeof(on)-1,HLCD_NUM0) :
												LCDstring(off,sizeof(off)-1,HLCD_NUM0);
					lcd_write_data(COMMAND,0xc0,HLCD_NUM0);
					LCDstring(choose_op_level,sizeof(choose_op_level)-1,HLCD_NUM0);
					while (value_in_keypad==1)
					{
						keypadgetnumber(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
						if (1!=value_in_keypad)
						{
							lcd_write_data(DATA,value_in_keypad,HLCD_NUM0);
							spi_master_transmit_byte(value_in_keypad);	
							lcdclear();
							lcd_flag=0;				
						}
					}
				//	local_variable=4;
					break	;
					
					case '2':
					value_in_keypad=1;
					spi_master_transmit_byte(2);
					_delay_ms(100);
					spi_master_receive_byte(&(loads_status.state_of_led2));
					lcdclear();
					LCDstring(status,sizeof(status)-1,HLCD_NUM0);
					loads_status.state_of_led2 ?LCDstring(on,sizeof(on)-1,HLCD_NUM0) :
												LCDstring(off,sizeof(off)-1,HLCD_NUM0);
					lcd_write_data(COMMAND,0xc0,HLCD_NUM0);
					LCDstring(choose_op_level,sizeof(choose_op_level)-1,HLCD_NUM0);
					while (value_in_keypad==1)
					{
						keypadgetnumber(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
						if (1!=value_in_keypad)
						{
							lcd_write_data(DATA,value_in_keypad,HLCD_NUM0);
							spi_master_transmit_byte(value_in_keypad);
							lcdclear();
							lcd_flag=0;	
						}
					}
					//local_variable=4;
					break	;
					
					case '3':
					value_in_keypad=1;
					spi_master_transmit_byte(3);
					_delay_ms(100);
					spi_master_receive_byte(&(loads_status.state_of_led3));
					lcdclear();
					LCDstring(status,sizeof(status)-1,HLCD_NUM0);
					loads_status.state_of_led3 ?LCDstring(on,sizeof(on)-1,HLCD_NUM0) :
												LCDstring(off,sizeof(off)-1,HLCD_NUM0);
					lcd_write_data(COMMAND,0xc0,HLCD_NUM0);
					LCDstring(choose_op_level,sizeof(choose_op_level)-1,HLCD_NUM0);
					while (value_in_keypad==1)
					{
						keypadgetnumber(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
						if (1!=value_in_keypad)
						{
							lcd_write_data(DATA,value_in_keypad,HLCD_NUM0);
							spi_master_transmit_byte(value_in_keypad);
							lcdclear();
							lcd_flag=0;	
						}
					}
					//local_variable=4;					
					break	;
					
					case '4':
					value_in_keypad=1;
					spi_master_transmit_byte(4);
					_delay_ms(100);
					spi_master_receive_byte(&(loads_status.state_of_led4));
					lcdclear();
					LCDstring(status,sizeof(status)-1,HLCD_NUM0);
					loads_status.state_of_led4 ?LCDstring(on,sizeof(on)-1,HLCD_NUM0) :
												LCDstring(off,sizeof(off)-1,HLCD_NUM0);
					lcd_write_data(COMMAND,0xc0,HLCD_NUM0);
					LCDstring(choose_op_level,sizeof(choose_op_level)-1,HLCD_NUM0);
					while (value_in_keypad==1)
					{
						keypadgetnumber(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
						if (1!=value_in_keypad)
						{
							lcd_write_data(DATA,value_in_keypad,HLCD_NUM0);
							spi_master_transmit_byte(value_in_keypad);
							lcdclear();
							lcd_flag=0;	
						}
					}				
					//local_variable=4;
					break	;
					
					case '5':
					value_in_keypad=1;
					spi_master_transmit_byte(5);
					_delay_ms(100);
					spi_master_receive_byte(&(loads_status.state_of_led5));
					lcdclear();
					LCDstring(status,sizeof(status)-1,HLCD_NUM0);
					loads_status.state_of_led5 ?LCDstring(on,sizeof(on)-1,HLCD_NUM0) :
												LCDstring(off,sizeof(off)-1,HLCD_NUM0);
					lcd_write_data(COMMAND,0xc0,HLCD_NUM0);
					LCDstring(choose_op_level,sizeof(choose_op_level)-1,HLCD_NUM0);
					while (value_in_keypad==1)
					{
						keypadgetnumber(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
						if (1!=value_in_keypad)
						{
							lcd_write_data(DATA,value_in_keypad,HLCD_NUM0);
							spi_master_transmit_byte(value_in_keypad);
							lcdclear();
							lcd_flag=0;	
						}
					}					
					//local_variable=4;
					break	;
					
					case '6':
					value_in_keypad=1;
					spi_master_transmit_byte(6);
					_delay_ms(100);
					spi_master_receive_byte(&(loads_status.state_of_led6));
					lcdclear();
					LCDstring(status,sizeof(status)-1,HLCD_NUM0);
					loads_status.state_of_led6 ?LCDstring(on,sizeof(on)-1,HLCD_NUM0) :
												LCDstring(off,sizeof(off)-1,HLCD_NUM0);
					lcd_write_data(COMMAND,0xc0,HLCD_NUM0);
					LCDstring(choose_op_level,sizeof(choose_op_level)-1,HLCD_NUM0);
					while (value_in_keypad==1)
					{
						keypadgetnumber(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
						if (1!=value_in_keypad)
						{
							lcd_write_data(DATA,value_in_keypad,HLCD_NUM0);
							spi_master_transmit_byte(value_in_keypad);
							lcdclear();
							lcd_flag=0;	
						}
					}				
					//local_variable=4;
					break	;
					
					case '7':
					value_in_keypad=1;
					spi_master_transmit_byte(7);
					_delay_ms(100);
					spi_master_receive_byte(&(loads_status.state_of_led7));
					lcdclear();
					LCDstring(status,sizeof(status)-1,HLCD_NUM0);
					loads_status.state_of_led7 ?LCDstring(on,sizeof(on)-1,HLCD_NUM0) :
												LCDstring(off,sizeof(off)-1,HLCD_NUM0);
					lcd_write_data(COMMAND,0xc0,HLCD_NUM0);
					LCDstring(choose_op_level,sizeof(choose_op_level)-1,HLCD_NUM0);
					while (value_in_keypad==1)
					{
						keypadgetnumber(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
						if (1!=value_in_keypad)
						{
							lcd_write_data(DATA,value_in_keypad,HLCD_NUM0);
							spi_master_transmit_byte(value_in_keypad);
							lcdclear();
							lcd_flag=0;	
						}
					}					
					//local_variable=4;
					break	;
					
					default:
					break	;
					
				}
				value_in_keypad=1;
			}
	}

		
		return local_variable;	
}





//SLAVE CODE
/*u8 data_from_master=0;
u8 data_to_master=0;
int main(void)
{	
	led_init();

	led_on(&HLED_arrayofleds[0]);		//led1
	
	led_off(&HLED_arrayofleds[1]);		//led2

	led_on(&HLED_arrayofleds[2]);		//led3

	lcd_init();	
	
	spi_slave_init();
	
	while (1)
	{
		
	spi_slave_receive_byte(&data_from_master);
	if(data_from_master !=0)
	{
	lcd_write_data(DATA,'0'+data_from_master,HLCD_NUM0);
	switch(data_from_master)
		{
			
		case 0:
		//data_to_master=GET_BIT(PORTC_REGISTER,MDIO_PIN2);
		spi_slave_transmit_byte(data_to_master);
		data_from_master=0;
		while (0 == data_from_master)
		{
			spi_slave_receive_byte(&data_from_master);
		}
		//(data_from_master-48)>0 ? SET_BIT(PORTC_REGISTER,MDIO_PIN2) : CLR_BIT(PORTC_REGISTER,MDIO_PIN2) ;
		break;
					
		case 1:
		data_to_master=GET_BIT(PORTC_REGISTER,MDIO_PIN2);
		spi_slave_transmit_byte(data_to_master);
		data_from_master=0;
		while (0 == data_from_master)
		{
			spi_slave_receive_byte(&data_from_master);
		}
		(data_from_master-48)>0 ? SET_BIT(PORTC_REGISTER,MDIO_PIN2) : CLR_BIT(PORTC_REGISTER,MDIO_PIN2) ;
		break;
		
		case 2:
		data_to_master=GET_BIT(PORTC_REGISTER,MDIO_PIN7);
		spi_slave_transmit_byte(data_to_master);
		data_from_master=0;
		while (0 == data_from_master)
		{
			spi_slave_receive_byte(&data_from_master);
		}
		(data_from_master-48)>0 ? SET_BIT(PORTC_REGISTER,MDIO_PIN7) : CLR_BIT(PORTC_REGISTER,MDIO_PIN7) ;
		break;	
		
		case 3:
		data_to_master=GET_BIT(PORTD_REGISTER,MDIO_PIN3);
		spi_slave_transmit_byte(data_to_master);
		data_from_master=0;
		while (0 == data_from_master)
		{
			spi_slave_receive_byte(&data_from_master);
		}
		(data_from_master-48)>0 ? SET_BIT(PORTD_REGISTER,MDIO_PIN3) : CLR_BIT(PORTD_REGISTER,MDIO_PIN3) ;
		break;
		
		case 4:
		//data_to_master=GET_BIT(PORTD_REGISTER,MDIO_PIN3);
		spi_slave_transmit_byte(data_to_master);
		data_from_master=0;
		while (0 == data_from_master)
		{
			spi_slave_receive_byte(&data_from_master);
		}
		//(data_from_master-48)>0 ? SET_BIT(PORTD_REGISTER,MDIO_PIN3) : CLR_BIT(PORTD_REGISTER,MDIO_PIN3);		
		break;
		
		case 5:
		//data_to_master=GET_BIT(PORTD_REGISTER,MDIO_PIN3);
		spi_slave_transmit_byte(data_to_master);
		data_from_master=0;
		while (0 == data_from_master)
		{
			spi_slave_receive_byte(&data_from_master);
		}
		//(data_from_master-48)>0 ? SET_BIT(PORTD_REGISTER,MDIO_PIN3) : CLR_BIT(PORTD_REGISTER,MDIO_PIN3);
		break;
		
		case 6:
		//data_to_master=GET_BIT(PORTD_REGISTER,MDIO_PIN3);
		spi_slave_transmit_byte(data_to_master);
		data_from_master=0;
		while (0 == data_from_master)
		{
			spi_slave_receive_byte(&data_from_master);
		}
		//(data_from_master-48)>0 ? SET_BIT(PORTD_REGISTER,MDIO_PIN3) : CLR_BIT(PORTD_REGISTER,MDIO_PIN3);
		break;
		
		case 7:
		//data_to_master=GET_BIT(PORTD_REGISTER,MDIO_PIN3);
		spi_slave_transmit_byte(data_to_master);
		data_from_master=0;
		while (0 == data_from_master)
		{
			spi_slave_receive_byte(&data_from_master);
		}
		//(data_from_master-48)>0 ? SET_BIT(PORTD_REGISTER,MDIO_PIN3) : CLR_BIT(PORTD_REGISTER,MDIO_PIN3);
		break;
											
		default:
		break;		
		}
	
	}

	}
	return 0;
}*/


//servo motor
/*int main(void)
{
	timer1_ctc_interrupt_call_back(servo_start);


	while (1)
	{
		for (u8 i=0;i<180;i+=5)
		{
			servo_init(i,&x);
			_delay_ms(100);
		}
		for (u8 i=180;i>0;i-=5)
		{
			servo_init(i,&x);
			_delay_ms(100);
		}
	}
	return 0;
}*/


//temperature sensor
/*extern MADC_T HTEMP_SENSOR;
f32 temp=0;
tenumFncErrorState error= LSTY_EXECUTED_SUCCESSFULLY;
int main(void)
{
	error=tenumFncErrorStateinittemp_sensor(&HTEMP_SENSOR);
	while (1)
	{
	error=tenumFncErrorStatetempvalue(&HTEMP_SENSOR,&temp);
	_delay_ms(100);
	}
	return 0;
}*/



//DC motor
/*extern MOTOR_T MOTOR1;	
tenumFncErrorState state=LSTY_EXECUTED_SUCCESSFULLY;
int main(void)
{
	state=Motor_init(&MOTOR1);
	while (1)
	{
	state= Motor_right(&MOTOR1);
	_delay_ms(3000);
	state= tenumFncErrorStateMotor_stop(&MOTOR1);
	_delay_ms(3000);
	state= tenumFncErrorStateMotor_left(&MOTOR1);
	_delay_ms(3000);

	}
	return 0;
}*/



