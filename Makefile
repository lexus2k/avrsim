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

EMU_FILES := $(wildcard emu/*/*.cpp) \
             $(wildcard emu/*/*/*.cpp)
MAIN_FILES := $(wildcard main/*.cpp)
PROJECT_FILES := $(wildcard projects/$(PROJECT)/*.cpp) \
              $(wildcard projects/$(PROJECT)/*.ino) \
              boards/$(PROJECT).cpp
LIBRARY_FILES := $(foreach lib, $(LIBRARIES), $(wildcard projects/libraries/$(lib)/*.cpp))
LIBRARY_FILES := $(foreach lib, $(LIBRARIES), $(wildcard projects/libraries/$(lib)/src/*.cpp))

EMU_SRC_FILES = $(EMU_FILES)
PROJECT_SRC_FILES = $(PROJECT_FILES) $(LIBRARY_FILES)
MAIN_SRC_FILES = $(MAIN_FILES)

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

$(BLD)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -c $< -o $@

$(BLD)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) -std=c++11 $(CCFLAGS) -c $< -o $@

$(BLD)/%.o: %.ino
	mkdir -p $(dir $@)
	$(CXX) -std=c++11 $(CCFLAGS) -x c++ -c $< -o $@

INCLUDES += -Iemu \
        $(addprefix -Iprojects/libraries/, $(LIBRARIES)) \
        $(addsuffix /src,$(addprefix -Iprojects/libraries/, $(LIBRARIES))) \

CCFLAGS += -fPIC -g $(INCLUDES) -Wall -Werror -DF_CPU=16000000 -pthread \
         $(SDL)

ifeq ($(MCU),attiny85)
    CCFLAGS += -D__AVR_ATtiny85__
endif

PROJECT_OBJ_FILES = $(addprefix $(BLD)/, $(addsuffix .o, $(basename $(PROJECT_SRC_FILES))))

EMU_OBJ_FILES = $(addprefix $(BLD)/, $(addsuffix .o, $(basename $(EMU_SRC_FILES))))
MAIN_OBJ_FILES = $(addprefix $(BLD)/, $(addsuffix .o, $(basename $(MAIN_SRC_FILES))))

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
