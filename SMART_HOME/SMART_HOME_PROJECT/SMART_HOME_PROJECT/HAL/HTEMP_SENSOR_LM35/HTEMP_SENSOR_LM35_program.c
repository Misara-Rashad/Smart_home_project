/*
 * HTEMP_SENSOR_LM35_program.c
 *
 * Created: 23/05/2023 7:19:48 PM
 *  Author: Misra
 */ 

#include "HTEMP_SENSOR_LM35_INTERFACE.h"

MADC_T HTEMP_SENSOR={
	.enumchannel=MADC_CH1,
	.enumconvmode=MADC_SINGLE_CONV,
	.enumoutputmode=MADC_POLLING,
	.enumprescalar=MADC_PS128,
	.enumregister_select=MADC_LEFT_ADJUST,
	.enumvref=MADC_AVCC
};


//functions implementation
tenumFncErrorState temp_sensor_init(MADC_T* ptostruct)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY ;
	error=ADC_init(ptostruct);
	return error;
}

tenumFncErrorState temp_value(MADC_T* ptostruct,pf32 ptofloat)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	error=ADC_START_CONVERSION();
	error=ADC_get_analog_value(ptostruct,ptofloat);
	//precision is 1mv for each 1 degree celsius
	*ptofloat=(*ptofloat)/(f32)(0.01);
	return error;			
}

