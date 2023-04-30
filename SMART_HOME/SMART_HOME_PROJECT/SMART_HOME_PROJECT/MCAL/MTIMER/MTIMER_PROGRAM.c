/*
 * MTIMER_PROGRAM.c
 *
 * Created: 04/03/2023 10:21:45 PM
 *  Author: Misra
 */ 

/*...........includes section...........*/

#include <avr/interrupt.h>

//libraries
#include "../../Libraries_/LIB_STDTypes.h"




//MCAL
#include "../MDIO/MDIO_CONFIG.h"
#include "../MDIO/MDIO_INTERFACE.h"
#include "../MDIO/MDIO_REGISTERS.h"




#include "MTIMER_INTERFACE.h"




TIMER_T TIMER0_STRUCT={
	.enumstate_for_timer_or_counter=FREE,
	.enum_timer_or_counter=TIMER_MODE,
	.enummode_of_operation=NORMAL_MODE,
	.enumprescalar_values= MTIMER_PRESCALAR_1024,
	.enummode_OC=Normal_port_operation,
	.enumnumber_of_timer= timer0
};


TIMER_T TIMER1_STRUCT={
	.enumstate_for_timer_or_counter=FREE,
	.enum_timer_or_counter=TIMER_MODE,
	.enummode_of_operation=NORMAL_MODE,
	.enumprescalar_values=MTIMER_PRESCALAR_1024,
	.enummode_OC=Normal_port_operation,
	.enumnumber_of_timer= timer1
};


TIMER_T TIMER2_STRUCT={
	.enumstate_for_timer_or_counter=FREE,
	.enum_timer_or_counter=TIMER_MODE,
	.enummode_of_operation=NORMAL_MODE,
	.enumprescalar_values=MTIMER_PRESCALAR_1024,
	.enummode_OC=Normal_port_operation,
	.enumnumber_of_timer= timer2
};

DIO_PIN T0_PIN={
	.enumpin=MDIO_PIN0,
	.enumport=MDIO_PORTB,
	.enummode=MDIO_INPUT,
	.enumoutputlevel=MDIO_LOW
};


DIO_PIN T1_PIN={
	.enumpin=MDIO_PIN1,
	.enumport=MDIO_PORTB,
	.enummode=MDIO_INPUT,
	.enumoutputlevel=MDIO_LOW
};


static u16 u16counter_of_ovf_timer0=0;

//functions implementation
static void voidtimer_on(TIMER_T* ptostruct);
static void voidtimer_off(TIMER_T* ptostruct);

u16 u16get_counter0_value(void)
{
	return u16counter_of_ovf_timer0;
}


static void voidtimer_on(TIMER_T* ptostruct)
{
		SET_BIT(SREG,7);		//enable global interrupt
		switch(ptostruct->enumprescalar_values)
		{	
			case MTIMER_NO_PRESCALING:
			SET_BIT(TCCR0,CS00);
			CLR_BIT(TCCR0,CS01);
			CLR_BIT(TCCR0,CS02);
			SET_BIT(TIMSK,TOIE0);			
			break;
			
			case  MTIMER_PRESCALAR_8:
			CLR_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			CLR_BIT(TCCR0,CS02);
			SET_BIT(TIMSK,TOIE0);
			break;
			
			case MTIMER_PRESCALAR_64:
			SET_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			CLR_BIT(TCCR0,CS02);
			SET_BIT(TIMSK,TOIE0);
			break;
			
			case MTIMER_PRESCALAR_256:
			CLR_BIT(TCCR0,CS00);
			CLR_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
			SET_BIT(TIMSK,TOIE0);			
			break;
			
			case MTIMER_PRESCALAR_1024:
			SET_BIT(TCCR0,CS00);
			CLR_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
			SET_BIT(TIMSK,TOIE0);
			break;
			
			default:
			break;
			
		}
}


static void voidtimer_off(TIMER_T* ptostruct)
{
	ptostruct->enumprescalar_values= Timer_counter_stopped;
			CLR_BIT(TCCR0,CS00);
			CLR_BIT(TCCR0,CS01);
			CLR_BIT(TCCR0,CS02);
}



void voidtimerdelay_in_ms_MTIMER(u32 desired_time_in_ms,TIMER_T* ptostruct)
{
	voidtimer_on(ptostruct);
	u32 t_ovf=(u32)(((u32)1024 * (u32 )255)/((u32)16000));   //overflow time in ms
	u32 no_of_OVFS=desired_time_in_ms/t_ovf;
	u32 i=0;
	if (ptostruct->enummode_of_operation == NORMAL_MODE)
			{
					CLR_BIT(TCCR0,WGM00); //select wave generation mode
					CLR_BIT(TCCR0,WGM01);
						while (!(i == no_of_OVFS))
						{
							while (!(GET_BIT(TIFR,TOV0)));   //polling method 
							i++;
							SET_BIT(TIFR,TOV0);
						}	
			}
	voidtimer_off(ptostruct);
}

