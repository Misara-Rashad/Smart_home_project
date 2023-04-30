/*
 * main.c
 *
 * Created: 16/04/2023 12:45:02 PM
 *  Author: Misra
 */ 

#define F_CPU	16000000UL
#include <util/delay.h>
#define no_of_trials		3


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

//MASTER CODE
/*u8 state_of_led0=100;
u8 state_of_led1=100;
u8 state_of_led2=100;
u8 value_in_keypad = 1;
u8 counter_in_eeprom=0;
u8 wrong_pass_flag=0;
u8 pass_saved_to_eeprom=0;
u8 q=0;
u8 sequence=1;
u8 lcd_flag=0;
u8 counter_for_wrong_pass_entered=no_of_trials;

u8 enter_password_message[]="password:";
u8 error_massage[]= "wrong password";
u8 right_pass[]="welcome";
u8 choose[]="Room 1 to 9:";
int main(void)
{
	voidinitkeypad_HKEYPAD();
	voidinitlcd_HLCD();
	voidinitspi_master_MSPI();	
	
	//password saved to master eeprom
	voidEEPROM_WRITE_BYTE('4',4);
	voidEEPROM_WRITE_BYTE('5',5);
	voidEEPROM_WRITE_BYTE('6',6);
	voidEEPROM_WRITE_BYTE('7',7);

	pass_saved_to_eeprom=u8EEPROM_READ_BYTE_MEEPROM(3);

	voidLCDstring_HLCD(enter_password_message,9,HLCD_NUM0);
	while (1)
	{
		if (1 == sequence)
		{
				//enter_pass_again:
				enumkeypadgetnumber_HKEYPAD(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
				if (value_in_keypad != 1 && counter_in_eeprom<4)
					{
						voidEEPROM_WRITE_BYTE(value_in_keypad,counter_in_eeprom);
						voidLCDwrite_data_HLCD(DATA,value_in_keypad,HLCD_NUM0);
						value_in_keypad=1;
						counter_in_eeprom++;
					}
					
		     	else{}

		pass_saved_to_eeprom=u8EEPROM_READ_BYTE_MEEPROM(3);
		
				if ( pass_saved_to_eeprom != 255 && wrong_pass_flag ==0)
					{
						voidlcdclear();
							for (u8 i=0;i<4;i++)
								{
									q=u8EEPROM_READ_BYTE_MEEPROM(i+4);
									pass_saved_to_eeprom=u8EEPROM_READ_BYTE_MEEPROM(i);
									if (q != pass_saved_to_eeprom)
										{
											voidLCDstring_HLCD(error_massage,14,HLCD_NUM0);
											wrong_pass_flag=1;
											counter_for_wrong_pass_entered++;
											if (counter_for_wrong_pass_entered ==3)
											{
													break;
											}
										//	goto enter_pass_again;
										}
										
									else{}
			}
			
			if (wrong_pass_flag !=1)    //wrong_pass_flag=0 so entered right password
			{
				voidLCDstring_HLCD(right_pass,7,HLCD_NUM0);
				wrong_pass_flag=1;
				sequence=2;
			}
			
			}
		else{}


		
		}

	else if (2==sequence)    //entered a right password so we will enter seq=2 which allows to control
		{
		if (0==lcd_flag)
		{
		voidlcdclear();
		voidLCDstring_HLCD(choose,12,HLCD_NUM0);
		lcd_flag=1;
		}
		
		else{}
			
		enumkeypadgetnumber_HKEYPAD(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
		if (value_in_keypad != 1)
		{
		voidLCDwrite_data_HLCD(DATA,value_in_keypad,HLCD_NUM0);
		voidinitspi_master_MSPI();
		switch(value_in_keypad)
			{
			case '1':
			voidspi_master_transmit_byte_MSPI(1);
			_delay_ms(100);
			state_of_led0=u8spi_master_receive_byte_MSPI();
			voidLCDwrite_data_HLCD(DATA,'0'+state_of_led0,HLCD_NUM0);
			break; 

			case '2':
			voidspi_master_transmit_byte_MSPI(2);
			_delay_ms(100);
			state_of_led1=u8spi_master_receive_byte_MSPI();
			voidLCDwrite_data_HLCD(DATA,'0'+state_of_led1,HLCD_NUM0);
			break;

			case '3':
			voidspi_master_transmit_byte_MSPI(3);
			_delay_ms(100);
			state_of_led2=u8spi_master_receive_byte_MSPI();
			voidLCDwrite_data_HLCD(DATA,'0'+state_of_led2,HLCD_NUM0);
			break;
			
			default:
			break;
			}
			value_in_keypad=1;
		}
		}
}
	
	return 0;
	
}*/




