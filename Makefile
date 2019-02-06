DIR = src

SOURCE = $(DIR)/main.cpp $(DIR)/tetrisformation.cpp $(DIR)/tetrisgenerators.cpp $(DIR)/tetrismatrix.cpp $(DIR)/tetristimer.cpp $(DIR)/formations/_formation.cpp $(DIR)/formations/lformation.cpp $(DIR)/formations/oformation.cpp $(DIR)/formations/sformation.cpp $(DIR)/formations/tformation.cpp

LIBS = -lglfw -ldrawtext -lm -lGL -lpthread

main:
	g++ $(SOURCE) $(LIBS) -o tetris.elf

run: main
	./tetris.elf
