/*
 * HDC_MOTOR.c
 *
 * Created: 22/05/2023 9:39:21 AM
 *  Author: Misra
 */ 


//includes
#include "HDC_MOTOR_INTERFACE.h"

//global variables
MOTOR_T MOTOR1={
	{
		.enumpin=MDIO_PIN0,
		.enumport=MDIO_PORTD,
		.enummode=MDIO_OUTPUT,
		.enumoutputlevel=MDIO_HIGH
	}
	,
	{
		.enumpin=MDIO_PIN1,
		.enumport=MDIO_PORTD,
		.enummode=MDIO_OUTPUT,
		.enumoutputlevel=MDIO_HIGH
	}
	,{
		.enumpin=MDIO_PIN2,
		.enumport=MDIO_PORTD,
		.enummode=MDIO_OUTPUT,
		.enumoutputlevel=MDIO_HIGH
	}
};

//functions implementation
tenumFncErrorState Motor_init(MOTOR_T* ptomotor_structs)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==ptomotor_structs)
	{
		error=LSTY_NULL_POINTER;
	}
	else
	{
		pin_direction(&(ptomotor_structs->ENABLE));
		pin_direction(&(ptomotor_structs->IN1));
		pin_direction(&(ptomotor_structs->IN2));
	}

	return error;
}


tenumFncErrorState Motor_right(MOTOR_T* ptomotor_structs)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==ptomotor_structs)
	{
		error=LSTY_NULL_POINTER;
	}
	else
	{
		pin_value_selection(&(ptomotor_structs->ENABLE),MDIO_HIGH);
		pin_value_selection(&(ptomotor_structs->IN1),MDIO_HIGH);
		pin_value_selection(&(ptomotor_structs->IN2),MDIO_LOW);
	}

	return error;
}

tenumFncErrorState Motor_left(MOTOR_T* ptomotor_structs)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==ptomotor_structs)
	{
		error=LSTY_NULL_POINTER;
	}
	else
	{
		pin_value_selection(&(ptomotor_structs->ENABLE),MDIO_HIGH);
		pin_value_selection(&(ptomotor_structs->IN1),MDIO_LOW);
		pin_value_selection(&(ptomotor_structs->IN2),MDIO_HIGH);
	}

	return error;
}

tenumFncErrorState Motor_stop(MOTOR_T* ptomotor_structs)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==ptomotor_structs)
	{
		error=LSTY_NULL_POINTER;
	}
	else
	{
		pin_value_selection(&(ptomotor_structs->ENABLE),MDIO_LOW);
	}

	return error;
}