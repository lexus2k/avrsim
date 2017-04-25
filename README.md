# AVR Simulator

This is simulator for AVR controllers.
It supports partially Attiny85, and is provided as is.

1. Introduction

It was created to run some avr code on the pc to get 
common representation of algorythms, developed. It is
simulator and NOT emulator. That is:

 * you run your program on the different CPU, not Atmel (x86);
 * interrupts do not actually interrupt main program (They work in parallel thread);
 * signals are not emulated as they are in real life.

Feel free, if you need to do any changes to simulator code.

Only C++ is supported.

2. Supported MCUs

 * Attiny85 (partially)

3. Structure

 * emu/avr      - Fake AVR stdlib headers
 * emu/core     - Simulator core, implementing main Arduino/AVR
                  functions
 * emu/mcu      - cpu specific files (reworked avr files)
 * emu/modules  - Modules to connect to your mcu configuration: display, buttons
 * emu/utils    - Some headers with avrlib specific functions

4. Using

 SDL2 is required to be installed in the system, you're working in.

 To run demo (arkanoid breakout game is used as example):
     make run

 If you want to place your project:
 a) put all libs, projects requires to projects/libraries
 b) put your project files to projects/<name> folder
 c) create board configuration for your project: boards/<name>.cpp.
    refer to lcd_arkanoid.cpp as example.
 d) run: make PROJECT=<name> LIBRARIES=<list> run

That's it