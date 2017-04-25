#ifndef _ATTINY85_H_
#define _ATTINY85_H_ 1

/* I/O registers */

/* Reserved [0x00..0x02] */

extern  CRegister  ADCSRB;
#define BIN     7
#define ACME    6
#define IPR     5
#define ADTS2   2
#define ADTS1   1
#define ADTS0   0

/** 16 bit **/
extern CRegister ADC;
#define ADCW    _SFR_IO16(0x04)
#define ADCL    _SFR_IO8(0x04)
#define ADCH    _SFR_IO8(0x05)

extern CRegister16 ADCSRA;
#define ADEN    7
#define ADSC    6
#define ADATE   5
#define ADIF    4
#define ADIE    3
#define ADPS2   2
#define ADPS1   1
#define ADPS0   0

extern CRegister ADMUX;
#define REFS1   7
#define REFS0   6
#define ADLAR   5
#define REFS2   4
#define MUX3    3
#define MUX2    2
#define MUX1    1
#define MUX0    0

extern CRegister ACSR;
#define ACD     7
#define ACBG    6
#define ACO     5
#define ACI     4
#define ACIE    3
#define ACIS1   1
#define ACIS0   0

/* Reserved [0x09..0x0C] */

extern CRegister USICR;
#define USISIE  7
#define USIOIE  6
#define USIWM1  5
#define USIWM0  4
#define USICS1  3
#define USICS0  2
#define USICLK  1
#define USITC   0

#define USISR   _SFR_IO8(0x0E)
#define USISIF  7 
#define USIOIF  6
#define USIPF   5
#define USIDC   4
#define USICNT3 3
#define USICNT2 2
#define USICNT1 1
#define USICNT0 0

extern CRegister USIDR;
extern CRegister USIBR;
extern CRegister GPIOR0;
extern CRegister GPIOR1;
extern CRegister GPIOR2;

extern CRegister DIDR0;
#define ADC0D   5
#define ADC2D   4
#define ADC3D   3
#define ADC1D   2
#define AIN1D   1 
#define AIN0D   0

extern CRegister PCMSK;
#define PCINT5  5
#define PCINT4  4
#define PCINT3  3
#define PCINT2  2
#define PCINT1  1
#define PCINT0  0

extern CRegister PINB;
#define PINB5   5
#define PINB4   4
#define PINB3   3
#define PINB2   2
#define PINB1   1
#define PINB0   0

extern CRegister DDRB;
#define DDB5    5
#define DDB4    4
#define DDB3    3
#define DDB2    2
#define DDB1    1
#define DDB0    0

extern CRegister PORTB;
#define PB5     5
#define PB4     4
#define PB3     3
#define PB2     2
#define PB1     1
#define PB0     0

/* Reserved [0x19..0x1B] */

/* EEPROM Control Register EECR */
extern CRegister EECR;
#define EEPM1   5
#define EEPM0   4
#define EERIE   3
#define EEMPE   2
#define EEPE    1
#define EERE    0

/* EEPROM Data Register */
extern CRegister EEDR;

/* EEPROM Address Register */
#define EEAR	_SFR_IO16(0x1E)
#define EEARL	_SFR_IO8(0x1E)
#define EEARH	_SFR_IO8(0x1F)

#define PRR     _SFR_IO8(0x20)
#define PRTIM1  3
#define PRTIM0  2
#define PRUSI   1
#define PRADC   0

#define __AVR_HAVE_PRR	((1<<PRADC)|(1<<PRUSI)|(1<<PRTIM0)|(1<<PRTIM1))
#define __AVR_HAVE_PRR_PRADC
#define __AVR_HAVE_PRR_PRUSI
#define __AVR_HAVE_PRR_PRTIM0
#define __AVR_HAVE_PRR_PRTIM1

extern CRegister WDTCR;
#define WDIF    7
#define WDIE    6
#define WDP3    5
#define WDCE    4
#define WDE     3
#define WDP2    2
#define WDP1    1
#define WDP0    0

#define DWDR    _SFR_IO8(0x22)

#define DTPS1   _SFR_IO8(0x23)
#define DTPS11   1
#define DTPS10   0