//SLAVE CODE
/*u8 data_from_master=0;
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
		case 1:
		data_to_master=GET_BIT(PORTC_REGISTER,MDIO_PIN2);
		voidspi_slave_transmit_byte_MSPI(data_to_master);
		break;
		
		case 2:
		data_to_master=GET_BIT(PORTC_REGISTER,MDIO_PIN7);
		voidspi_slave_transmit_byte_MSPI(data_to_master);
		break;	
		
		case 3:
		data_to_master=GET_BIT(PORTD_REGISTER,MDIO_PIN3);
		voidspi_slave_transmit_byte_MSPI(data_to_master);
		break;						
		
		default:
		break;		
		}
	
	}

	}
	return 0;
}*/





//ULTRASONIC CODE
/*u8 y=0;
f32 x=0;
f32 distance_in_cm=0,distance_in_m=0;

DIO_PIN PD7_pin={
	.enumpin= MDIO_PIN7,
	.enumport= MDIO_PORTD,
	.enummode= MDIO_OUTPUT,
	.enumoutputlevel=MDIO_HIGH
};

void fun (void);

int main(void)
{
	voidinitlcd_HLCD();
	voidinitinterrupt_MINT();
	voidINTENABLEHandler_MINT(MINT_EXINT0, MINT_ISC_RISING_EDGE);
	voidINTSetCallBack_MINT(fun, MINT_EXINT0);
	enumpindirection_MDIO(&PD7_pin);
	

	
	while (1)
	{
			enumpinvalue_selection_MDIO(&PD7_pin,MDIO_HIGH);
			_delay_ms(0.01); //delay 10us
			enumpinvalue_selection_MDIO(&PD7_pin,MDIO_LOW);
			x=f32timer_get_timer_value_in_us(&TIMER0_STRUCT);
			distance_in_cm=(x)/58;
			voidlcdfloat_number_HLCD(distance_in_cm,HLCD_NUM0);
			distance_in_m=distance_in_cm/100;
			voidLCDwrite_data_HLCD(DATA,' ',HLCD_NUM0);
			voidlcdfloat_number_HLCD(distance_in_m,HLCD_NUM0);
			_delay_ms(1000);
			voidlcdclear();
	}
	return 0;
}



void fun (void)
{
	if (0==y)
	{
	voidtimer_start_timer_MTIMER(&TIMER0_STRUCT);
	voidINTENABLEHandler_MINT(MINT_EXINT0, MINT_ISC_FALLING_EDGE);
	y=1;
	}
	
	else if (1==y)
	{
	voidtimer_end_timer_MTIMER(&TIMER0_STRUCT);
	y=0;
	voidINTENABLEHandler_MINT(MINT_EXINT0, MINT_ISC_RISING_EDGE);
	}
	
	else{}
}*/



/*f32 x=0;
u32 y=0;
DIO_PIN PD7_pin={
	.enumpin= MDIO_PIN7,
	.enumport= MDIO_PORTD,
	.enummode= MDIO_OUTPUT,
	.enumoutputlevel=MDIO_HIGH
};

int main(void)
{
	
	enumpindirection_MDIO(&PD7_pin);
	enumpinvalue_selection_MDIO(&PD7_pin,MDIO_HIGH);
	voidtimer_start_timer_MTIMER(&TIMER0_STRUCT);

	
	while (1)
	{
		if(100 ==u16get_counter0_value())
		{
			x=f32timer_get_timer_value_in_ms(&TIMER0_STRUCT);
			y=u16get_counter0_value();
		}
	}
	
	return 0;
}*/




//f32 x=0;
//u32 y=0;
//
//DIO_PIN PD7_pin={
	//.enumpin= MDIO_PIN7,
	//.enumport= MDIO_PORTD,
	//.enummode= MDIO_OUTPUT,
	//.enumoutputlevel=MDIO_HIGH
//};
//
//int main(void)
//{
	//
	//voidtimer_start_timer_MTIMER(&TIMER0_STRUCT);
	//_delay_ms(1600);
	//voidtimer_end_timer_MTIMER(&TIMER0_STRUCT);
	//x=f32timer_get_timer_value_in_ms(&TIMER0_STRUCT);
	//y=u16get_counter0_value();
	//while (1)
	//{
//
	//}
	//
	//return 0;
//}


//MASTER CODE
u8 state_of_led0=100;
u8 state_of_led1=100;
u8 state_of_led2=100;
u8 value_in_keypad = 0;
u8 add_of_pass_saved_in_eeprom=0;
u8 add_of_pass_entered_by_user=4;
u8 sequence=0;
u8 lcd_flag=0;
u8 counter_for_wrong_pass_entered=0;

