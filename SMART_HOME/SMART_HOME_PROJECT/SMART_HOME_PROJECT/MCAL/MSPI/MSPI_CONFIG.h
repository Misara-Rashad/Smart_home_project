/*
 * MSPI_CONFIG.h
 *
 * Created: 13/04/2023 4:37:53 PM
 *  Author: Misra
 */ 


#ifndef MSPI_CONFIG_H_
#define MSPI_CONFIG_H_

#define INTERRUPT_MODE			INTERRUPT_ENABLED

#define SPI_MODE				SPI_ENABLED

#define DATA_ORDER				the_MSB_of_the_data_word_is_transmitted_first

#define SPI_M_OR_S				SPI_MASTER

#define CLOCK_POLARITY			CLOCK_POLARITY_SCK_is_low_when_idle

#define CLOCK_PHASE				CLOCK_PHASE_SAMPLE_ON_LEADING_SETUP_ON_TRAILING

#define SCK_CLOCK				Fosc_16


#endif /* MSPI_CONFIG_H_ */