#define DT1B    _SFR_IO8(0x24)
#define DT1BH3  7
#define DT1BH2  6
#define DT1BH1  5
#define DT1BH0  4
#define DT1BL3  3
#define DT1BL2  2
#define DT1BL1  1
#define DT1BL0  0

#define DT1A    _SFR_IO8(0x25)
#define DT1AH3  7
#define DT1AH2  6
#define DT1AH1  5
#define DT1AH0  4
#define DT1AL3  3
#define DT1AL2  2
#define DT1AL1  1
#define DT1AL0  0

#define CLKPR   _SFR_IO8(0x26)
#define CLKPCE  7
#define CLKPS3  3
#define CLKPS2  2
#define CLKPS1  1
#define CLKPS0  0

#define PLLCSR  _SFR_IO8(0x27)
#define LSM     7
#define PCKE    2
#define PLLE    1
#define PLOCK   0

#define OCR0B   _SFR_IO8(0x28)

#define OCR0A   _SFR_IO8(0x29)

#define TCCR0A  _SFR_IO8(0x2A)
#define COM0A1  7
#define COM0A0  6
#define COM0B1  5
#define COM0B0  4
#define WGM01   1
#define WGM00   0

#define OCR1B   _SFR_IO8(0x2B)

#define GTCCR   _SFR_IO8(0x2C)
#define TSM     7
#define PWM1B   6
#define COM1B1  5
#define COM1B0  4
#define FOC1B   3
#define FOC1A   2
#define PSR1    1
#define PSR0    0

#define OCR1C   _SFR_IO8(0x2D)

#define OCR1A   _SFR_IO8(0x2E)

#define TCNT1   _SFR_IO8(0x2F)

#define TCCR1   _SFR_IO8(0x30)
#define CTC1    7
#define PWM1A   6
#define COM1A1  5
#define COM1A0  4
#define CS13    3
#define CS12    2
#define CS11    1
#define CS10    0

#define OSCCAL  _SFR_IO8(0x31)

#define TCNT0   _SFR_IO8(0x32)

#define TCCR0B  _SFR_IO8(0x33)
#define FOC0A   7
#define FOC0B   6
#define WGM02   3
#define CS02    2
#define CS01    1
#define CS00    0

#define MCUSR   _SFR_IO8(0x34)
#define WDRF    3
#define BORF    2
#define EXTRF   1
#define PORF    0

extern CRegister MCUCR;
#define BODS    7
#define PUD     6
#define SE      5
#define SM1     4
#define SM0     3
#define BODSE   2
#define ISC01   1
#define ISC00   0

/* Reserved [0x36] */

#define SPMCSR  _SFR_IO8(0x37)
#define RSIG    5
#define CTPB    4
#define RFLB    3
#define PGWRT   2
#define PGERS   1
#define SPMEN   0

#define TIFR    _SFR_IO8(0x38)
#define OCF1A   6
#define OCF1B   5
#define OCF0A   4
#define OCF0B   3
#define TOV1    2
#define TOV0    1

#define TIMSK   _SFR_IO8(0x39)
#define OCIE1A  6
#define OCIE1B  5
#define OCIE0A  4
#define OCIE0B  3
#define TOIE1   2
#define TOIE0   1

#define GIFR    _SFR_IO8(0x3A)
#define INTF0   6
#define PCIF    5

extern  CRegister  GIMSK;
#define INT0    6
#define PCIE    5

/* Reserved [0x3C] */

/* 0x3D..0x3E SP  [defined in <avr/io.h>] */
/* 0x3F SREG      [defined in <avr/io.h>] */

extern CRegister SREG;
#define SREG_C  (0)
#define SREG_Z  (1)
#define SREG_N  (2)
#define SREG_V  (3)
#define SREG_S  (4)
#define SREG_H  (5)
#define SREG_T  (6)
#define SREG_I  (7)

///---


/* Interrupt vectors */
/* Interrupt vector 0 is the reset vector. */
/* External Interrupt 0 */
#define INT0_vect_num	        1
#define INT0_vect			_VECTOR(1)
#define SIG_INTERRUPT0			_VECTOR(1)

/* Pin change Interrupt Request 0 */
#define PCINT0_vect_num			2
#define PCINT0_vect			_VECTOR(2)
#define SIG_PIN_CHANGE			_VECTOR(2)

