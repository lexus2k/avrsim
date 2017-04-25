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

#ifndef _MCU_PINS_H_
#define _MCU_PINS_H_

#include <vector>
#include "register.h"

#define WEAK_CONNECTION   &GetWeakConnection

/**
 * Base class for all mcu pins
 */
class CMcuPin
{
public:
    CMcuPin()      {};
    ~CMcuPin()     {};
    void            Connect(const std::function<int32_t (void)> &onGet,
                            const std::function<void (int32_t)> &onSet);
    /* Voltage in special units. Use ITOV VTOI */
    virtual void    SetVoltage(int32_t voltage) { m_voltage = voltage; };
    virtual int32_t GetVoltage() { return m_voltage; };
    void            attachInterrupt(const std::function <void (uint8_t)>  &interrupt);
protected:
    int32_t m_voltage;
    std::vector<std::function<void (int32_t)>> m_onSet;
    std::vector<std::function<int32_t (void)>> m_onGet;
    std::vector<std::function <void (uint8_t)>>
                                               m_interrupts;
    void NotifyAll(int32_t v) { for(auto a: m_onSet) a(v); };
};


class CDigitalPin: public CMcuPin
{
public:
    CDigitalPin(CRegister &dir, CRegister &out, CRegister &in, uint8_t bit);
    ~CDigitalPin() {};
    virtual void SetVoltage(int32_t voltage);
    virtual int32_t GetVoltage();
protected:
    CRegister  &m_dir;
    CRegister  &m_out;
    CRegister  &m_in;
    uint8_t     m_bit;
    void        OnPortChange(uint8_t bit, uint8_t v);
};


extern int32_t GetWeakConnection();

#endif /* _PORT_H_ */

