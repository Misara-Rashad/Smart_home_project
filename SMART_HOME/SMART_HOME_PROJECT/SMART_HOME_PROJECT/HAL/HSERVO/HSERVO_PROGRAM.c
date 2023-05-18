/*
 * HSERVO_PROGRAM.c
 *
 * Created: 16/05/2023 12:33:26 AM
 *  Author: Misra
 */ 

//includes
#include "../../Libraries_/LIB_STDTypes.h"
#include "../../MCAL/MDIO/MDIO_INTERFACE.h"
#include "HSERVO_INTERFACE.h"


//global variables
DIO_PIN A0={
	.enumpin=MDIO_PIN0,
	.enumport=MDIO_PORTA,
	.enummode=MDIO_OUTPUT,
	.enumoutputlevel=MDIO_HIGH
};
u8 flag=0;


//functions imlementation
f32 f32initservo_HSERVO(u8 u8angle)
{
	//using timer 1
	f32 f32on_time=0;
	f32on_time=((0.0056)*(u8angle))+1;
	//how to calculate on-time for a given angle in ms
	//on-time=((1/180)*angle)+1
	//on-time=((0.00556))*angle)+1

	//ctc mode

	//SET_BIT(TCCR1B,WGM12);
	//CLR_BIT(TCCR1B,WGM13);

	//CLR_BIT(TCCR1A,WGM10);
	//CLR_BIT(TCCR1A,WGM11);

	//set prescalar 8
	//CLR_BIT(TCCR1B,CS10);
	//SET_BIT(TCCR1B,CS11);
	//CLR_BIT(TCCR1B,CS12);

	TCCR1A=0b00000000;
	TCCR1B=0b00001010;

	//make pin op high
	enumpindirection_MDIO(&A0);
	enumpinvalue_selection_MDIO(&A0,MDIO_HIGH);

	//set ocr value
	OCR1A=f32on_time/0.0005;    //tick time of 8 prescalar is 5*10power(-4)

	//enable ctc interrupt
	SET_BIT(SREG,I);
	SET_BIT(TIMSK,OCIE1A);

	return f32on_time;
}


void voidservo_start_HSERVO(f32 f32on_time)
{
	f32 f32off_time=0;
	if (0==flag)
	{
		enumpinvalue_selection_MDIO(&A0,MDIO_LOW);
		f32off_time=20-f32on_time;
		OCR1A=(f32off_time/0.0005);
		flag=1;
	}
	else if (1==flag)
	{
		enumpinvalue_selection_MDIO(&A0,MDIO_HIGH);
		OCR1A=(f32on_time/0.0005);
		flag=0;
	}
}