/* Timer/Counter1 Compare Match 1A */
#define TIM1_COMPA_vect_num		3
#define TIM1_COMPA_vect			_VECTOR(3)
#define TIMER1_COMPA_vect_num	3
#define TIMER1_COMPA_vect		_VECTOR(3)
#define SIG_OUTPUT_COMPARE1A	_VECTOR(3)

/* Timer/Counter1 Overflow */
#define TIM1_OVF_vect_num		4
#define TIM1_OVF_vect			_VECTOR(4)
#define TIMER1_OVF_vect_num		4
#define TIMER1_OVF_vect			_VECTOR(4)
#define SIG_OVERFLOW1			_VECTOR(4)

/* Timer/Counter0 Overflow */
#define TIM0_OVF_vect_num		5
#define TIM0_OVF_vect			_VECTOR(5)
#define TIMER0_OVF_vect_num		5
#define TIMER0_OVF_vect			_VECTOR(5)
#define SIG_OVERFLOW0			_VECTOR(5)

/* EEPROM Ready */
#define EE_RDY_vect_num			6
#define EE_RDY_vect		    	_VECTOR(6)
#define SIG_EEPROM_READY		_VECTOR(6)

/* Analog comparator */
#define ANA_COMP_vect_num		7
#define ANA_COMP_vect			_VECTOR(7)
#define SIG_COMPARATOR			_VECTOR(7)

/* ADC Conversion ready */
#define ADC_vect_num    		8
#define ADC_vect		    	_VECTOR(8)
#define SIG_ADC				    _VECTOR(8)

/* Timer/Counter1 Compare Match B */
#define TIM1_COMPB_vect_num  	9
#define TIM1_COMPB_vect			_VECTOR(9)
#define TIMER1_COMPB_vect_num	9
#define TIMER1_COMPB_vect   	_VECTOR(9)
#define SIG_OUTPUT_COMPARE1B	_VECTOR(9)

/* Timer/Counter0 Compare Match A */
#define TIM0_COMPA_vect_num		10
#define TIM0_COMPA_vect			_VECTOR(10)
#define TIMER0_COMPA_vect_num	10
#define TIMER0_COMPA_vect		_VECTOR(10)
#define SIG_OUTPUT_COMPARE0A	_VECTOR(10)

/* Timer/Counter0 Compare Match B */
#define TIM0_COMPB_vect_num		11
#define TIM0_COMPB_vect			_VECTOR(11)
#define TIMER0_COMPB_vect_num	11
#define TIMER0_COMPB_vect		_VECTOR(11)
#define SIG_OUTPUT_COMPARE0B	_VECTOR(11)

/* Watchdog Time-out */
#define WDT_vect_num			12
#define WDT_vect				_VECTOR(12)
#define SIG_WATCHDOG_TIMEOUT	_VECTOR(12)

/* USI START */
#define USI_START_vect_num		13
#define USI_START_vect			_VECTOR(13)
#define SIG_USI_START			_VECTOR(13)

/* USI Overflow */
#define USI_OVF_vect_num		14
#define USI_OVF_vect			_VECTOR(14)
#define SIG_USI_OVERFLOW		_VECTOR(14)

#define _VECTORS_SIZE 30


/* ========================  ARDUINO PART ============================= */

#include <avr/pgmspace.h>

// ATMEL ATTINY45 / ARDUINO
//
//                  +-\/-+
// Ain0 (D 5) PB5  1|    |8  Vcc
// Ain3 (D 3) PB3  2|    |7  PB2 (D 2)  Ain1
// Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1
//            GND  4|    |5  PB0 (D 0) pwm0
//                  +----+

#define NUM_DIGITAL_PINS            3
#define NUM_ANALOG_INPUTS           1
#define LED_BUILTIN   	            1

/* arduino registers */


static const uint8_t A0 = 6;
static const uint8_t A1 = 7;
static const uint8_t A2 = 8;
static const uint8_t A3 = 9;

#define digitalPinToPCICR(p)    ( ((p) >= 0 && (p) <= 4) ? (&GIMSK) : ((uint8_t *)0) )
#define digitalPinToPCICRbit(p) ( PCIE )
#define digitalPinToPCMSK(p)    ( ((p) <= 4) ? (&PCMSK) : ((uint8_t *)0) )
#define digitalPinToPCMSKbit(p) ( (p) )

