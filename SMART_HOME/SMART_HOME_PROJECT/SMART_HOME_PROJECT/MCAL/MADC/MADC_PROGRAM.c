/*
 * MADC_PROGRAM.c
 *
 * Created: 03/03/2023 9:47:43 PM
 *  Author: Misra
 */ 



/*.........includes section........*/
//libraries
#include "../../Libraries_/LIB_STDTypes.h"

//MCAL
#include "MADC_INTERFACE.h"


//global variables
MADC_T HADC={
	.enumchannel=MADC_CH1,
	.enumconvmode=MADC_SINGLE_CONV,
	.enumoutputmode=MADC_POLLING,
	.enumprescalar=MADC_PS128,
	.enumregister_select=MADC_RIGHT_ADJUST,
	.enumvref=MADC_AVCC
};



//functions implementation
tenumFncErrorState ADC_init(MADC_T* ptostruct)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==ptostruct)
	{
		error=LSTY_NULL_POINTER;
	}
	else
	{
		switch(ptostruct->enumvref)
		{
			case MADC_AVCC:
			SET_BIT(ADMUX,REFS0); //AVCC
			CLR_BIT(ADMUX,REFS1);
			break;
			
			case MADC_AREF:
			CLR_BIT(ADMUX,REFS0); //Aref
			CLR_BIT(ADMUX,REFS1);
			break;
			
			case MADC_INTERNALREF:
			SET_BIT(ADMUX,REFS0); //internal reference 2.56V
			SET_BIT(ADMUX,REFS1);
			break;
			
			default:
			break;
		}


		switch(ptostruct->enumregister_select)
		{
			case MADC_LEFT_ADJUST: //left adjust means store 8 bits in ADCH
			SET_BIT(ADMUX,ADLAR);
			break;
			
			case MADC_RIGHT_ADJUST: //right adjust means store 8 bits in ADCL
			CLR_BIT(ADMUX,ADLAR);
			break;
			
			default:
			break;
		}
		

		
		switch (ptostruct->enumchannel) //ADC select pin
		{
			case MADC_CH0:
			CLR_BIT(ADMUX,MUX0);
			CLR_BIT(ADMUX,MUX1);
			CLR_BIT(ADMUX,MUX2);
			CLR_BIT(ADMUX,MUX3);
			CLR_BIT(ADMUX,MUX4);
			break;
			
			case MADC_CH1:
			SET_BIT(ADMUX,MUX0);
			CLR_BIT(ADMUX,MUX1);
			CLR_BIT(ADMUX,MUX2);
			CLR_BIT(ADMUX,MUX3);
			CLR_BIT(ADMUX,MUX4);
			break;

			case MADC_CH2:
			CLR_BIT(ADMUX,MUX0);
			SET_BIT(ADMUX,MUX1);
			CLR_BIT(ADMUX,MUX2);
			CLR_BIT(ADMUX,MUX3);
			CLR_BIT(ADMUX,MUX4);
			break;

			case MADC_CH3:
			SET_BIT(ADMUX,MUX0);
			SET_BIT(ADMUX,MUX1);
			CLR_BIT(ADMUX,MUX2);
			CLR_BIT(ADMUX,MUX3);
			CLR_BIT(ADMUX,MUX4);
			break;
			
			case MADC_CH4:
			CLR_BIT(ADMUX,MUX0);
			CLR_BIT(ADMUX,MUX1);
			SET_BIT(ADMUX,MUX2);
			CLR_BIT(ADMUX,MUX3);
			CLR_BIT(ADMUX,MUX4);
			break;
			
			case MADC_CH5:
			SET_BIT(ADMUX,MUX0);
			CLR_BIT(ADMUX,MUX1);
			SET_BIT(ADMUX,MUX2);
			CLR_BIT(ADMUX,MUX3);
			CLR_BIT(ADMUX,MUX4);
			break;
			
			case MADC_CH6:
			CLR_BIT(ADMUX,MUX0);
			SET_BIT(ADMUX,MUX1);
			SET_BIT(ADMUX,MUX2);
			CLR_BIT(ADMUX,MUX3);
			CLR_BIT(ADMUX,MUX4);
			break;
			
			case MADC_CH7:
			SET_BIT(ADMUX,MUX0);
			SET_BIT(ADMUX,MUX1);
			SET_BIT(ADMUX,MUX2);
			CLR_BIT(ADMUX,MUX3);
			CLR_BIT(ADMUX,MUX4);
			break;
			
			default:
			break;
		}
		

		SET_BIT(ADCSRA,ADEN);  //ADC enabled
		
		switch(ptostruct->enumconvmode)
		{
			case MADC_SINGLE_CONV:
			CLR_BIT(ADCSRA,ADATE); //auto-triggered off
			break;
			
			case MADC_AUTO_TRIG_CONV:
			break;
			
			default:
			break;
		}
		

		
		
		switch(ptostruct->enumoutputmode)
		{
			case MADC_POLLING:
			CLR_BIT(ADCSRA,ADIE); //polling not interrupt

			break;
			
			case MADC_INTERRUPT:
			break;
			
			default:
			break;
		}
		
		
		switch(ptostruct->enumprescalar)
		{
			case MADC_PS2:
			CLR_BIT(ADCSRA,ADPS0);
			CLR_BIT(ADCSRA,ADPS1);
			CLR_BIT(ADCSRA,ADPS2);
			break;
			
			case MADC_PS4:
			CLR_BIT(ADCSRA,ADPS0);
			SET_BIT(ADCSRA,ADPS1);
			CLR_BIT(ADCSRA,ADPS2);
			break;
			
			case MADC_PS8:
			SET_BIT(ADCSRA,ADPS0);
			SET_BIT(ADCSRA,ADPS1);
			CLR_BIT(ADCSRA,ADPS2);
			break;
			
			case MADC_PS16:
			CLR_BIT(ADCSRA,ADPS0);
			CLR_BIT(ADCSRA,ADPS1);
			SET_BIT(ADCSRA,ADPS2);
			break;
			
			case MADC_PS32:
			SET_BIT(ADCSRA,ADPS0);
			CLR_BIT(ADCSRA,ADPS1);
			SET_BIT(ADCSRA,ADPS2);
			break;
			
			case MADC_PS64:
			CLR_BIT(ADCSRA,ADPS0);
			SET_BIT(ADCSRA,ADPS1);
			SET_BIT(ADCSRA,ADPS2);
			break;
			
			case MADC_PS128:
			SET_BIT(ADCSRA,ADPS0);
			SET_BIT(ADCSRA,ADPS1);
			SET_BIT(ADCSRA,ADPS2);
			break;
			
			default:
			break;
		}
		
	}
	return error;
	

}

