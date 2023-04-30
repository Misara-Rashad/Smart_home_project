/*
 * MADC_PROGRAM.c
 *
 * Created: 03/03/2023 9:47:43 PM
 *  Author: Misra
 */ 



/*.........includes section........*/
//libraries
#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"
#include "../../Libraries_/ATMega32_Registers.h"



//MCAL
#include "MADC_INTERFACE.h"
#include "MADC_REGISTERS.h"

void voidinitADC_MADC(void)
{
	switch(HADC.enumvref)
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


	switch(HADC.enumregister_select)
	{
		case MADC_ADCH: //left adjust means store 8 bits in ADCH
		SET_BIT(ADMUX,ADLAR);
		break;
		
		case MADC_ADCL: //right adjust means store 8 bits in ADCL
		CLR_BIT(ADMUX,ADLAR);		
		break;
		
		default:
		break;	
	}
	

	
	switch (HADC.enumchannel) //ADC select pin
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
	
	switch(HADC.enumconvmode)
	{
		case MADC_SINGLE_CONV:
		CLR_BIT(ADCSRA,ADATE); //auto-triggered off
		break;
		
		case MADC_AUTO_TRIG_CONV:
		break;
		
		default:
		break;
	}
	

	
	
	switch(HADC.enumoutputmode)
	{
		case MADC_POLLING:
	CLR_BIT(ADCSRA,ADIE); //polling not interrupt

		break;
		
		case MADC_INTERRUPT:
		break;
		
		default:
		break;
	}
	
	
	switch(HADC.enumprescalar)
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



void voidADCget_analog_value(pu8 pu8pstruct)
{
	
}
