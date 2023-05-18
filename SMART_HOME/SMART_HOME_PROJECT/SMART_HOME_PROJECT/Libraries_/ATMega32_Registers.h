#ifndef ATMega32_Features_h
#define ATMega32_Features_h

/* ADC */
#define   ADCW         (*((volatile u16*)0x24))
#define   ADCL         (*((volatile u8*)0x24))
#define   ADCH         (*((volatile u8*)0x25))
#define   ADCSRA       (*((volatile u8*)0x26))
#define   ADMUX        (*((volatile u8*)0x27))

/* I/O Registers */
#define   TWBR         (*((volatile u8*)0x20))
#define   TWSR         (*((volatile u8*)0x21))
#define   TWAR         (*((volatile u8*)0x22))
#define   TWDR         (*((volatile u8*)0x23))

/* Analog Comparator */
#define   ACSR         (*((volatile u8*)0x28))

/* USART */
#define   UBRRL        (*((volatile u8*)0x29))
#define   UCSRB        (*((volatile u8*)0x2A))
#define   UCSRA        (*((volatile u8*)0x2B))
#define   UDR          (*((volatile u8*)0x2C))

/* SPI */
#define   SPCR         (*((volatile u8*)0x2D))
#define   SPSR         (*((volatile u8*)0x2E))
#define   SPDR         (*((volatile u8*)0x2F))

/* EEPROM Control Register */
#define   EECR         (*((volatile u8*)0x3C))

/* EEPROM Data Register */
#define   EEDR         (*((volatile u8*)0x3D))

/* EEPROM Address Register */
#define   EEAR         (*((volatile u16*)0x3E))
#define   EEARL        (*((volatile u8*)0x3E))
#define   EEARH        (*((volatile u8*)0x3F))

#define   UBRRH        (*((volatile u8*)0x40))
#define   UCSRC        UBRRH

#define   WDTCR        (*((volatile u8*)0x41))

#define   ASSR         (*((volatile u8*)0x42))

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

/* Timer 0 */
#define   TCNT0        (*((volatile u8*)0x52))
#define   TCCR0        (*((volatile u8*)0x53))

#define   MCUSR        (*((volatile u8*)0x54))
//#define   MCUCSR       MCUSR
#define   MCUCR        (*((volatile u8*)0x55))

#define   TWCR         (*((volatile u8*)0x56))

#define   SPMCR        (*((volatile u8*)0x57))

#define   TIFR         (*((volatile u8*)0x58))
#define   TIMSK        (*((volatile u8*)0x59))

//#define   GIFR         (*((volatile u8*)0x5A))
#define   GIMSK        (*((volatile u8*)0x5B))
//#define   GICR         GIMSK

#define   OCR0         (*((volatile u8*)0x5C))

#define   SPL          (*((volatile u8*)0x5D))
#define   SPH          (*((volatile u8*)0x5E))

#define   SREG         (*((volatile u8*)0x5F))


/* Interrupt vectors */

#define _VECTOR(N) __vector_ ## N

/* External Interrupt Request 0 */
#define INT0_vect			_VECTOR(1)

/* External Interrupt Request 1 */
#define INT1_vect			_VECTOR(2)

/* External Interrupt Request 2 */
#define INT2_vect			_VECTOR(3)

/* Timer/Counter2 Compare Match */
#define TIMER2_COMP_vect		_VECTOR(4)

/* Timer/Counter2 Overflow */
#define TIMER2_OVF_vect			_VECTOR(5)

/* Timer/Counter1 Capture Event */
#define TIMER1_CAPT_vect		_VECTOR(6)

/* Timer/Counter1 Compare Match A */
#define TIMER1_COMPA_vect		_VECTOR(7)

/* Timer/Counter1 Compare Match B */
#define TIMER1_COMPB_vect		_VECTOR(8)

/* Timer/Counter1 Overflow */
#define TIMER1_OVF_vect			_VECTOR(9)

/* Timer/Counter0 Compare Match */
#define TIMER0_COMP_vect		_VECTOR(10)

/* Timer/Counter0 Overflow */
#define TIMER0_OVF_vect			_VECTOR(11)

/* Serial Transfer Complete */
#define SPI_STC_vect			_VECTOR(12)

