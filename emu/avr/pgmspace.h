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

#ifndef __PGMSPACE_H_
#define __PGMSPACE_H_ 1

#include <stdint.h>

#define PROGMEM

#ifdef __cplusplus
extern "C" {
#endif

#define pgm_read_byte(address_short)    *((uint8_t *)address_short)

#define pgm_read_word(address_short)    *((uint16_t *)address_short)

#define pgm_read_dword(address_short)   *((uint32_t *)address_short)

#define pgm_read_float(address_short)   *((float *)address_short)

#define pgm_read_ptr(address_short)     *(address_short)

#ifdef __cplusplus
}
#endif

#endif /* __PGMSPACE_H_ */
