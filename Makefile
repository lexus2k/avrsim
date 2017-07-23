#
#   Copyright (C) 2016-2017 Alexey Dynda
#
#   This file is part of AVR Simulator project.
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.

#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#################################################################
#   Input parameters:
#      PROJECT           - Arduino project name
#      LIBRARIES         - List of libraries, neeed for the project
#      BLD               - build dir
#

default: all

BLD ?= bld
PROJECT ?= arkanoid
LIBRARIES ?= ssd1306
MCU ?= attiny85

ifeq ($(MCU),attiny85)
    CCFLAGS += -D__AVR_ATtiny85__ -D__AVR_ARCH__=100
endif

ifeq ($(MCU),atmega328p)
    CCFLAGS += -D__AVR_ATmega328P__ -D__AVR_ARCH__=100
    LIBRARIES += Wire
endif

# Emulator library files
EMU_FILES := $(wildcard emu/alt_arduino/*.cpp) \
             $(wildcard emu/alt_gcc/utils/*.cpp) \
             $(wildcard emu/gcc/util/*.cpp) \
             $(wildcard emu/arduino/*.cpp) \
             $(wildcard emu/core/*.cpp) \

MODULES_FILES := $(wildcard modules/*/*.cpp)
EMU_SRC_FILES = $(EMU_FILES) $(MODULES_FILES)
EMU_OBJ_FILES = $(addprefix $(BLD)/, $(addsuffix .o, $(basename $(EMU_SRC_FILES))))

# Emulator executable files
MAIN_FILES := $(wildcard emu/main/*.cpp)
MAIN_SRC_FILES = $(MAIN_FILES)
MAIN_OBJ_FILES = $(addprefix $(BLD)/, $(addsuffix .o, $(basename $(MAIN_SRC_FILES))))

# Project files (include requires libraries and project code)
PROJECT_FILES := $(wildcard projects/$(PROJECT)/*.cpp) \
                 $(wildcard projects/$(PROJECT)/*.ino) \
                 boards/$(PROJECT).cpp
LIBRARY_FILES := $(foreach lib, $(LIBRARIES), $(wildcard libraries/$(lib)/*.cpp)) \
                 $(foreach lib, $(LIBRARIES), $(wildcard libraries/$(lib)/src/*.cpp)) \
                 $(foreach lib, $(LIBRARIES), $(wildcard libraries/$(lib)/src/*/*.cpp)) \

PROJECT_SRC_FILES = $(PROJECT_FILES) $(LIBRARY_FILES)

# Looking for installed SDL2 library
SDL := $(shell sdl2-config --cflags --libs)

# set up compiler and options
ifeq ($(CROSS_COMPILE),)
    STRIP ?= strip
    AR ?= ar
else
    CC = $(CROSS_COMPILE)gcc
    CXX = $(CROSS_COMPILE)g++
    STRIP = $(CROSS_COMPILE)strip
    AR = $(CROSS_COMPILE)ar
endif

export CROSS_COMPILE

.SUFFIXES: .c .cpp .ino

# Compile c as c++ because we use overloaded C++ operators.
$(BLD)/%.o: %.c
	mkdir -p $(dir $@)
	$(CXX) -std=c++11 $(CCFLAGS) -c $< -o $@
#	$(CC) $(CCFLAGS) -c $< -o $@

$(BLD)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) -std=c++11 $(CCFLAGS) -c $< -o $@

$(BLD)/%.o: %.ino
	mkdir -p $(dir $@)
	$(CXX) -std=c++11 $(CCFLAGS) -x c++ -c $< -o $@

INCLUDES += -Iemu/alt_arduino -Iemu/arduino \
            -Iemu/alt_gcc -Iemu/gcc \
            -Imodules \
            -Iemu \
            -Iemu/mcu \
            $(addprefix -Ilibraries/, $(LIBRARIES)) \
            $(addsuffix /src,$(addprefix -Ilibraries/, $(LIBRARIES))) \

CCFLAGS += -fPIC -g $(INCLUDES) -Wall -Werror -DF_CPU=16000000 -pthread \
         $(SDL)

# -nostdinc

PROJECT_OBJ_FILES = $(addprefix $(BLD)/, $(addsuffix .o, $(basename $(PROJECT_SRC_FILES))))


.PHONY: clean all executable run

all: executable

clean:
	rm -rf $(BLD)

$(BLD)/lib$(MCU).so: $(EMU_OBJ_FILES)
	$(CXX) -shared $(CCFLAGS) -o $@ $(EMU_OBJ_FILES) -L. -L$(BLD) $(SDL) -lm -lpthread

$(BLD)/lib$(PROJECT).so: $(PROJECT_OBJ_FILES) $(BLD)/lib$(MCU).so
	$(CXX) -shared $(CCFLAGS) -o $@ $(PROJECT_OBJ_FILES) -L. -L$(BLD) -l$(MCU)

executable: $(MAIN_OBJ_FILES) $(BLD)/lib$(MCU).so $(BLD)/lib$(PROJECT).so
	$(CXX) $(CCFLAGS) -o $(BLD)/start $(MAIN_OBJ_FILES) -L. -L$(BLD) $(SDL) -lm -lpthread -l$(PROJECT) -l$(MCU)

run: executable
	LD_LIBRARY_PATH=$(BLD) ./$(BLD)/start
