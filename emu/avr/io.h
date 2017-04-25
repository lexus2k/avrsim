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

#ifndef _AVR_IO_H_
#define _AVR_IO_H_

#include <core/register.h>
#include <core/register16.h>
#include <core/mcupins.h>
#include <avr/sfr_defs.h>

extern std::map<uint8_t, std::function <void ()>> g_vectors;

#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__)
#  include <mcu/atmega328p.h>
#elif defined (__AVR_ATmega168__)
#  include <mcu/atmega168.h>
#elif defined (__AVR_ATtiny85__)
#  include <mcu/attiny85.h>
#else
#  error "device type is not supported"
#endif

#endif /* _AVR_IO_H_ */
