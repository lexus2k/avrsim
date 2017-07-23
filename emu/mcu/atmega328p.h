/*
    Copyright (C) 2016-2017 Alexey Dynda

    This file is part of AVR Simulator project.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _ATMEGA328P_H_
#define _ATMEGA328P_H_ 1

#include <core/register.h>
#include <core/register16.h>
#include <core/mcupins.h>
#include <avr/sfr_defs.h>
#include <avr/common.h>

// Defines all registers to use in the beginning of the header file.
// Implemention of all specific functions and veriables must be defines under EMULATOR_MAIN directive

extern std::map<uint8_t, std::function <void ()>> g_vectors;

/* I/O registers */

/* Reserved [0x00..0x02] */

#undef ADCSRB
extern  CRegister  ADCSRB;

/** 16 bit **/
#undef ADC
extern CRegister ADC;

#undef ADCSRA
extern CRegister16 ADCSRA;

#undef ADMUX
extern CRegister ADMUX;

#undef ACSR
extern CRegister ACSR;

#undef USICR
extern CRegister USICR;

#undef USIDR
extern CRegister USIDR;

#undef USIBR
extern CRegister USIBR;

#undef GPIOR0
extern CRegister GPIOR0;

#undef GPIOR1
extern CRegister GPIOR1;

#undef GPIOR2
extern CRegister GPIOR2;

#undef DIDR0
extern CRegister DIDR0;

#undef PCMSK
extern CRegister PCMSK;

#undef PINB
extern CRegister PINB;

#undef DDRB
extern CRegister DDRB;

#undef PORTB
extern CRegister PORTB;

#undef EECR
extern CRegister EECR;

/* EEPROM Data Register */
#undef EEDR
extern CRegister EEDR;

#undef WDTCR
extern CRegister WDTCR;

#undef MCUCR
extern CRegister MCUCR;

#undef GIMSK
extern  CRegister  GIMSK;

#undef SREG
extern CRegister SREG;

/* ========================  ARDUINO PART ============================= */
// Arduino functions, which are specific for the controller

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
//    if ((GIMSK & (1<<PCIE)) == 0)
//    {
//        return;
//    }
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


#endif /* _ATMEGA328P_H_ */
