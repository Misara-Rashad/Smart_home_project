/*
 * MTIMER_INTERFACE.h
 *
 * Created: 04/03/2023 10:22:44 PM
 *  Author: Misra
 */ 


#ifndef MTIMER_INTERFACE_H_
#define MTIMER_INTERFACE_H_

#include "MTIMER_REGISTERS.h"
#include "MTIMER_CONFIG.h"

//modes of operation 
/*#define normal 0 //overflow mode 
#define normal_polling_method 1
#define normal_interrupt_method 2
#define ctc    2 //clear time on compare match


//prescalar options for timer  
#define Timer_counter_stopped   0
#define MTIMER_PRESCALAR_8       1
#define MTIMER_PRESCALAR_64      2
#define MTIMER_PRESCALAR_256     3
#define MTIMER_PRESCALAR_1024    4*/


typedef enum{
	Timer_counter_stopped=0,MTIMER_NO_PRESCALING=1,MTIMER_PRESCALAR_8=8,MTIMER_PRESCALAR_64=64,MTIMER_PRESCALAR_256=256,MTIMER_PRESCALAR_1024=1024,MTIMER_CLOCK_ON_FALLING_EDGE=1050,MTIMER_CLOCK_ON_RISING_EDGE=1200
	}PRESCALAR_VALUES;


typedef enum {
	NORMAL_MODE,CTC_MODE
}MODES_OF_OPERATION;

typedef enum{
	Normal_port_operation,Toggle_OC,Clear_OC,Set_OC
}MODES_OF_OC_PIN;


typedef enum{
	COUNTER_MODE,TIMER_MODE
}MODES_OF_TIMER_OR_COUNTER;
		

typedef enum{
	FREE,BUSY
}STATE_FOR_TIMER_OR_COUNTER;
	
typedef enum
{
timer0,timer1,timer2	
}TIMER_NUM;

typedef struct {
	STATE_FOR_TIMER_OR_COUNTER enumstate_for_timer_or_counter;
	MODES_OF_TIMER_OR_COUNTER enum_timer_or_counter;
	MODES_OF_OPERATION enummode_of_operation;
	PRESCALAR_VALUES enumprescalar_values;
	MODES_OF_OC_PIN enummode_OC;
	TIMER_NUM enumnumber_of_timer;
}TIMER_T;



TIMER_T TIMER0_STRUCT;
TIMER_T TIMER1_STRUCT;
TIMER_T TIMER2_STRUCT;



//functions prototype

tenumFncErrorState timerdelay_in_millisec(u32 desired_time_in_ms,TIMER_T* ptostruct);
tenumFncErrorState timerdelay_in_microsec(u32 desired_time_in_us,TIMER_T* ptostruct);
tenumFncErrorState timerctc_mode(u32 time_to_clear_on,TIMER_T* ptostruct,u8 u8value_to_be_set_in_OCR0_register );

tenumFncErrorState timer_start_timer(TIMER_T* ptostruct);
tenumFncErrorState timer_end_timer(TIMER_T* ptostruct);
tenumFncErrorState timer_continue_timer(TIMER_T* ptostruct);
tenumFncErrorState timer_get_timer_value_in_millisec(TIMER_T* ptostruct,pf32 pf32_variable);
tenumFncErrorState timer_get_timer_value_in_microsec(TIMER_T* ptostruct,pf32 pf32_variable);

tenumFncErrorState counter_start_counter(TIMER_T* ptostruct);
tenumFncErrorState counter_end_counter(TIMER_T* ptostruct);
tenumFncErrorState counter_continue_counter(TIMER_T* ptostruct);
tenumFncErrorState counter_get_counter_value(TIMER_T* ptostruct,pu32 pu32variable);

tenumFncErrorState timer1_ctc_interrupt_call_back(void (*ptr) (f32));



#endif /* MTIMER_INTERFACE_H_ */