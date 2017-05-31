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


#ifndef _SSD1306_H_
#define _SSD1306_H_

#include "ssd1306_i2c.h"

#ifndef SSD1306_SA
    /* Write command will be SSD1306_SA<<1 and read will be SSD1306_SA<<1 | 1 */
    #define SSD1306_SA    0x3C  // Slave address
#endif

#define SSD1306_DEFAULT_ADDRESS 0x78
#define SSD1306_SETCONTRAST    0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON   0xA5
#define SSD1306_NORMALDISPLAY  0xA6
#define SSD1306_INVERTDISPLAY  0xA7
#define SSD1306_DISPLAYOFF     0xAE
#define SSD1306_DISPLAYON      0xAF
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS     0xDA
#define SSD1306_SETVCOMDETECT  0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE   0xD9
#define SSD1306_SETMULTIPLEX   0xA8
#define SSD1306_SETLOWCOLUMN   0x00
#define SSD1306_SETHIGHCOLUMN  0x10
#define SSD1306_SETSTARTLINE   0x40
#define SSD1306_MEMORYMODE     0x20
#define SSD1306_COLUMNADDR     0x21
#define SSD1306_PAGEADDR       0x22
#define SSD1306_COMSCANINC     0xC0
#define SSD1306_COMSCANDEC     0xC8
#define SSD1306_SEGREMAP       0xA0
#define SSD1306_CHARGEPUMP     0x8D
#define SSD1306_SWITCHCAPVCC   0x2
#define SSD1306_NOP            0xE3

typedef struct
{
    uint8_t left;
    uint8_t top;
    uint8_t right;
    uint8_t bottom;
} SSD1306_RECT;


typedef struct
{
    uint8_t x;
    uint8_t y;
    uint8_t w;
    uint8_t lx;
    uint8_t ly;
    const uint8_t * data;
} SPRITE;


void         ssd1306_init();
void         ssd1306_setPos(uint8_t x, uint8_t y);
void         ssd1306_fillScreen(uint8_t fill_Data);
void         ssd1306_clearScreen();
void         ssd1306_charF5x7(uint8_t x, uint8_t y, const char ch[]);
void         ssd1306_charF6x8(uint8_t x, uint8_t y, const char ch[]);
void         ssd1306_drawCanvas(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *buf);
void         ssd1306_drawBitmap(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *buf);
void         ssd1306_drawSpriteData(uint8_t x, uint8_t y, const uint8_t *sprite);

// ----------------------------------------------------------------------------
void         ssd1306_drawSprite(SPRITE *sprite);
void         ssd1306_eraseSprite(SPRITE *sprite);
void         ssd1306_eraseTrace(SPRITE *sprite);
SPRITE       ssd1306_createSprite(uint8_t x, uint8_t y, uint8_t w, const uint8_t *data);
SSD1306_RECT ssd1306_rect(SPRITE * sprite);
SSD1306_RECT ssd1306_rectFromSprite(uint8_t x, uint8_t y, uint8_t w);

// ----------------------------------------------------------------------------
#endif // _SSD1306_H_
