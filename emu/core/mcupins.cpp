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

#include "mcupins.h"
#include "system.h"
#include <Arduino.h>

using namespace std::placeholders;


void  CMcuPin::Connect(
    const std::function<int32_t (void)> &onGet,
    const std::function<void (int32_t)> &onSet)
{
    m_onSet.push_back(onSet);
    m_onGet.push_back(onGet);
}


void CMcuPin::attachInterrupt(const std::function <void (uint8_t)> &interrupt)
{
    m_interrupts.push_back(interrupt);
}


CDigitalPin::CDigitalPin(CRegister &dir, CRegister &out, CRegister &in, uint8_t bit)
   :m_dir(dir)
   ,m_out(out)
   ,m_in(in)
{
    m_bit=bit;
    m_out.OnChangeBit(bit, std::bind(&CDigitalPin::OnPortChange, this, _1, _2));
}


void CDigitalPin::OnPortChange(uint8_t bit, uint8_t v)
{
    /* If port is output, this affects connected devices */
    if (m_dir.Get() & (OUTPUT << m_bit))
    {
        if (v == 0) NotifyAll(0.0);
        else        NotifyAll(g_powerVoltage);
    }
    /* If port is input, this is pull up resistor */
    else
    {
        int32_t volt = VOLTAGE_UNSPECIFIED;
        for (auto cb: m_onGet)
        {
            volt = cb();
            if (volt != VOLTAGE_UNSPECIFIED) break;
        }
        if (volt == VOLTAGE_UNSPECIFIED)
        {
            if (v == HIGH) // pull-up resistor enabled
                volt = g_powerVoltage;
        }
        NotifyAll(volt);
    }
}


void CDigitalPin::SetVoltage(int32_t voltage)
{
    /* If pin is configured as output, do nothing */
    if (m_dir.Get() & (OUTPUT << m_bit))
    {
        return;
    }
    /* Pin is configured as input, in the common case, its level is defined by connected devices */
    m_voltage = voltage;
    uint8_t level;
    /* High Level and Low Level */
    if (m_voltage > g_powerVoltage/2)
    {
        level = HIGH;
        m_in |= (1 << m_bit);
    }
    else
    {
        level = LOW;
        m_in &= ~(1 << m_bit);
    }
    /* Check interrupt tables */
    for (auto i: m_interrupts)
    {
        i(level);
    }
}


int32_t CDigitalPin::GetVoltage()
{
    /* If pin is configured as output, just return what is set now */
    if (m_dir.Get() & (OUTPUT << m_bit))
    {
        if (m_out.Get() & (HIGH << m_bit))
            return g_powerVoltage;
        else
            return 0;
    }
    /* Pin is configured as input, in the common case, its level is defined by connected devices */
    return m_voltage;
}


int32_t GetWeakConnection()
{
    return VOLTAGE_UNSPECIFIED;
}