#define digitalPinToInterrupt(p)  ((p) == 2 ? 0 : NOT_AN_INTERRUPT)

#define analogPinToChannel(p)   ( (p) < 6 ? (p) : (p) - 6 )

#define TCCR1A GTCCR


#define digitalPinToPort(P)     (2)
#define digitalPinToBitMask(P)  (1<<P)
#define portOutputRegister(P)   PORTB
#define portInputRegister(P)    PINB
#define portModeRegister(P)     DDRB

extern  CDigitalPin             MCU_PIN2;
extern  CDigitalPin             MCU_PIN3;
extern  CDigitalPin             MCU_PIN5;
extern  CDigitalPin             MCU_PIN7;

#ifdef EMULATOR_MAIN

#define LOW_ 0
#define HIGH_ 1

CRegister   DDRB;
CRegister   PORTB;
CRegister   PINB;
CRegister   GIMSK;
CRegister16 ADCSRA;
CRegister   PCMSK;
CRegister   SREG;
CRegister   MCUCR;

// Core
//   ->Button
//     ->Pin
//       ->Check SREG
//       ->checks MCUCR ISC bits to figure out if interrupt should happen
//         ->checks PCMSK   mask
//           ->checks GIMSK INT0 bit
//             ->checks sei and calls vector 1

void __vector_1() __attribute__((weak));
void __vector_1()
{
}

void __vector_2() __attribute__((weak));
void __vector_2()
{
}


std::map<uint8_t, std::function <void ()>> g_vectors;


CDigitalPin             MCU_PIN2(DDRB, PORTB, PINB, 3); // PCINT3
CDigitalPin             MCU_PIN3(DDRB, PORTB, PINB, 4); // PCINT4
CDigitalPin             MCU_PIN5(DDRB, PORTB, PINB, 0); // PCINT0
CDigitalPin             MCU_PIN7(DDRB, PORTB, PINB, 2); // INT0,PCINT2

void int0Interrupt(uint8_t level)
{
    static uint8_t lastLevel = LOW_;
    if ((SREG & (1<<SREG_I)) == 0)
    {
        return;
    }
    if ((GIMSK & (1<<INT0)) == 0)
    {
        return;
    }
    bool shouldHappen = false;
    if ( (level == LOW_) && (lastLevel == LOW_) && !(MCUCR & (1<<ISC01)) && !(MCUCR & (1<<ISC00)) )
    {
        shouldHappen  = true;
    }
    if ( (level != lastLevel) && !(MCUCR & (1<<ISC01)) && (MCUCR & (1<<ISC00)) )
    {
        shouldHappen = true;
    }
    if ( (level == LOW_) && (level != lastLevel) && (MCUCR & (1<<ISC01)) && !(MCUCR & (1<<ISC00)) )
    {
        shouldHappen = true;
    }
    if ( (level == HIGH_) && (level != lastLevel) && (MCUCR & (1<<ISC01)) && (MCUCR & (1<<ISC00)) )
    {
        shouldHappen = true;
    }
    lastLevel = level;

    // or user defined interrupt via attachInterrupt(0 + 1-> vector int0, mode -> ISC)
    if (shouldHappen)
    {
        g_vectors[1]();
    }
}


void pcint0Interrupt(uint8_t bit, uint8_t level)
{
    static uint8_t lastLevel = level;
    if ((SREG & (1<<SREG_I)) == 0)
    {
        return;
    }
    if ((GIMSK & (1<<PCIE)) == 0)
    {
        return;
    }
    if ((PCMSK & (1<<bit)) == 0)
    {
        return;
    }
    if (lastLevel != level)
    {
        // or user defined interrupt via attachInterrupt(0 + 1-> vector int0, mode -> ISC)
        g_vectors[2]();
    }
    lastLevel = level;
}

using namespace std::placeholders;

void initMcu()
{
    g_vectors[1] = &__vector_1;
    g_vectors[2] = &__vector_2;
    MCU_PIN7.attachInterrupt(&int0Interrupt);
    MCU_PIN5.attachInterrupt(std::bind(&pcint0Interrupt, 0, _1));
}

#endif


#endif /* _ATTINY85_H_ */