void voidtimerdelay_in_us_MTIMER(u32 desired_time_in_us,TIMER_T* ptostruct)
{
	/*voidtimer_on(ptostruct);
	u32 t_ovf=(u32)(((u32)1024 * (u32 )255)/((u32)16));   //overflow time in us
	u32 no_of_OVFS=desired_time_in_us/t_ovf;
	u32 i=0;
	if (ptostruct->enummode_of_operation == NORMAL_MODE)
	{
		CLR_BIT(TCCR0,WGM00); //select wave generation mode
		CLR_BIT(TCCR0,WGM01);
		while (!(i == no_of_OVFS))
		{
			while (!(GET_BIT(TIFR,TOV0)));   //polling method
			i++;
			SET_BIT(TIFR,TOV0);
		}
	}
	voidtimer_off(ptostruct);	*/
}



void voidtimerctc_mode_MTIMER(u32 time_to_clear_on,TIMER_T* ptostruct,u8 u8value_to_be_set_in_OCR0_register )
{
	
		voidtimer_on(ptostruct);

	if (ptostruct->enummode_of_operation == CTC_MODE)
	{	
		CLR_BIT(TCCR0,WGM00); //select wave generation mode
		SET_BIT(TCCR0,WGM01);
	
		SET_BIT(DDRB_REGISTER,3); //make OC0 output
	
		OCR0=u8value_to_be_set_in_OCR0_register;
		
		switch(ptostruct->enummode_OC)
		{
		case Normal_port_operation:
		CLR_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
		
		case Toggle_OC :
		SET_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
		
		case Clear_OC:
		CLR_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
		
		case Set_OC:
		SET_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;	
		}
		
		

	}
	
}




void voidtimer_start_timer_MTIMER(TIMER_T* ptostruct)
{
	if (ptostruct->enumstate_for_timer_or_counter == FREE)
	{
		ptostruct->enumstate_for_timer_or_counter=BUSY;
		if (ptostruct->enum_timer_or_counter == TIMER_MODE)
		{
			//here needs to be modified to serve the three timers
				TCNT0=0;
				//normal mode
				CLR_BIT(TCCR0,WGM00);
				CLR_BIT(TCCR0,WGM01);
				
			voidtimer_on(ptostruct);			
		}
	}
}


void voidtimer_end_timer_MTIMER(TIMER_T* ptostruct)
{
	//stop timer0
	voidtimer_off(ptostruct);
	ptostruct->enumstate_for_timer_or_counter= FREE;
}


void voidtimer_continue_timer_MTIMER(TIMER_T* ptostruct)
{
	if (ptostruct->enumstate_for_timer_or_counter == FREE)
	{
		ptostruct->enumstate_for_timer_or_counter= BUSY;
		voidtimer_on(ptostruct);		
	}	
}


