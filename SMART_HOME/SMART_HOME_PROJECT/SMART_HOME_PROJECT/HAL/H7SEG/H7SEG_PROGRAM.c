/*
 * H7SEG_PROGRAM.c
 *
 * Created: 21/02/2023 1:27:43 AM
 *  Author: Misra
 */ 

/*...........includes section.........*/
//libraries
#include "../../Libraries_/LIB_STDTypes.h"

//MCAL
#include "../../MCAL/MDIO/MDIO_INTERFACE.h"

//HAL
#include "H7SEG_INTERFACE.h"




//functions implementation
tenumFncErrorState seven_segment_init(void)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	u8 i;
	for(i=0;i<NUM_OF_7SEG;i++)
	{
		pin_direction(&H7SEGarrayof7seg_H7SEG[i].A);
		pin_direction(&H7SEGarrayof7seg_H7SEG[i].B);
		pin_direction(&H7SEGarrayof7seg_H7SEG[i].C);
		pin_direction(&H7SEGarrayof7seg_H7SEG[i].D);
		pin_direction(&H7SEGarrayof7seg_H7SEG[i].DOT);
		pin_direction(&H7SEGarrayof7seg_H7SEG[i].ENABLE);
	}
	return error;
}


tenumFncErrorState seven_segment_enable_one(SSD_T* pstructcpy_pin)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==pstructcpy_pin)
	{
		error=LSTY_NULL_POINTER;
	}
	else
	{
	//enumpinvalue_MDIO(&H7SEGarrayof7seg_H7SEG[1].ENABLE);   //error due to array index
	if((pstructcpy_pin->enummode=COMMON_CATHODE))
	{
		pstructcpy_pin->ENABLE.enumoutputlevel=MDIO_HIGH;
		pin_value(&pstructcpy_pin->ENABLE);
	}
	else if((pstructcpy_pin->enummode=COMMON_ANODE)) //common_anode(+)
	{
		pstructcpy_pin->ENABLE.enumoutputlevel=MDIO_LOW;
		pin_value(&pstructcpy_pin->ENABLE);
	}	
	}
	return error;
	

}


tenumFncErrorState seven_segment_disable_one(SSD_T* pstructcpy_pin)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==pstructcpy_pin)
	{
		error=LSTY_NULL_POINTER;
	}
	else
	{
		//pstructcpy_pin[0].ENABLE.enumoutputlevel=MDIO_LOW;
		//enumpinvalue_MDIO(&pstructcpy_pin[0].ENABLE);   //error due to array index
		if((pstructcpy_pin->enummode=COMMON_CATHODE))
		{
			pstructcpy_pin->ENABLE.enumoutputlevel=MDIO_LOW;
			pin_value(&pstructcpy_pin->ENABLE);
			//enumpinvalue_MDIO(&H7SEGarrayof7seg_H7SEG[1].ENABLE);   //error due to array index
		}
		else if((pstructcpy_pin->enummode=COMMON_ANODE))
		{
			pstructcpy_pin->ENABLE.enumoutputlevel=MDIO_HIGH;
			pin_value(&pstructcpy_pin->ENABLE);
		}

	}
	return error;
	
}


tenumFncErrorState seven_segment_sendnumber(SSD_T* pstructcpy_pin,Register regcpy_num)
{
	tenumFncErrorState error=LSTY_EXECUTED_SUCCESSFULLY;
	if (NULL==pstructcpy_pin)
	{
		error=LSTY_NULL_POINTER;
	}
	else
	{
		if(pstructcpy_pin->enummode==COMMON_CATHODE)
		{
			
			pstructcpy_pin->A.enumoutputlevel= regcpy_num.Bit.B0;
			pstructcpy_pin->B.enumoutputlevel= regcpy_num.Bit.B1;
			pstructcpy_pin->C.enumoutputlevel= regcpy_num.Bit.B2;
			pstructcpy_pin->D.enumoutputlevel= regcpy_num.Bit.B3;


		}
		else if((pstructcpy_pin->enummode=COMMON_ANODE))
		{
			pstructcpy_pin->A.enumoutputlevel= ~regcpy_num.Bit.B0;
			pstructcpy_pin->B.enumoutputlevel= ~regcpy_num.Bit.B1;
			pstructcpy_pin->C.enumoutputlevel= ~regcpy_num.Bit.B2;
			pstructcpy_pin->D.enumoutputlevel= ~regcpy_num.Bit.B3;
			

		}
		pin_value(&pstructcpy_pin->A);
		pin_value(&pstructcpy_pin->B);
		pin_value(&pstructcpy_pin->C);
		pin_value(&pstructcpy_pin->D);





	}
	return error;

}