u8 set_admin_pass[]="Set Admin Pass of 4 digits:";
u8 pass_saved_successfully[]="password saved successfully";
u8 enter_password_message[]="password:";
u8 error_massage[]= "wrong password";
u8 restart_system[]="Restart....";
u8 right_pass[]="welcome :)";
u8 choose[]="Room 1 to 9:";
u8 on[]="on";
u8 off[]="off";
int main(void)
{
	voidinitkeypad_HKEYPAD();
	voidinitlcd_HLCD();
	if (u8EEPROM_READ_BYTE_MEEPROM(3) != 0xFF)
	{
		sequence=1;
	}
	
	while (1)
	{
		
		
		if (0 == sequence) //to save password of admin to master eeprom in the beigning
		{
			if (0==lcd_flag)
			{
				voidLCDstring_HLCD(set_admin_pass,27,HLCD_NUM0);
				lcd_flag=1;
			}
			
			else
			{
				enumkeypadgetnumber_HKEYPAD(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
				if (0 != value_in_keypad)
				{
					voidEEPROM_WRITE_BYTE(value_in_keypad,add_of_pass_saved_in_eeprom);
					voidLCDwrite_data_HLCD(DATA,value_in_keypad,HLCD_NUM0);
					if (3==add_of_pass_saved_in_eeprom)
					{
						voidlcdclear();
						voidLCDstring_HLCD(pass_saved_successfully,27,HLCD_NUM0);
						lcd_flag=0;
						sequence=1;
					}
					add_of_pass_saved_in_eeprom++;  //0 1 2 3
					value_in_keypad=0;
				}
			}

		} 
		else if (1 == sequence  && counter_for_wrong_pass_entered <= no_of_trials)
		{
			
			if (0==lcd_flag)
			{
				voidlcdclear();
				voidLCDstring_HLCD(enter_password_message,9,HLCD_NUM0);
				lcd_flag=1;
			}
			
			else
			{
				enumkeypadgetnumber_HKEYPAD(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
				if (0!=value_in_keypad)
				{
					voidEEPROM_WRITE_BYTE(value_in_keypad,add_of_pass_entered_by_user);
					voidLCDwrite_data_HLCD(DATA,value_in_keypad,HLCD_NUM0);
					value_in_keypad=0;
					if (7==add_of_pass_entered_by_user)
					{
						voidlcdclear();
						for (u8 i=0;i<4;i++)
						{
							if (u8EEPROM_READ_BYTE_MEEPROM(i)!= u8EEPROM_READ_BYTE_MEEPROM(i+4))
							{
								voidLCDstring_HLCD(error_massage,14,HLCD_NUM0);
								counter_for_wrong_pass_entered++;
								if (3==counter_for_wrong_pass_entered)
								{
									lcd_flag=0;
									voidLCDstring_HLCD(restart_system,11,HLCD_NUM0);
								}
								add_of_pass_entered_by_user=3;
								lcd_flag=0;
								break;
							}
							
							else if ((u8EEPROM_READ_BYTE_MEEPROM(i) == u8EEPROM_READ_BYTE_MEEPROM(i+4)) 
									 && 3==i)
							{
								voidLCDstring_HLCD(right_pass,10,HLCD_NUM0);
								_delay_ms(500);
								lcd_flag=0;
								sequence=2;
							}
						}
					}
					add_of_pass_entered_by_user++;
				}
			}
			
		}
		else if (2 == sequence)
		{
			if (0==lcd_flag)
			{
				voidlcdclear();
				voidLCDstring_HLCD(choose,12,HLCD_NUM0);
				lcd_flag=1;
			}
			else{}
				
			enumkeypadgetnumber_HKEYPAD(&HKEYPAD_arrayofkeypads[0],&value_in_keypad);
			if (0!=value_in_keypad)
			{
				voidLCDwrite_data_HLCD(DATA,value_in_keypad,HLCD_NUM0);
				voidinitspi_master_MSPI();
				switch(value_in_keypad)
					{
						case '1':
						voidspi_master_transmit_byte_MSPI(1);
						_delay_ms(100);
						state_of_led0=u8spi_master_receive_byte_MSPI();
						if (0==state_of_led0)
						{
							voidlcdclear();
							voidLCDstring_HLCD(off,3,HLCD_NUM0);
						}
						else
						{
							voidlcdclear();
							voidLCDstring_HLCD(on,2,HLCD_NUM0);							
						}
						break;

						case '2':
						voidspi_master_transmit_byte_MSPI(2);
						_delay_ms(100);
						state_of_led1=u8spi_master_receive_byte_MSPI();
						if (0==state_of_led1)
						{
							voidlcdclear();
							voidLCDstring_HLCD(off,3,HLCD_NUM0);
						}
						else
						{
							voidlcdclear();
							voidLCDstring_HLCD(on,2,HLCD_NUM0);
						}
						break;

						case '3':
						voidspi_master_transmit_byte_MSPI(3);
						_delay_ms(100);
						state_of_led2=u8spi_master_receive_byte_MSPI();
						if (0==state_of_led2)
						{
							voidlcdclear();
							voidLCDstring_HLCD(off,3,HLCD_NUM0);
						}
						else
						{
							voidlcdclear();
							voidLCDstring_HLCD(on,2,HLCD_NUM0);
						}
						break;
			
						default:
						break;
					}
				value_in_keypad=0;
			}
			
		}
	}
	
	return 0;	
}