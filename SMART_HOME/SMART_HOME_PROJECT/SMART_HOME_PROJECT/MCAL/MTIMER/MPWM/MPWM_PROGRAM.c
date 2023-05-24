/*
 * MPWM_PROGRAM.c
 *
 * Created: 11/03/2023 9:32:16 PM
 *  Author: Misra
 */ 


//includes section
//libraries
#include "../../../Libraries_/LIB_STDTypes.h"


//MDIO
#include "../../MDIO/MDIO_INTERFACE.h"


#include "MPWM_INTERFACE.h"

MPWM_T HPWM_arrayofpwm[3]={
	[MPWM_NUM_0]={
		.enumpwm_num=MPWM_NUM0,
		.enumpwm_mode=MPWM_FASTPWM,
		.enumpwm_op_format=MPWM_INVERTED,
		.enumstate_of_timer=MPWM_FREE,
		.u8output_compare_unit=128
		
	},
	[MPWM_NUM_1]={
		.enumpwm_num=MPWM_NUM1,
		.enumpwm_mode=MPWM_FASTPWM,
		.enumpwm_op_format=MPWM_INVERTED,
		.enumstate_of_timer=MPWM_FREE,
		.u8output_compare_unit=128,
		.enumno_of_bits=EIGHT_BIT

	},
	[MPWM_NUM_2]={
		.enumpwm_num=MPWM_NUM2,
		.enumpwm_mode=MPWM_FASTPWM,
		.enumpwm_op_format=MPWM_INVERTED,
		.enumstate_of_timer=MPWM_FREE,
		.u8output_compare_unit=128
	}
};

//OC0
DIO_PIN OC0_PIN={
	.enumpin=MDIO_PIN3,
	.enumport=MDIO_PORTB,
	.enummode=MDIO_OUTPUT,
	.enumoutputlevel=MDIO_LOW
	
};


//OC1A
DIO_PIN OC1A_PIN={
	.enumpin=MDIO_PIN5,
	.enumport=MDIO_PORTD,
	.enummode=MDIO_OUTPUT,
	.enumoutputlevel=MDIO_LOW
	
};




//OC1B
DIO_PIN OC1B_PIN={
	.enumpin=MDIO_PIN4,
	.enumport=MDIO_PORTD,
	.enummode=MDIO_OUTPUT,
	.enumoutputlevel=MDIO_LOW
	
};

//OC2
DIO_PIN OC2_PIN={
			.enumpin=MDIO_PIN7,
			.enumport=MDIO_PORTD,
			.enummode=MDIO_OUTPUT,
			.enumoutputlevel=MDIO_LOW
	
};







