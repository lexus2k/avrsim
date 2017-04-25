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

#include "ssd1306_i2c.h"
#include <core/system.h>

using namespace std::placeholders;

#define PIXEL_SIZE 2

inline uint8_t bitMaskToBit(uint8_t mask)
{
    uint8_t i=(uint8_t)-1;
    while (mask) { i++; mask>>=1; };
    return i;
}


void Cssd1306i2c::BindPins(CMcuPin &sda, CMcuPin &scl)
{
    sda.Connect(WEAK_CONNECTION, std::bind(&Cssd1306i2c::OnSDA, this, _1));
    scl.Connect(WEAK_CONNECTION, std::bind(&Cssd1306i2c::OnSCL, this, _1));
}

Cssd1306i2c::Cssd1306i2c(int x, int y)
    :CModule(x, y, 128*PIXEL_SIZE + 3, 64*PIXEL_SIZE + 3)
{
    m_inProgress = false;
}

Cssd1306i2c::~Cssd1306i2c()
{
}


void Cssd1306i2c::OnSDA(int32_t v)
{
    if (m_scl && (v>g_powerVoltage/2))
    {
        /* Stop transmission */
        m_addr = 0x0;
        m_inProgress = false;
        if (!s_commandMode)
        {
        }
    }
    m_sda = (v > g_powerVoltage/2);
}


void Cssd1306i2c::OnSCL(int32_t v)
{
    if (!m_inProgress && !m_sda && (v<g_powerVoltage/2))
    {
        /* Start transmission */
        s_newTransmission = true;
        m_inProgress = true;
        m_idx = 8;
        m_data = 0;
    }
    else if ((v>g_powerVoltage/2) && m_inProgress)
    {
        if (m_idx == 0)
        {
            m_idx = 8;
            /* byte transferred */
            if (m_addr == 0)
            {
                m_addr = m_data;
            }
            else if (m_addr == (I2C_ADDR << 1))
            {
                ssd1306_i2cSendByte(m_data);
            }
        }
        else
        {
            m_idx--;
            m_data &= ~(1 << m_idx);
            m_data |= (m_sda << m_idx);
        }
    }
    m_scl = (v > g_powerVoltage/2);
}


void Cssd1306i2c::ssd1306_i2cSendByte(uint8_t byte)
{
    if (s_newTransmission)
    {
        s_newTransmission = false;
        if (byte == 0x00) s_commandMode = true;
        else s_commandMode = false;
    }
    else if (s_commandMode)
    {
        if ((byte >= 0xb0) && (byte <= 0xbf))
        {
            m_pixelY =  (uint16_t)(byte & 0x0F) * 8;
        }
        else if ((byte <= 0x0F))
        {
            m_pixelX = (m_pixelX & 0xFFF0) | (uint16_t)byte;
        }
        else if ((byte <= 0x1F) && (byte >= 0x10))
        {
            m_pixelX = (m_pixelX & 0x000F) | ((int16_t)(byte & 0x0F) << 4);
        }
    }
    else if (!s_commandMode)
    {
        for (int i=0; i<8; i++)
        {
            if (byte & (1<<i))
            {
                m_buffer[m_pixelY][m_pixelX] = 1;
            }
            else
            {
                m_buffer[m_pixelY][m_pixelX] = 0;
            }
            m_pixelY++;
        }
        m_pixelY -= 8;
        m_pixelX++;
        if (m_pixelX >= 128)
        {
            m_pixelX = 0;
            m_pixelY += 8;
        }
    }
}


void Cssd1306i2c::OnDraw(SDL_Renderer *renderer)
{
    for (int y = 0; y < 64; y++)
    {
        for (int x=0; x<128; x++)
        {
            if (m_buffer[y][x])
            {
                SDL_SetRenderDrawColor( renderer, 170, 170, 205, 255 );
            }
            else
            {
                SDL_SetRenderDrawColor( renderer, 20, 20, 20, 255 );
            }
            SDL_Rect r;
            r.x = x * PIXEL_SIZE + m_posX + 1;
            r.y = y * PIXEL_SIZE + m_posY + 1;
            r.w = PIXEL_SIZE;
            r.h = PIXEL_SIZE;
            // Render rect
            SDL_RenderFillRect( renderer, &r );
        }
    }
    SDL_SetRenderDrawColor( renderer, 60, 200, 60, 255 );
    SDL_Rect r;
    r.x = m_posX;
    r.y = m_posY;
    r.w = m_width;
    r.h = m_height;
    SDL_RenderDrawRect( renderer, &r );

}


