/*
 * HLCD_PROGRAM.c
 *
 * Created: 21/02/2023 11:13:02 PM
 *  Author: Misra
 */ 


#define F_CPU 16000000UL
#include <util/delay.h>


/*...........includes section.........*/
//libraries
#include "../../Libraries_/LIB_STDTypes.h"

//MCAL
#include "../../MCAL/MDIO/MDIO_INTERFACE.h"

//HAL

#include "HLCD_INTERFACE.h"


tenumFncErrorState lcd_init(void)
{	
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	u8 u8local_no_of_lcds=0;
	for(u8local_no_of_lcds;u8local_no_of_lcds < NUM_OF_LCDS;u8local_no_of_lcds++)
	{
		
		pin_direction(&HLCD_arrayoflcds[u8local_no_of_lcds].RS);
		pin_direction(&HLCD_arrayoflcds[u8local_no_of_lcds].RW);
		pin_direction(&HLCD_arrayoflcds[u8local_no_of_lcds].ENABLE);
		
		
		if ((HLCD_arrayoflcds[u8local_no_of_lcds].enummode==EIGHT_BIT_MODE))
		{
				pin_direction(&HLCD_arrayoflcds[u8local_no_of_lcds].D0);
				pin_direction(&HLCD_arrayoflcds[u8local_no_of_lcds].D1);
				pin_direction(&HLCD_arrayoflcds[u8local_no_of_lcds].D2);
				pin_direction(&HLCD_arrayoflcds[u8local_no_of_lcds].D3);
				
				pin_direction(&HLCD_arrayoflcds[u8local_no_of_lcds].D4);
				pin_direction(&HLCD_arrayoflcds[u8local_no_of_lcds].D5);
				pin_direction(&HLCD_arrayoflcds[u8local_no_of_lcds].D6);
				pin_direction(&HLCD_arrayoflcds[u8local_no_of_lcds].D7);
		}
		
		else if((HLCD_arrayoflcds[u8local_no_of_lcds].enummode==four_BIT_MODE)) //4bit_mode
		{
				pin_direction(&HLCD_arrayoflcds[u8local_no_of_lcds].D4);
				pin_direction(&HLCD_arrayoflcds[u8local_no_of_lcds].D5);
				pin_direction(&HLCD_arrayoflcds[u8local_no_of_lcds].D6);
				pin_direction(&HLCD_arrayoflcds[u8local_no_of_lcds].D7);	
		}
		
			_delay_ms(30); //delay after LCD power on 
			
			
		if ((HLCD_arrayoflcds[u8local_no_of_lcds].enummode==EIGHT_BIT_MODE))
		{
				lcd_write_data(COMMAND,FUNCTION_SET,u8local_no_of_lcds);	//0x38	
		}
		
		else if((HLCD_arrayoflcds[u8local_no_of_lcds].enummode==four_BIT_MODE)) //4bit_mode
		{
			//functions set
		lcd_write_data(COMMAND,LCD_4BitMode1,u8local_no_of_lcds); //0x33
		lcd_write_data(COMMAND,LCD_4BitMode2,u8local_no_of_lcds);  //0x32
		lcd_write_data(COMMAND,LCD_2Lines5X8_4BitMode,u8local_no_of_lcds); //0x28
		
		//instead of sending 0x33 then 0x32 ....send 0x02 
		}	
		
			_delay_ms(1);
			
			//display on\off control
			lcd_write_data(COMMAND,0x0F,u8local_no_of_lcds);  
			_delay_ms(1);

			//display clear
			lcd_write_data(COMMAND,0x01,u8local_no_of_lcds); 
			_delay_ms(1);
			
			//entry mode
			lcd_write_data(COMMAND,0x06,u8local_no_of_lcds); //entry mode 0b0000 0100

	}
	
	return error;
}