tenumFncErrorState PWM_init_MPWM(MPWM_T* ptostruct)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==ptostruct)
	{
		error=LSTY_NULL_POINTER;
	}
	else
	{
			switch(ptostruct->enumpwm_num)
			{
				case MPWM_NUM0:
				if (ptostruct->enumstate_of_timer == MPWM_FREE)
				{
					ptostruct->enumstate_of_timer = MPWM_BUSY;
					
					SET_BIT(TCCR0,CS00);       //set 1024 prescalar
					CLR_BIT(TCCR0,CS01);
					SET_BIT(TCCR0,CS02);
					
					
					enumpindirection_MDIO(&OC0_PIN);  //make OC0 OUTPUT
					
					
					CLR_BIT(TCCR0,FOC0);
					OCR0=(ptostruct->u8output_compare_unit);
					if (ptostruct->enumpwm_mode == MPWM_PHASECORRECT)
					{
						SET_BIT(TCCR0,WGM00);
						CLR_BIT(TCCR0,WGM01);
						
						switch(ptostruct->enumpwm_op_format)
						{
							case MPWM_NON_INVERTED:
							CLR_BIT(TCCR0,COM00);
							SET_BIT(TCCR0,COM01);
							break;
							
							case MPWM_INVERTED:
							SET_BIT(TCCR0,COM00);
							SET_BIT(TCCR0,COM01);
							break;
							
							default:
							break;
						}
					}
					else if (ptostruct->enumpwm_mode == MPWM_FASTPWM)
					{
						SET_BIT(TCCR0,WGM00);
						SET_BIT(TCCR0,WGM01);
						
						switch(ptostruct->enumpwm_op_format)
						{
							case MPWM_NON_INVERTED:
							CLR_BIT(TCCR0,COM00);
							SET_BIT(TCCR0,COM01);
							break;
							
							case MPWM_INVERTED:
							SET_BIT(TCCR0,COM00);
							SET_BIT(TCCR0,COM01);
							break;
							
							default:
							break;
						}
					}
				}
				break;
				
				case MPWM_NUM1:
				if (ptostruct->enumstate_of_timer == MPWM_FREE)
				{
					ptostruct->enumstate_of_timer = MPWM_BUSY;
					
					SET_BIT(TCCR1B,CS10);       //set 1024 prescalar
					CLR_BIT(TCCR1B,CS11);
					SET_BIT(TCCR1B,CS12);
					
					
					enumpindirection_MDIO(&OC1A_PIN);  //make OC1A OUTPUT
					enumpindirection_MDIO(&OC1B_PIN);  //make OC1B OUTPUT
					
					CLR_BIT(TCCR1A,FOC1A);
					CLR_BIT(TCCR1A,FOC1B);

					OCR1AH=0;
					OCR1AL=(ptostruct->u8output_compare_unit);
					
					OCR1BH=0;
					OCR1BL=(ptostruct->u8output_compare_unit);

					if (ptostruct->enumpwm_mode == MPWM_PHASECORRECT)
					{
						
						switch(ptostruct->enumno_of_bits)
						{
							case EIGHT_BIT:   //mode1  0001
							
							CLR_BIT(TCCR1B,WGM13);
							CLR_BIT(TCCR1B,WGM12);
							
							CLR_BIT(TCCR1A,WGM11);
							SET_BIT(TCCR1A,WGM10);
							
							//selected o/p form such as inverted or non inverted
							switch(ptostruct->enumpwm_op_format)
							{
								case MPWM_NON_INVERTED:
								SET_BIT(TCCR1A,COM1A1);
								CLR_BIT(TCCR1A,COM1A0);
								
								SET_BIT(TCCR1A,COM1B1);
								CLR_BIT(TCCR1A,COM1B0);
								break;
								
								case MPWM_INVERTED:
								SET_BIT(TCCR1A,COM1A1);
								SET_BIT(TCCR1A,COM1A0);
								
								SET_BIT(TCCR1A,COM1B1);
								SET_BIT(TCCR1A,COM1B0);
								break;
								
								default:
								break;
							}
							break;
							
							case NINE_BIT:   //mode2  0010
							CLR_BIT(TCCR1B,WGM13);
							CLR_BIT(TCCR1B,WGM12);
							
							SET_BIT(TCCR1A,WGM11);
							CLR_BIT(TCCR1A,WGM10);
							//selected o/p form such as inverted or non inverted
							switch(ptostruct->enumpwm_op_format)
							{
								case MPWM_NON_INVERTED:
								SET_BIT(TCCR1A,COM1A1);
								CLR_BIT(TCCR1A,COM1A0);
								
								SET_BIT(TCCR1A,COM1B1);
								CLR_BIT(TCCR1A,COM1B0);
								break;
								
								case MPWM_INVERTED:
								SET_BIT(TCCR1A,COM1A1);
								SET_BIT(TCCR1A,COM1A0);
								
								SET_BIT(TCCR1A,COM1B1);
								SET_BIT(TCCR1A,COM1B0);
								break;
								
								default:
								break;
							}
							break;
							
							case TEN_BIT:   //mode3  0011
							CLR_BIT(TCCR1B,WGM13);
							CLR_BIT(TCCR1B,WGM12);
							
							SET_BIT(TCCR1A,WGM11);
							SET_BIT(TCCR1A,WGM10);
							//selected o/p form such as inverted or non inverted
							switch(ptostruct->enumpwm_op_format)
							{
								case MPWM_NON_INVERTED:
								SET_BIT(TCCR1A,COM1A1);
								CLR_BIT(TCCR1A,COM1A0);
								
								SET_BIT(TCCR1A,COM1B1);
								CLR_BIT(TCCR1A,COM1B0);
								break;
								
								case MPWM_INVERTED:
								SET_BIT(TCCR1A,COM1A1);
								SET_BIT(TCCR1A,COM1A0);
								
								SET_BIT(TCCR1A,COM1B1);
								SET_BIT(TCCR1A,COM1B0);
								break;
								
								default:
								break;
							}
							break;
						}

						

					}
					else if (ptostruct->enumpwm_mode == MPWM_FASTPWM)
					{
						
						switch(ptostruct->enumno_of_bits)
						{
							case EIGHT_BIT:   //mode5  0101
							
							CLR_BIT(TCCR1B,WGM13);
							SET_BIT(TCCR1B,WGM12);
							
							CLR_BIT(TCCR1A,WGM11);
							SET_BIT(TCCR1A,WGM10);
							
							//selected o/p form such as inverted or non inverted
							switch(ptostruct->enumpwm_op_format)
							{
								case MPWM_NON_INVERTED:
								SET_BIT(TCCR1A,COM1A1);
								CLR_BIT(TCCR1A,COM1A0);
								
								SET_BIT(TCCR1A,COM1B1);
								CLR_BIT(TCCR1A,COM1B0);
								break;
								
								case MPWM_INVERTED:
								SET_BIT(TCCR1A,COM1A1);
								SET_BIT(TCCR1A,COM1A0);
								
								SET_BIT(TCCR1A,COM1B1);
								SET_BIT(TCCR1A,COM1B0);
								break;
								
								default:
								break;
							}
							break;
							
							case NINE_BIT:   //mode6  0110
							CLR_BIT(TCCR1B,WGM13);
							SET_BIT(TCCR1B,WGM12);
							
							SET_BIT(TCCR1A,WGM11);
							CLR_BIT(TCCR1A,WGM10);
							//selected o/p form such as inverted or non inverted
							switch(ptostruct->enumpwm_op_format)
							{
								case MPWM_NON_INVERTED:
								SET_BIT(TCCR1A,COM1A1);
								CLR_BIT(TCCR1A,COM1A0);
								
								SET_BIT(TCCR1A,COM1B1);
								CLR_BIT(TCCR1A,COM1B0);
								break;
								
								case MPWM_INVERTED:
								SET_BIT(TCCR1A,COM1A1);
								SET_BIT(TCCR1A,COM1A0);
								
								SET_BIT(TCCR1A,COM1B1);
								SET_BIT(TCCR1A,COM1B0);
								break;
								
								default:
								break;
							}
							break;
							
							case TEN_BIT:   //mode7  0011
							CLR_BIT(TCCR1B,WGM13);
							SET_BIT(TCCR1B,WGM12);
							
							SET_BIT(TCCR1A,WGM11);
							SET_BIT(TCCR1A,WGM10);
							//selected o/p form such as inverted or non inverted
							switch(ptostruct->enumpwm_op_format)
							{
								case MPWM_NON_INVERTED:
								SET_BIT(TCCR1A,COM1A1);
								CLR_BIT(TCCR1A,COM1A0);
								
								SET_BIT(TCCR1A,COM1B1);
								CLR_BIT(TCCR1A,COM1B0);
								break;
								
								case MPWM_INVERTED:
								SET_BIT(TCCR1A,COM1A1);
								SET_BIT(TCCR1A,COM1A0);
								
								SET_BIT(TCCR1A,COM1B1);
								SET_BIT(TCCR1A,COM1B0);
								break;
								
								default:
								break;
							}
							break;
						}

						

					}
				}
				break;
				
				case MPWM_NUM2:
				if (ptostruct->enumstate_of_timer == MPWM_FREE)
				{
					
					ptostruct->enumstate_of_timer = MPWM_BUSY;

					SET_BIT(TCCR2,CS20);       //set 1024 prescalar
					SET_BIT(TCCR2,CS21);
					SET_BIT(TCCR2,CS22);
					
					
					enumpindirection_MDIO(&OC2_PIN);  //make OC2 OUTPUT
					
					
					CLR_BIT(TCCR2,FOC2);
					OCR2=(ptostruct->u8output_compare_unit);
					if (ptostruct->enumpwm_mode == MPWM_PHASECORRECT)
					{
						SET_BIT(TCCR2,WGM20);
						CLR_BIT(TCCR2,WGM21);
						
						switch(ptostruct->enumpwm_op_format)
						{
							case MPWM_NON_INVERTED:
							CLR_BIT(TCCR2,COM20);
							SET_BIT(TCCR2,COM21);
							break;
							
							case MPWM_INVERTED:
							SET_BIT(TCCR2,COM20);
							SET_BIT(TCCR2,COM21);
							break;
							
							default:
							break;
						}
					}
					else if (ptostruct->enumpwm_mode == MPWM_FASTPWM)
					{
						SET_BIT(TCCR2,WGM20);
						SET_BIT(TCCR2,WGM21);
						
						switch(ptostruct->enumpwm_op_format)
						{
							case MPWM_NON_INVERTED:
							CLR_BIT(TCCR2,COM20);
							SET_BIT(TCCR2,COM21);
							break;
							
							case MPWM_INVERTED:
							SET_BIT(TCCR2,COM20);
							SET_BIT(TCCR2,COM21);
							break;
							
							default:
							break;
						}
					}
				}
				break;
				
				default:
				break;
			}
			
		}
		return  error;	
	}



