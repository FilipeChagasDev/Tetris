TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lGL -lglfw -lm -ldrawtext -lpthread

SOURCES += main.cpp \
    tetrismatrix.cpp \
    tetristimer.cpp \
    tetrisformation.cpp \
    formations/tformation.cpp \
    tetrisgenerators.cpp \
    formations/lformation.cpp \
    formations/oformation.cpp \
    formations/_formation.cpp



HEADERS += \
    tetrismatrix.hpp \
    tetrisblock.hpp \
    tetristimer.hpp \
    tetrisformation.hpp \
    formations/tformation.hpp \
    tetrisgenerators.hpp \
    formations/lformation.hpp \
    formations/oformation.hpp \
    formations/_formation.hpp
