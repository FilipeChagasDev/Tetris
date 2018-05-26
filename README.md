# Tetris
This is a Tetris game developed with C ++ and OpenGL

## Author Notes:
This project was developed using the Qt-creator IDE (although no Qt framework library was used). The code files, together with the qt-creator project file "Tetris-qtcreator.pro", are in the "src/Tetris-qtcreator-project" directory. The project is configured to be compiled in the "src/build-Tetris" directory. Both of these directories need to be located in the same parent directory, otherwise the qt-creator will not find the build-Tetris directory.
Inside the "src/build-Tetris" directory, there is a file called "serif.ttf". This file contains the font used for rendering text in this program, and it must be in the same directory as the compiled executable. 
This project was developed in Linux and has not been tested on other platforms.

## Dependencies
this project depends on the following libraries and APIS: OpenGL, GLFW 3 and libDrawText 0.3.

OpenGL is used as a rendering engine. The tests were done with version 4.6 of OpenGL, but probably works with older versions.

The GLFW3 library was used to control the windows. It must be installed in the compiler libraries and can be found in the following repository: https://github.com/glfw/glfw

The libDrawText 0.3 library was used to render the texts. It must be installed in the compiler libraries and can be found in the following repository: https://github.com/jtsiomb/libdrawtext

