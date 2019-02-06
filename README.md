# Tetris
This is a Tetris game developed with C++ and classic OpenGL

<img src="https://github.com/FilipeChagasDev/Tetris/tree/master/screenshots/1.gif" alt="Playing">

## Author Notes:
The code files are in the "src" directory.

The "serif.ttf" file contains the font used for rendering text in this program, and it must be in the same directory as the compiled executable. 

This project was developed in Linux and has not been tested on other platforms.

## Compile and Run

The compiler used here is the g++. Install it before try to compile this project.

To compile this project, you must first install all dependencies. After do it, you must open this directory in the terminal and put the following commands:

``` sh
make
```
After do it, the compiler will generate a "tetris.elf" linux executable file. To run it, you need to put the following command in the terminal:

``` sh
./tetris.elf
```

To compile and run this project at once, you need to put the following command in the terminal:

```
make run
```

## Dependencies
this project depends on the following libraries and APIS: OpenGL, GLFW 3 and libDrawText 0.3.

OpenGL is used as a rendering engine. The tests were done with version 4.6 of OpenGL, but probably works with older versions.

The GLFW3 library was used to control the windows. It must be installed in the compiler libraries and can be found in the following repository: https://github.com/glfw/glfw

The libDrawText 0.3 library was used to render the texts. It must be installed in the compiler libraries and can be found in the following repository: https://github.com/jtsiomb/libdrawtext

