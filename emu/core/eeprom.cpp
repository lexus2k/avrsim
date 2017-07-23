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

#include <avr/eeprom.h>
#include <string.h>

uint8_t eeprom_read_byte (const uint8_t *__p)
{
    return 0xFF;
}

uint16_t eeprom_read_word (const uint16_t *__p)
{
    return 0xFFFF;
}

uint32_t eeprom_read_dword (const uint32_t *__p)
{
    return 0xFFFFFFFF;
}

float eeprom_read_float (const float *__p)
{
    return (float)0xFFFFFFFF;
}

void eeprom_read_block (void *__dst, const void *__src, size_t __n)
{
    memset(__dst, 0xFF, __n);
}

void eeprom_write_byte (uint8_t *__p, uint8_t __value)
{
}

void eeprom_write_word (uint16_t *__p, uint16_t __value)
{
}

void eeprom_write_dword (uint32_t *__p, uint32_t __value)
{
}

void eeprom_write_float (float *__p, float __value)
{
}

void eeprom_write_block (const void *__src, void *__dst, size_t __n)
{
}

void eeprom_update_byte (uint8_t *__p, uint8_t __value)
{
}

void eeprom_update_word (uint16_t *__p, uint16_t __value)
{
}

void eeprom_update_dword (uint32_t *__p, uint32_t __value)
{
}

void eeprom_update_float (float *__p, float __value)
{
}

void eeprom_update_block (const void *__src, void *__dst, size_t __n)
{
}
