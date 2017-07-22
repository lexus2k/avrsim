# AVR Simulator

This is simulator for AVR controllers.
It supports partially Attiny85, and is provided as is.
OS: Linux

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
 
3. Supported OS

 * Linux

4. Structure

 * emu/avr      - Fake AVR stdlib headers
 * emu/core     - Simulator core, implementing main Arduino/AVR
                  functions
 * emu/mcu      - cpu specific files (reworked avr files)
 * emu/modules  - Modules to connect to your mcu configuration: display, buttons
 * emu/utils    - Some headers with avrlib specific functions
 * boards       - contains hardware board description in C++ for each project
 * projects     - contains original project sources
 * projects/libraries - contains libraries used by the projects

5. Usage

 SDL2 is required to be installed in the system, you're working in.

 To run demo (arkanoid breakout game is used as default example):

 * make run

 To run lode runner demo:
 * make PROJECT=lode_runner run

 If you want to place your project:
 * put all libs, projects requires to projects/libraries
 * put your project files to projects/<name> folder
 * create board configuration for your project: boards/<name>.cpp.
    refer to lcd_arkanoid.cpp as example.
 * run: make PROJECT=<name> LIBRARIES=<list> run

That's it
