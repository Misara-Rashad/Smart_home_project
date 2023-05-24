/*
 * HTEMP_SENSOR_LM35_INTERFACE.h
 *
 * Created: 23/05/2023 7:20:12 PM
 *  Author: Misra
 */ 


#ifndef HTEMP_SENSOR_LM35_INTERFACE_H_
#define HTEMP_SENSOR_LM35_INTERFACE_H_


//includes
#include "../../Libraries_/LIB_STDTypes.h"

//MADC
#include "../../MCAL/MADC/MADC_INTERFACE.h"

//functions declaration
tenumFncErrorState temp_sensor_init(MADC_T* ptostruct);
tenumFncErrorState temp_value(MADC_T* ptostruct,pf32 ptofloat);

#endif /* HTEMP_SENSOR_LM35_INTERFACE_H_ */