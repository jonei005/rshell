CC=g++
CC_FLAGS=-Wall -Werror -ansi -pedantic
EXEC=rshell

all: src/rshell.cpp src/Functions.cpp src/*.h
	mkdir -p bin
	$(CC) src/rshell.cpp src/Functions.cpp -o bin/rshell

rshell: src/rshell.cpp src/Functions.cpp src/*.h
	mkdir -p bin
	$(CC) src/rshell.cpp src/Functions.cpp -o bin/rshell

clean:
	rm *.o rshell