f32  f32timer_get_timer_value_in_ms(TIMER_T* ptostruct)
{
				//here needs to be modified to serve the three timers

		f32 f32timer_tick_time_in_ms=0,f32time_in_ms=0;
		
		switch(ptostruct->enumprescalar_values)
		{
			case MTIMER_NO_PRESCALING:
			f32timer_tick_time_in_ms = (f32)( (f32)(MTIMER_NO_PRESCALING) / (f32)(16000) ) ; //   /1000 to covert to ms
			f32time_in_ms=(f32)(((f32)(TCNT0) * (f32timer_tick_time_in_ms))) ;
			f32time_in_ms=f32time_in_ms + ((f32)(u16counter_of_ovf_timer0)*(f32)(f32timer_tick_time_in_ms)*(f32)(256));
			break;
			
			case  MTIMER_PRESCALAR_8:
			f32timer_tick_time_in_ms = (f32)( (f32)(MTIMER_PRESCALAR_8) / (f32)(16000) ) ; //   /1000 to covert to ms
			f32time_in_ms=(f32)(((f32)(TCNT0) * (f32timer_tick_time_in_ms))) ;
			f32time_in_ms=f32time_in_ms + ((f32)(u16counter_of_ovf_timer0)*(f32)(f32timer_tick_time_in_ms)*(f32)(256));
			break;
			
			case MTIMER_PRESCALAR_64:
			f32timer_tick_time_in_ms = (f32)( (f32)(MTIMER_PRESCALAR_64) / (f32)(16000) ) ; //   /1000 to covert to ms
			f32time_in_ms=(f32)(((f32)(TCNT0) * (f32timer_tick_time_in_ms))) ;
			f32time_in_ms=f32time_in_ms + ((f32)(u16counter_of_ovf_timer0)*(f32)(f32timer_tick_time_in_ms)*(f32)(256));
			break;
			
			case MTIMER_PRESCALAR_256:
			f32timer_tick_time_in_ms = (f32)( (f32)(MTIMER_PRESCALAR_256) / (f32)(16000) ) ; //   /1000 to covert to ms
			f32time_in_ms=(f32)(((f32)(TCNT0) * (f32timer_tick_time_in_ms))) ;
			f32time_in_ms=f32time_in_ms + ((f32)(u16counter_of_ovf_timer0)*(f32)(f32timer_tick_time_in_ms)*(f32)(256));
			break;
						
			case MTIMER_PRESCALAR_1024:
			f32timer_tick_time_in_ms = (f32)( (f32)(MTIMER_PRESCALAR_1024) / (f32)(16000) ) ; //   /1000 to covert to ms
			f32time_in_ms=(f32)(((f32)(TCNT0) * (f32timer_tick_time_in_ms))) ;
			f32time_in_ms=f32time_in_ms + ((f32)(u16counter_of_ovf_timer0)*(f32)(f32timer_tick_time_in_ms)*(f32)(256));
			break;
			
			default:
			break;
			
		}
		
			f32timer_tick_time_in_ms = (f32)( (f32)(MTIMER_PRESCALAR_1024) / (f32)(16000) ) ; //   /1000 to covert to ms
			f32time_in_ms=(f32)(((f32)(TCNT0) * (f32timer_tick_time_in_ms))) ;
			f32time_in_ms=f32time_in_ms + ((f32)(u16counter_of_ovf_timer0)*(f32)(f32timer_tick_time_in_ms)*(f32)(256));
			return f32time_in_ms ;
}


f32  f32timer_get_timer_value_in_us(TIMER_T* ptostruct)
{
			f32 f32timer_tick_time_in_us=0,f32time_in_us=0;

			f32timer_tick_time_in_us = (f32)( (f32)(MTIMER_PRESCALAR_1024) / (f32)(16) ) ; //   
			f32time_in_us=(f32)(((f32)(TCNT0) * (f32timer_tick_time_in_us))) ;
			return f32time_in_us ;	
}





void voidcounter_start_counter_MTIMER(TIMER_T* ptostruct)
{
	if (ptostruct->enumstate_for_timer_or_counter == FREE)
	{
		ptostruct->enumstate_for_timer_or_counter= BUSY;
			if (ptostruct->enum_timer_or_counter == COUNTER_MODE)
			{
				
				enumpindirection_MDIO(&T0_PIN);   //set t0 as input 
				TCNT0=0;
				//normal mode
				CLR_BIT(TCCR0,WGM00);
				CLR_BIT(TCCR0,WGM01);
				
				switch(ptostruct->enumprescalar_values)
				{
					case MTIMER_CLOCK_ON_FALLING_EDGE:
					CLR_BIT(TCCR0,CS00);
					SET_BIT(TCCR0,CS01);
					SET_BIT(TCCR0,CS02);
					break;
					
					case MTIMER_CLOCK_ON_RISING_EDGE:
					SET_BIT(TCCR0,CS00);
					SET_BIT(TCCR0,CS01);
					SET_BIT(TCCR0,CS02);
					break;
					
					default:
					break;
				}

			}
	}

}



void voidcounter_end_counter_MTIMER(TIMER_T* ptostruct)
{
	//stop counter
	CLR_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);

	ptostruct->enumstate_for_timer_or_counter= FREE;
}


void voidcounter_continue_counter_MTIMER(TIMER_T* ptostruct)
{
	if (ptostruct->enumstate_for_timer_or_counter == FREE)
	{
		ptostruct->enumstate_for_timer_or_counter= BUSY;
		
		switch(ptostruct->enumprescalar_values)
		{
			case MTIMER_CLOCK_ON_FALLING_EDGE:
			CLR_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
			break;
			
			case MTIMER_CLOCK_ON_RISING_EDGE:
			SET_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
			break;
			
			default:
			break;
		}
		
	}
}



u32  u32counter_get_counter_value(TIMER_T* ptostruct)
{
	switch(ptostruct->enumnumber_of_timer)
	{
	case timer0:
	return TCNT0;
	break;

	case timer1:
	return TCNT1;
	break;
	
	case timer2:
	return TCNT2;
	break;	
	default:
	break;	
	}
	
	return TCNT0;
}



ISR(TIMER0_OVF_vect)
{
	u16counter_of_ovf_timer0++;	
}