tenumFncErrorState lcd_write_data(HLCD_DATA_TYPE enumcpy_data_type,u8 u8Cpy_LCDData, u8 u8Cpy_LCDNumber)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (enumcpy_data_type<COMMAND || enumcpy_data_type>DATA)
	{
		error=LSTY_OUT_OF_RANGE;
	}
	else
	{
			Register reglocal_data;

			if ((u8Cpy_LCDData>=0 && u8Cpy_LCDNumber<NUM_OF_LCDS))
			{
				if(enumcpy_data_type==COMMAND)
				{
					HLCD_arrayoflcds[u8Cpy_LCDNumber].RS.enumoutputlevel=MDIO_LOW;
				}
				
				else if((enumcpy_data_type==DATA))
				{
					HLCD_arrayoflcds[u8Cpy_LCDNumber].RS.enumoutputlevel=MDIO_HIGH;
				}
				
				HLCD_arrayoflcds[u8Cpy_LCDNumber].RW.enumoutputlevel=MDIO_LOW;
				pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].RS);
				pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].RW);
				
				
				
				if((HLCD_arrayoflcds[u8Cpy_LCDNumber].enummode==four_BIT_MODE))
				{
					reglocal_data.Byte=u8Cpy_LCDData & (0xf0);
					//taking most significant 4 bits first
					HLCD_arrayoflcds[u8Cpy_LCDNumber].D4.enumoutputlevel =reglocal_data.Bit.B4;
					HLCD_arrayoflcds[u8Cpy_LCDNumber].D5.enumoutputlevel =reglocal_data.Bit.B5;
					HLCD_arrayoflcds[u8Cpy_LCDNumber].D6.enumoutputlevel =reglocal_data.Bit.B6;
					HLCD_arrayoflcds[u8Cpy_LCDNumber].D7.enumoutputlevel =reglocal_data.Bit.B7;
					
					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].D4);
					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].D5);
					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].D6);
					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].D7);
					
					
					//enable pin high for 10ms then low before sending least 4 significant bits(generate a falling edge)
					HLCD_arrayoflcds[u8Cpy_LCDNumber].ENABLE.enumoutputlevel=MDIO_HIGH;
					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].ENABLE);
					_delay_ms(10);
					HLCD_arrayoflcds[u8Cpy_LCDNumber].ENABLE.enumoutputlevel=MDIO_LOW;
					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].ENABLE);

					reglocal_data.Byte=u8Cpy_LCDData<<4;
					//taking least significant 4 bits first
					HLCD_arrayoflcds[u8Cpy_LCDNumber].D4.enumoutputlevel =reglocal_data.Bit.B4;
					HLCD_arrayoflcds[u8Cpy_LCDNumber].D5.enumoutputlevel =reglocal_data.Bit.B5;
					HLCD_arrayoflcds[u8Cpy_LCDNumber].D6.enumoutputlevel =reglocal_data.Bit.B6;
					HLCD_arrayoflcds[u8Cpy_LCDNumber].D7.enumoutputlevel =reglocal_data.Bit.B7;
					
					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].D4);
					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].D5);
					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].D6);
					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].D7);
					
					//enable pin high for 10ms then low after sending least 4 significant bits
					HLCD_arrayoflcds[u8Cpy_LCDNumber].ENABLE.enumoutputlevel=MDIO_HIGH;
					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].ENABLE);
					_delay_ms(10);
					HLCD_arrayoflcds[u8Cpy_LCDNumber].ENABLE.enumoutputlevel=MDIO_LOW;
					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].ENABLE);

				}
				
				else if((HLCD_arrayoflcds[u8Cpy_LCDNumber].enummode==EIGHT_BIT_MODE)) //8 bit mode
				{
					reglocal_data.Byte=u8Cpy_LCDData;
					HLCD_arrayoflcds[u8Cpy_LCDNumber].D0.enumoutputlevel=reglocal_data.Bit.B0;
					HLCD_arrayoflcds[u8Cpy_LCDNumber].D1.enumoutputlevel=reglocal_data.Bit.B1;
					HLCD_arrayoflcds[u8Cpy_LCDNumber].D2.enumoutputlevel=reglocal_data.Bit.B2;
					HLCD_arrayoflcds[u8Cpy_LCDNumber].D3.enumoutputlevel=reglocal_data.Bit.B3;
					HLCD_arrayoflcds[u8Cpy_LCDNumber].D4.enumoutputlevel=reglocal_data.Bit.B4;
					HLCD_arrayoflcds[u8Cpy_LCDNumber].D5.enumoutputlevel=reglocal_data.Bit.B5;
					HLCD_arrayoflcds[u8Cpy_LCDNumber].D6.enumoutputlevel=reglocal_data.Bit.B6;
					HLCD_arrayoflcds[u8Cpy_LCDNumber].D7.enumoutputlevel=reglocal_data.Bit.B7;

					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].D0);
					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].D1);
					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].D2);
					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].D3);
					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].D4);
					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].D5);
					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].D6);
					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].D7);

					//enable pin high for 10ms then low after sending the 8 bits
					HLCD_arrayoflcds[u8Cpy_LCDNumber].ENABLE.enumoutputlevel=MDIO_HIGH;
					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].ENABLE);
					_delay_ms(10);
					HLCD_arrayoflcds[u8Cpy_LCDNumber].ENABLE.enumoutputlevel=MDIO_LOW;
					pin_value(&HLCD_arrayoflcds[u8Cpy_LCDNumber].ENABLE);

				}
				

			}

	}
	return error;

}




