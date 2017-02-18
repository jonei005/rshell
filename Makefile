CC=g++
CC_FLAGS=-Wall -Werror -ansi -pedantic
EXEC=rshell

all: src/main.cpp src/*.h
	mkdir -p bin
	$(CC) src/main.cpp -o bin/rshell

rshell: src/main.cpp src/*.h
	mkdir -p bin
	$(CC) src/main.cpp -o bin/rshell

clean:
	rm *.o rshell