/* USART, Rx Complete */
#define USART_RXC_vect			_VECTOR(13)

/* USART Data Register Empty */
#define USART_UDRE_vect			_VECTOR(14)

/* USART, Tx Complete */
#define USART_TXC_vect			_VECTOR(15)

/* ADC Conversion Complete */
#define ADC_vect			_VECTOR(16)

/* EEPROM Ready */
#define EE_RDY_vect			_VECTOR(17)

/* Analog Comparator */
#define ANA_COMP_vect			_VECTOR(18)

/* 2-wire Serial Interface */
#define TWI_vect			_VECTOR(19)

/* Store Program Memory Ready */
#define SPM_RDY_vect			_VECTOR(20)


/* Bit numbers */

/* SREG */
#define I		7  //global interrupt enable

/* GICR */
#define INT1    7
#define INT0    6
#define INT2    5
#define IVSEL   1
#define IVCE    0

/* GICR */
#define INT1    7
#define INT0    6
#define INT2    5
#define IVSEL   1
#define IVCE    0

/* GIFR */
#define INTF1   7
#define INTF0   6
#define INTF2   5

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

/* SPMCR */
#define SPMIE   7
#define RWWSB   6
/* bit 5 reserved */
#define RWWSRE  4
#define BLBSET  3
#define PGWRT   2
#define PGERS   1
#define SPMEN   0

/* TWCR */
#define TWINT   7
#define TWEA    6
#define TWSTA   5
#define TWSTO   4
#define TWWC    3
#define TWEN    2
/* bit 1 reserved */
#define TWIE    0

/* TWAR */
#define TWA6    7
#define TWA5    6
#define TWA4    5
#define TWA3    4
#define TWA2    3
#define TWA1    2
#define TWA0    1
#define TWGCE   0

/* TWSR */
#define TWS7    7
#define TWS6    6
#define TWS5    5
#define TWS4    4
#define TWS3    3
/* bit 2 reserved */
#define TWPS1   1
#define TWPS0   0

/* MCUCR */
#define SE      7
#define SM2     6
#define SM1     5
#define SM0     4
#define ISC11   3
#define ISC10   2
#define ISC01   1
#define ISC00   0

/* MCUCSR */
#define JTD     7
#define ISC2    6
/* bit 5 reserved */
#define JTRF    4
#define WDRF    3
#define BORF    2
#define EXTRF   1
#define PORF    0

/* SFIOR */
#define ADTS2   7
#define ADTS1   6
#define ADTS0   5
/* bit 4 reserved */
#define ACME    3
#define PUD     2
#define PSR2    1
#define PSR10   0

/* TCCR0 */
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0

/* TCCR2 */
#define FOC2    7
#define WGM20   6
#define COM21   5
#define COM20   4
#define WGM21   3
#define CS22    2
#define CS21    1
#define CS20    0

/* ASSR */
/* bits 7-4 reserved */
#define AS2     3
#define TCN2UB  2
#define OCR2UB  1
#define TCR2UB  0

/* TCCR1A */
#define COM1A1  7
#define COM1A0  6
#define COM1B1  5
#define COM1B0  4
#define FOC1A   3
#define FOC1B   2
#define WGM11   1
#define WGM10   0

/* TCCR1B */
#define ICNC1   7
#define ICES1   6
/* bit 5 reserved */
#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0

/* WDTCR */
/* bits 7-5 reserved */
#define WDTOE   4
#define WDE     3
#define WDP2    2
#define WDP1    1
#define WDP0    0

/* PA7-PA0 = ADC7-ADC0 */
/* PORTA */
#define PA7     7
#define PA6     6
#define PA5     5
#define PA4     4
#define PA3     3
#define PA2     2
#define PA1     1
#define PA0     0

/* DDRA */
#define DDA7    7
#define DDA6    6
#define DDA5    5
#define DDA4    4
#define DDA3    3
#define DDA2    2
#define DDA1    1
#define DDA0    0

/* PINA */
#define PINA7   7
#define PINA6   6
#define PINA5   5
#define PINA4   4
#define PINA3   3
#define PINA2   2
#define PINA1   1
#define PINA0   0