tenumFncErrorState pwm_change_duty_cycle_MPWM(u8 u8cpy_value_to_OCRn,MPWM_T* ptostruct)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==ptostruct)
	{
		error=LSTY_NULL_POINTER;
	}
	else
	{
			switch(ptostruct->enumpwm_num)
			{
				case MPWM_NUM0:
				OCR0=u8cpy_value_to_OCRn;
				break;

				case MPWM_NUM1:
				OCR1AH=0;
				OCR1AL=u8cpy_value_to_OCRn;
				
				OCR1BH=0;
				OCR1BL=u8cpy_value_to_OCRn;


				break;
				
				case MPWM_NUM2:
				OCR2=u8cpy_value_to_OCRn;
				break;
				
				
				default:
				break;
			}
	}
	return error;

}



tenumFncErrorState pwm_disable_MPWM(MPWM_T* ptostruct)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==ptostruct)
	{
		error=LSTY_NULL_POINTER;
	}
	else
	{
		switch(ptostruct->enumpwm_num)
		{
			case MPWM_NUM0:
			CLR_BIT(TCCR0,CS00);
			CLR_BIT(TCCR0,CS01);
			CLR_BIT(TCCR0,CS02);
			
			ptostruct->enumstate_of_timer = MPWM_FREE;
			break;

			case MPWM_NUM1:
			//OCR0=u8cpy_value_to_OCRn;
			ptostruct->enumstate_of_timer = MPWM_FREE;

			break;
			
			case MPWM_NUM2:
			CLR_BIT(TCCR2,CS20);
			CLR_BIT(TCCR2,CS21);
			CLR_BIT(TCCR2,CS22);
			
			ptostruct->enumstate_of_timer = MPWM_FREE;
			break;
			
			
			default:
			break;
		}	
	}
	return error;

}