tenumFncErrorState LCDintegartostring(u32 u32cpu_integar,  u8 u8Cpy_LCDNumber) //maximum 10-digits number (u32->4,294,967,295)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	//first get no of digits in the number
	u8 digit;
	u32 n,printed_num,i;
	digit=1;
	for(i=10;;i*=10)
	{
		n=u32cpu_integar/i;
		if(n==0)
		{
			break;
		}

		digit++;
	}
	
	
	n=1;
	for (i=0;i<(digit-1);i++)
	{
	n*=10;
	}
	
	
	i=0;
	for(n;n>0;n/=10)
	{
	if(i == 0)//first loop only assuming 4 digits
		{
		printed_num=u32cpu_integar/n;
		lcd_write_data(DATA,'0' + printed_num ,u8Cpy_LCDNumber);	
		i++;
		}	
		
		else
		{
		printed_num=(u32cpu_integar/n)%10;
		lcd_write_data(DATA,'0' + printed_num ,u8Cpy_LCDNumber);
		i++;
		}


	if(i==digit)
		{
			break;
		}
	
	}

	return error;

}




tenumFncErrorState LCDstring(u8 u8array_of_char[],u8 u8array_size,u8 u8Cpy_LCDNumber)
{	
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	u8 y=0;
	for (u8 x=0;x<u8array_size;x++)
	{
		if (15==x && 0==y)
		{
			lcd_write_data(COMMAND,0xc0,u8Cpy_LCDNumber);
			y=1;
		}
		lcd_write_data(DATA,u8array_of_char[x],u8Cpy_LCDNumber);
	}
	return error;
}


tenumFncErrorState lcdfloat_number(f32 f32float_number,u8 u8Cpy_LCDNumber)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	u32 x=(u32)f32float_number;
	f32 f32number_after_printing_real_number=0,number_to_be_printed_with_4_digit_resolution=0;
	//first get no of digits in the number
	u8 digit;
	u32 n,printed_num,i;
	digit=1;
	for(i=10;;i*=10)
	{
		n=x/i;
		if(n==0)
		{
			break;
		}

		digit++;
	}
	
	
	n=1;
	for (i=0;i<(digit-1);i++)
	{
		n*=10;
	}
	
	
	i=0;
	for(n;n>0;n/=10)
	{
		if(i == 0)//first loop only assuming 4 digits
		{
			printed_num=x/n;
			lcd_write_data(DATA,'0' + printed_num ,u8Cpy_LCDNumber);
			i++;
		}
		
		else
		{
			printed_num=(x/n)%10;
			lcd_write_data(DATA,'0' + printed_num ,u8Cpy_LCDNumber);
			i++;
		}


		if(i==digit)
		{
			break;
		}
		
	}

		lcd_write_data(DATA,'.',HLCD_NUM0);
		
		f32number_after_printing_real_number=f32float_number-(f32)x;
		
		number_to_be_printed_with_4_digit_resolution=f32number_after_printing_real_number*(f32)(10000);
digit=4;
n=1;
for (i=0;i<(digit-1);i++)
{
	n*=10;
}

i=0;
for(n;n>0;n/=10)
{
	if(i == 0)//first loop only assuming 4 digits
	{
		printed_num=(u32)(number_to_be_printed_with_4_digit_resolution)/n;
		lcd_write_data(DATA,'0' + printed_num ,u8Cpy_LCDNumber);
		i++;
	}
	
	else
	{
		printed_num=((u32)(number_to_be_printed_with_4_digit_resolution)/n)%10;
		lcd_write_data(DATA,'0' + printed_num ,u8Cpy_LCDNumber);
		i++;
	}


	if(i==digit)
	{
		break;
	}
	
}	
	return	error;
}


tenumFncErrorState lcdclear(void)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	lcd_write_data(COMMAND,CLEAR_DISPLAY,HLCD_NUM0);
	return error;
}