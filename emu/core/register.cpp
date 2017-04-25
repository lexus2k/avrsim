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

#include "register.h"

CRegister::CRegister()
{
}


CRegister & CRegister::operator =(uint8_t data)
{
    Assign(data);
    return *this;
}


CRegister & CRegister::operator |=(uint8_t value)
{
    Assign(m_value | value);
    return *this;
}


CRegister & CRegister::operator &=(uint8_t value)
{
    Assign(m_value & value);
    return *this;
}


uint8_t CRegister::operator |(uint8_t op2)
{
    return m_value | op2;
}

uint8_t CRegister::operator &(uint8_t op2)
{
    return m_value & op2;
}


void CRegister::OnChangeBit(uint8_t bit, const std::function<void (uint8_t, uint8_t)> &cb)
{
    m_callbacks[bit] = cb;
}


void CRegister::Assign(uint8_t value)
{
    uint8_t oldValue = m_value;
    uint8_t mask = oldValue ^ value;
    for (uint8_t i=0; i<8; i++)
    {
        if ((mask & (1<<i)) && (m_callbacks.find(i) != m_callbacks.end()))
        {
            m_callbacks[i](i, (value >> i) & 0x1);
        }
    }
    m_value = value;
}


