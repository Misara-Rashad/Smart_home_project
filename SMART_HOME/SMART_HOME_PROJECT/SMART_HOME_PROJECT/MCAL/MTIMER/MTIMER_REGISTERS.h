/*
 * MTIMER_REGISTERS.h
 *
 * Created: 04/03/2023 10:25:40 PM
 *  Author: Misra
 */ 


#ifndef MTIMER_REGISTERS_H_
#define MTIMER_REGISTERS_H_


/* Timer 0 */
#define   TCNT0        (*((volatile u8*)0x52))
#define   TCCR0        (*((volatile u8*)0x53))

#define   MCUSR        (*((volatile u8*)0x54))
#define   MCUCSR       MCUSR
#define   MCUCR        (*((volatile u8*)0x55))

#define   TWCR         (*((volatile u8*)0x56))

#define   SPMCR        (*((volatile u8*)0x57))

#define   TIFR         (*((volatile u8*)0x58))
#define   TIMSK        (*((volatile u8*)0x59))

#define   GIFR         (*((volatile u8*)0x5A))
#define   GIMSK        (*((volatile u8*)0x5B))
#define   GICR         GIMSK

#define   OCR0         (*((volatile u8*)0x5C))

#define   SPL          (*((volatile u8*)0x5D))
#define   SPH          (*((volatile u8*)0x5E))

#define   SREG         (*((volatile u8*)0x5F))

/* Timer 2 */
#define   OCR2         (*((volatile u8*)0x43))
#define   TCNT2        (*((volatile u8*)0x44))
#define   TCCR2        (*((volatile u8*)0x45))

/* Timer 1 */
#define   ICR1         (*((volatile u16*)0x46))
#define   ICR1L        (*((volatile u8*)0x46))
#define   ICR1H        (*((volatile u8*)0x47))
#define   OCR1B        (*((volatile u16*)0x48))
#define   OCR1BL       (*((volatile u8*)0x48))
#define   OCR1BH       (*((volatile u8*)0x49))
#define   OCR1A        (*((volatile u16*)0x4A))
#define   OCR1AL       (*((volatile u8*)0x4A))
#define   OCR1AH       (*((volatile u8*)0x4B))
#define   TCNT1        (*((volatile u16*)0x4C))
#define   TCNT1L       (*((volatile u8*)0x4C))
#define   TCNT1H       (*((volatile u8*)0x4D))
#define   TCCR1B       (*((volatile u8*)0x4E))
#define   TCCR1A       (*((volatile u8*)0x4F))

#define   SFIOR        (*((volatile u8*)0x50))

#define   OSCCAL       (*((volatile u8*)0x51))
#define   OCDR         OSCCAL





/* TIMSK */
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0


/* TIFR */
#define OCF2    7
#define TOV2    6
#define ICF1    5
#define OCF1A   4
#define OCF1B   3
#define TOV1    2
#define OCF0    1
#define TOV0    0


/* TCCR0 */
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0




#endif /* MTIMER_REGISTERS_H_ */