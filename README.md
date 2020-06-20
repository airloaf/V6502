# V6502
Instruction accurate 6502 CPU Library written in C++. STILL IN DEVELOPMENT

## Dependencies
### Required:
- [CMake 3.9+](https://cmake.org/)

### Optional:
- [Boost 1.66+](https://www.boost.org/) # Only for building the test

Note: Older versions of Boost may work, but 1.66+ have been tested to work.

## Building
There are two build targets for CMake, the actual V6502 library and the unit tests.

### Compiling libV6502
By default libV6502 will compile into a shared library, this can be changed in CMakeLists.txt
1. cmake .
2. make

### Compiling Unit Tests
The unit tests require the boost library, see [Dependencies](#Dependencies)
1. Place boost into the libs/ 
2. cmake .
3. make
4. ./Tests

Note: Your libs folders should look like this libs/boost_X/, where boost_X is your version of boost. For example boost 1.73.0 is boost_1_73_0.

## Use Cases 
The main purpose of this library is to provide a portable software implementation of the 6502 cpu for the development of emulators. My initial intention was to use this library to aid in the development of an NES emulator I hope to complete some day. The 6502 has been used in many devices such as:
- Nintendo Entertainment System and Famicom
- Atari 2600/5200/7800
- Commodore 64/128
- TurboGrafx-16
- Apple I and II

If someone desires to create an emulator for any of the aforementioned devices, they will need to implement the 6502 cpu in software. This library can be used in place of a CPU implementation from scratch.

This library does not necessarily need to be used in the development of an emulator, it can be used for other non-gaming applications:
- Interpreter
- CPU Visualizer

## References
List of articles, datasheets and videos used in the development of this library
- [Rockwell R650X and R651X Microprocessors Datasheet](http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf)
- [Obelisk CPU Instruction Reference](http://www.obelisk.me.uk/6502/reference.html)
- [NES Dev Wiki](http://wiki.nesdev.com/w/index.php/CPU)
- [NES Dev CPU Cycles](http://nesdev.com/6502_cpu.txt)