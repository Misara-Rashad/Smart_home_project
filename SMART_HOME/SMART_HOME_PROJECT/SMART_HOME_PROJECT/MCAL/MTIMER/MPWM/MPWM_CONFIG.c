/*
 * MPWM_CONFIG.c
 *
 * Created: 11/03/2023 9:45:29 PM
 *  Author: Misra
 */ 




//includes section 
#include "MPWM_CONFIG.h"
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
