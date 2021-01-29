# V6502

MOS 6502 CPU library emulator written in C++

## Features

- Instruction Accurate Implementation
- Modifiable Memory Bus (Useful for systems that utilize bank switching and memory mapped I/O)
- Simple To Use API
- No dependencies for the 6502 Library

## Dependencies

### Required:

- [CMake 3.9+](https://cmake.org/)

Note: Older versions of CMake may work, but 3.9 is what I have been using while developing V6502

### Optional:

- [Boost 1.66+](https://www.boost.org/) # Only need headers for Boost. Boost is only used for the unit tests.

You will need to modify the CMakeLists.txt file with the appropriate paths to find Boost. There are two variables in the CMakeLists.txt file INCLUDE_DIR and LIB_DIR. By default they point to C:/DevelopmentLibraries/include/ and C:/DevelopmentLibraries/lib/x64/ respectively. Ensure you have these directories created or specify the correct path in your environment which has the Boost library installed.

Note: Older versions of Boost may work, but 1.66+ has been tested to work.

## Building

There are two build targets for CMake, the actual V6502 library and the unit tests.

### Compiling V6502

By default V6502 will compile into a static library, but this can be changed in CMakeLists.txt. Modify LIB_TYPE to be SHARED for a dynamic library. Keeping it STATIC will make it a static library

### Compiling Unit Tests

The unit tests require the boost library, see [Dependencies](#Dependencies). The unit tests compile alongside the main library, so no extra steps are needed. You will see an executable called Tests which can be run in a terminal.

## Use Cases 

The main purpose of this library is to provide a portable software implementation of the 6502 cpu for the development of emulators. My initial intention was to use this library to aid in the development of an NES emulator I hope to complete some day. The 6502 has been used in many devices such as:
- Apple I and II
- Atari 2600/5200/7800
- Commodore 64/128
- Nintendo Entertainment System and Famicom
- TurboGrafx-16

If someone desires to create an emulator for any of the aforementioned devices, they will need an implementation of the 6502 cpu. This library should work perfectly for this type of application.

This library does not necessarily need to be used in the development of an emulator, it can be used for other non-gaming applications:
- 6502 Interpreters
- CPU Visualizer
- Virtual Machine for a 6502 computer

## References

List of articles, datasheets and videos used in the development of this library

- [Rockwell R650X and R651X Microprocessors Datasheet](http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf)
- [Obelisk CPU Instruction Reference](http://www.obelisk.me.uk/6502/reference.html)
- [NES Dev Wiki](http://wiki.nesdev.com/w/index.php/CPU)
- [NES Dev CPU Cycles](http://nesdev.com/6502_cpu.txt)
