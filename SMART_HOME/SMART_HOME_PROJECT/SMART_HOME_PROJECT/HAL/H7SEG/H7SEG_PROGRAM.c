/*
 * H7SEG_PROGRAM.c
 *
 * Created: 21/02/2023 1:27:43 AM
 *  Author: Misra
 */ 

/*...........includes section.........*/
//libraries
#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"
#include "../../Libraries_/ATMega32_Registers.h"


//MCAL
#include "../../MCAL/MDIO/MDIO_CONFIG.h"
#include "../../MCAL/MDIO/MDIO_INTERFACE.h"
#include "../../MCAL/MDIO/MDIO_REGISTERS.h"



//HAL
#include "H7SEG_CONFIG.h"
#include "H7SEG_INTERFACE.h"




//functions implementation
void voidinit7seg_H7SEG(void)
{
	u8 i;
	for(i=0;i<NUM_OF_7SEG;i++)
	{
		enumpindirection_MDIO(&H7SEGarrayof7seg_H7SEG[i].A);
		enumpindirection_MDIO(&H7SEGarrayof7seg_H7SEG[i].B);
		enumpindirection_MDIO(&H7SEGarrayof7seg_H7SEG[i].C);
		enumpindirection_MDIO(&H7SEGarrayof7seg_H7SEG[i].D);
		enumpindirection_MDIO(&H7SEGarrayof7seg_H7SEG[i].DOT);
		enumpindirection_MDIO(&H7SEGarrayof7seg_H7SEG[i].ENABLE);
	}
}


void void7seg_enable_one_H7SEG(SSD_T* pstructcpy_pin)
{
		//enumpinvalue_MDIO(&H7SEGarrayof7seg_H7SEG[1].ENABLE);   //error due to array index
	if((pstructcpy_pin->enummode=COMMON_CATHODE))
	{
	pstructcpy_pin->ENABLE.enumoutputlevel=MDIO_HIGH;
	enumpinvalue_MDIO(&pstructcpy_pin->ENABLE);	
	}
else if((pstructcpy_pin->enummode=COMMON_ANODE)) //common_anode(+)
{
	pstructcpy_pin->ENABLE.enumoutputlevel=MDIO_LOW;
	enumpinvalue_MDIO(&pstructcpy_pin->ENABLE);	
}

}


void void7seg_disable_one_H7SEG(SSD_T* pstructcpy_pin)
{
	//pstructcpy_pin[0].ENABLE.enumoutputlevel=MDIO_LOW;
	//enumpinvalue_MDIO(&pstructcpy_pin[0].ENABLE);   //error due to array index
	if((pstructcpy_pin->enummode=COMMON_CATHODE))
	{
		pstructcpy_pin->ENABLE.enumoutputlevel=MDIO_LOW;
		enumpinvalue_MDIO(&pstructcpy_pin->ENABLE);
		//enumpinvalue_MDIO(&H7SEGarrayof7seg_H7SEG[1].ENABLE);   //error due to array index
	}
else if((pstructcpy_pin->enummode=COMMON_ANODE)) 
	{
		pstructcpy_pin->ENABLE.enumoutputlevel=MDIO_HIGH;
		enumpinvalue_MDIO(&pstructcpy_pin->ENABLE);
	}

}


void void7seg_sendnumber_H7SEG(SSD_T* pstructcpy_pin,Register regcpy_num)
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
	enumpinvalue_MDIO(&pstructcpy_pin->A);
	enumpinvalue_MDIO(&pstructcpy_pin->B);
	enumpinvalue_MDIO(&pstructcpy_pin->C);
	enumpinvalue_MDIO(&pstructcpy_pin->D);





}
