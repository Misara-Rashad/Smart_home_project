/*
 * MADC_REGISTERS.h
 *
 * Created: 03/03/2023 9:48:42 PM
 *  Author: Misra
 */ 


#ifndef MADC_REGISTERS_H_
#define MADC_REGISTERS_H_

/*#define ADMUX 
#define ADCSRA
#define ADCH
#define ADCL
#define SFIOR*/


//ADMUX register
#define MUX0 0
#define MUX1 1
#define MUX2 2
#define MUX3 3
#define MUX4 4

#define ADLAR 5

#define REFS0 6
#define REFS1 7


//ADCSRA register
#define ADPS0 0
#define ADPS1 1
#define ADPS2 2

#define ADIE 3

#define ADIF 4

#define ADATE 5

#define ADSC 6

#define ADEN 7


//




#endif /* MADC_REGISTERS_H_ */