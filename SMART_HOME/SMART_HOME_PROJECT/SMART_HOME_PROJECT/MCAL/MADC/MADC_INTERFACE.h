/*
 * MADC_INTERFACE.h
 *
 * Created: 03/03/2023 9:49:01 PM
 *  Author: Misra
 */ 


#ifndef MADC_INTERFACE_H_
#define MADC_INTERFACE_H_


typedef enum{
	MADC_PS2=2 ,MADC_PS4=4, MADC_PS8=8, MADC_PS16=16, MADC_PS32=32, MADC_PS64=64, MADC_PS128=128
}MADC_PRESCALAR;
	
typedef enum{
	MADC_SINGLE_CONV,MADC_AUTO_TRIG_CONV
}MADC_CONVMODE;

typedef enum{
	MADC_AREF,MADC_AVCC,MADC_INTERNALREF
}MADC_VREF;

typedef enum{
	MADC_INTERRUPT,MADC_POLLING
}MADC_OUTPUTMODE;


typedef enum{
	MADC_CH0,MADC_CH1,MADC_CH2,MADC_CH3,MADC_CH4,MADC_CH5,MADC_CH6,MADC_CH7	
}MADC_CHANNEL;

typedef enum{
	MADC_ADCL,MADC_ADCH
	}MADC_REGISTER_LEFT_OR_RIGHT_ADJUST;

typedef struct  
{
	MADC_CHANNEL						enumchannel;
	MADC_CONVMODE						enumconvmode;
	MADC_OUTPUTMODE						enumoutputmode;
	MADC_PRESCALAR						enumprescalar;
	MADC_REGISTER_LEFT_OR_RIGHT_ADJUST	enumregister_select;
	MADC_VREF							enumvref;
}MADC_T;



//MADC_T HADC;


MADC_T HADC={
	.enumchannel=MADC_CH1,
	.enumconvmode=MADC_SINGLE_CONV,
	.enumoutputmode=MADC_POLLING,
	.enumprescalar=MADC_PS128,
	.enumregister_select=MADC_ADCH,
	.enumvref=MADC_AVCC
	};










//functions prototype
void voidinitADC_MADC(void);
void voidADCget_analog_value(pu8 pu8pstruct);


#endif /* MADC_INTERFACE_H_ */