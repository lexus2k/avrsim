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

#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <stdint.h>
#include <functional>
#include <map>

class CRegister
{
public:
    CRegister();
    CRegister & operator =(uint8_t value);
    CRegister & operator |=(uint8_t value);
    CRegister & operator &=(uint8_t value);
    uint8_t Get() { return m_value; };
    operator uint8_t();

    void OnChangeBit(uint8_t bit, const std::function<void (uint8_t, uint8_t)> &cb);
private:
    std::map<uint8_t, std::function<void (uint8_t, uint8_t)>>
                                    m_callbacks;
    uint8_t                         m_value = 0;
    void                            Assign(uint8_t value);
};

#endif /* _REGISTER_H_ */

