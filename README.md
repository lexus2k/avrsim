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

4. Sources structure

 * emu          - Emulator engine files
   * emu/alt_arduino - alternate implementation of Arduino includes
   * emu/arduino     - original Arduino includes (or with minimal rework)
   * emu/alt_gcc     - alternate implementation of AVR gcc includes
   * emu/gcc         - original AVR gcc includes (or with minimal rework) - look for [avrsim] tag)
   * emu/core        - Simulator core, implementing main Arduino/AVR functions for Desktop Linux
   * emu/mcu         - cpu specific files (implementation for uC)
 * modules  - Modules to connect to your mcu configuration: display, buttons
   * modules/ssd1306 module - emulates 128x64 ssd1306 OLED LCD display
   * modules/button module  - emulates digital button for AVR
 * boards       - contains hardware board description in C++ for each project
 * projects     - contains original project sources
 * libraries    - contains libraries used by the projects

5. Usage

 SDL2 is required to be installed in the system, you're working in.

 To run demo (arkanoid breakout game is used as default example):

 * make run

 To run lode runner demo:
 * make PROJECT=lode_runner run

 If you want to place your project:
 * put all libs, projects requires to libraries
 * put your project files to projects/<name> folder
 * create board configuration for your project: boards/<name>.cpp.
    refer to arkanoid.ino as example.
 * run: make PROJECT=<name> LIBRARIES=<list> run

Important! Don't forget to execute git command after cloning AVRSIM project:
 * git submodule init
 * git submodule update

That's it
