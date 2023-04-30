/*
 * HLCD_INTERFACE.h
 *
 * Created: 21/02/2023 11:13:18 PM
 *  Author: Misra
 */ 


#ifndef HLCD_INTERFACE_H_
#define HLCD_INTERFACE_H_

//includes
#include "../../Libraries_/LIB_STDTypes.h"

#include "HLCD_CONFIG.h"

//comands for lcd
//8 bit mode only
#define FUNCTION_SET                     ((u8)0b00111000) 





//4 bit mode and 8 bit mode
#define LCD_4BitMode1			         ((u8)0x33)       
#define LCD_4BitMode2			         ((u8)0x32)       
#define LCD_2Lines5X8_4BitMode		     ((u8)0x28) 
#define CLEAR_DISPLAY                    ((u8)0b00000001)
#define RETURN_HOME                      ((u8)0b00000010)
#define ENTERY_MODE                      ((u8)0b00000111) // id increases DDRAM address by 1 and sh shifts to left
#define DISPLAY_ON_CURSOR_ON_BLINK_ON    ((u8)0b00001111)
#define CURSOR_OR_DISPLAY_SHIFT          ((u8)0b00010000)    
#define DISPLAY_ON_WITH_CURSOR  	((u8)0b00001110)


typedef enum{
	COMMAND,DATA
}HLCD_DATA_TYPE;

typedef enum{
	four_BIT_MODE,EIGHT_BIT_MODE
	}MODES_OF_LCD;

typedef struct
{
	
DIO_PIN D0;
DIO_PIN D1;
DIO_PIN D2;
DIO_PIN D3;
	
DIO_PIN D4;
DIO_PIN D5;
DIO_PIN D6;
DIO_PIN D7;

DIO_PIN RS;
DIO_PIN RW;
DIO_PIN ENABLE;

MODES_OF_LCD enummode;	
}LCD_T;

LCD_T HLCD_arrayoflcds[NUM_OF_LCDS];

//functions prototype
void voidinitlcd_HLCD(void);
void voidLCDwrite_data_HLCD(HLCD_DATA_TYPE enumcpy_data_type,u8 u8Cpy_LCDData, u8 u8Cpy_LCDNumber);
void voidLCDintegartostring_HLCD(u32 u32cpu_integar,  u8 u8Cpy_LCDNumber);
void voidLCDstring_HLCD(u8 u8array_of_char[],u8 u8array_size,u8 u8Cpy_LCDNumber);
void voidlcdfloat_number_HLCD(f32 f32float_number,u8 u8Cpy_LCDNumber);
void voidlcdclear(void);
#endif /* HLCD_INTERFACE_H_ */