tenumFncErrorState ADC_START_CONVERSION(void)
{
	tenumFncErrorState error= LSTY_EXECUTED_SUCCESSFULLY;
	SET_BIT(ADCSRA,ADSC);
	return error;
}


tenumFncErrorState ADC_get_analog_value(MADC_T* ptostruct,pf32 ptofloat)
{
	tenumFncErrorState error= LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==ptostruct ||NULL==ptofloat)
	{
		error=LSTY_NULL_POINTER;
	}
	else
	{
		u8 low_byte=0,high_byte=0;
		u16 ADC_result=0;
		while(!(GET_BIT(ADCSRA,ADIF)));
		switch(ptostruct->enumregister_select)
		{
			case MADC_RIGHT_ADJUST:
			low_byte=ADCL;
			high_byte=ADCH & 0x03;
			ADC_result=(high_byte<<8)|(low_byte);
			break;
			
			case MADC_LEFT_ADJUST:
			low_byte=(ADCL & 0xc0)>>6;
			high_byte=ADCH;
			ADC_result=(high_byte<<2)|(low_byte);
			break;
			
			default:
			break;
		}
		//ADC_value=(Vin/Vref)*1024
		//Vin=(Vref*ADC_value)/1024
		
		*ptofloat=((f32)5*(f32)ADC_result)/((f32)1024);
	}
	return error;
	
	
}
