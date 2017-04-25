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

#ifndef _REGISTER16_H_
#define _REGISTER16_H_

#include <stdint.h>
#include <functional>
#include <map>

class CRegister16
{
public:
    CRegister16();
    CRegister16 & operator =(uint16_t value);
    CRegister16 & operator |=(uint16_t value);
    CRegister16 & operator &=(uint16_t value);
    uint16_t operator |(uint16_t op2);
    uint16_t operator &(uint16_t op2);
    uint16_t Get() { return m_value; };

    void OnChangeBit(uint16_t bit, const std::function<void (uint16_t, uint16_t)> &cb);
private:
    std::map<uint16_t, std::function<void (uint16_t, uint16_t)>>
                                    m_callbacks;
    uint16_t                         m_value = 0;
    void                            Assign(uint16_t value);
};

#endif /* _REGISTER16_H_ */