/*
   PB7 = SCK
   PB6 = MISO
   PB5 = MOSI
   PB4 = SS#
   PB3 = OC0/AIN1
   PB2 = INT2/AIN0
   PB1 = T1
   PB0 = XCK/T0
 */

/* PORTB */
#define PB7     7
#define PB6     6
#define PB5     5
#define PB4     4
#define PB3     3
#define PB2     2
#define PB1     1
#define PB0     0

/* DDRB */
#define DDB7    7
#define DDB6    6
#define DDB5    5
#define DDB4    4
#define DDB3    3
#define DDB2    2
#define DDB1    1
#define DDB0    0

/* PINB */
#define PINB7   7
#define PINB6   6
#define PINB5   5
#define PINB4   4
#define PINB3   3
#define PINB2   2
#define PINB1   1
#define PINB0   0

/*
   PC7 = TOSC2
   PC6 = TOSC1
   PC1 = SDA
   PC0 = SCL
 */
/* PORTC */
#define PC7     7
#define PC6     6
#define PC5     5
#define PC4     4
#define PC3     3
#define PC2     2
#define PC1     1
#define PC0     0

/* DDRC */
#define DDC7    7
#define DDC6    6
#define DDC5    5
#define DDC4    4
#define DDC3    3
#define DDC2    2
#define DDC1    1
#define DDC0    0

/* PINC */
#define PINC7   7
#define PINC6   6
#define PINC5   5
#define PINC4   4
#define PINC3   3
#define PINC2   2
#define PINC1   1
#define PINC0   0

/*
   PD7 = OC2
   PD6 = ICP
   PD5 = OC1A
   PD4 = OC1B
   PD3 = INT1
   PD2 = INT0
   PD1 = TXD
   PD0 = RXD
 */

/* PORTD */
#define PD7     7
#define PD6     6
#define PD5     5
#define PD4     4
#define PD3     3
#define PD2     2
#define PD1     1
#define PD0     0

/* DDRD */
#define DDD7    7
#define DDD6    6
#define DDD5    5
#define DDD4    4
#define DDD3    3
#define DDD2    2
#define DDD1    1
#define DDD0    0

/* PIND */
#define PIND7   7
#define PIND6   6
#define PIND5   5
#define PIND4   4
#define PIND3   3
#define PIND2   2
#define PIND1   1
#define PIND0   0

/* SPSR */
#define SPIF    7
#define WCOL    6
/* bits 5-1 reserved */
#define SPI2X   0

/* SPCR */
#define SPIE    7
#define SPE     6
#define DORD    5
#define MSTR    4
#define CPOL    3
#define CPHA    2
#define SPR1    1
#define SPR0    0

/* UCSRA */
#define RXC     7
#define TXC     6
#define UDRE    5
#define FE      4
#define DOR     3
#define PE      2
#define U2X     1
#define MPCM    0

/* UCSRB */
#define RXCIE   7
#define TXCIE   6
#define UDRIE   5
#define RXEN    4
#define TXEN    3
#define UCSZ2   2
#define RXB8    1
#define TXB8    0

/* UCSRC */
#define URSEL   7
#define UMSEL   6
#define UPM1    5
#define UPM0    4
#define USBS    3
#define UCSZ1   2
#define UCSZ0   1
#define UCPOL   0

/* ACSR */
#define ACD     7
#define ACBG    6
#define ACO     5
#define ACI     4
#define ACIE    3
#define ACIC    2
#define ACIS1   1
#define ACIS0   0

/* ADCSRA */
#define ADEN    7
#define ADSC    6
#define ADATE   5
#define ADIF    4
#define ADIE    3
#define ADPS2   2
#define ADPS1   1
#define ADPS0   0

/* ADMUX */
#define REFS1   7
#define REFS0   6
#define ADLAR   5
#define MUX4    4
#define MUX3    3
#define MUX2    2
#define MUX1    1
#define MUX0    0

/* EEPROM Control Register */
#define EERIE   3
#define EEMWE   2
#define EEWE    1
#define EERE    0

/* Constants */
#define SPM_PAGESIZE 128
#define RAMEND      0x85F
#define XRAMEND     RAMEND
#define E2END       0x3FF
#define E2PAGESIZE  4
#define FLASHEND    0x7FFF


#endif

