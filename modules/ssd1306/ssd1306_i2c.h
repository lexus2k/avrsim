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


#ifndef _MODULE_SSD1306_I2C_H_
#define _MODULE_SSD1306_I2C_H_

#include <stdint.h>
#include <SDL2/SDL.h>
#include <core/mcupins.h>
#include <core/system.h>
#include <core/module.h>

#include <Arduino.h>

class Cssd1306i2c: public CModule
{
const uint8_t I2C_ADDR  = 0x3C;
public:
    Cssd1306i2c(int x, int y);
    ~Cssd1306i2c();

//    void BindPins(CRegister &sda, uint8_t sdabit, CRegister &scl, uint8_t sclbit);
    void BindPins(CMcuPin &sda, CMcuPin &scl);
    virtual void OnDraw(SDL_Renderer *renderer);
private:
    bool s_newTransmission = false;
    bool s_commandMode = false;
    SDL_Window *s_window = nullptr;
    SDL_Renderer *s_renderer = nullptr;
    int m_columnStartAddress = 0;
    int m_columnEndAddress = 127;
    int m_activeColumn = 0;
    int m_activePage = 0;
    int m_command;

    uint8_t  m_buffer[8][128];

    uint8_t  m_scl;
    uint8_t  m_sda;
    uint8_t  m_idx;
    uint8_t  m_data;
    uint8_t  m_addr;
    bool     m_inProgress;

    void OnSDA(int32_t v);
    void OnSCL(int32_t v);
    void ssd1306_i2cSendByte(uint8_t byte);
};

// ----------------------------------------------------------------------------
#endif // _MODULE_SSD1306_I2C_H_
