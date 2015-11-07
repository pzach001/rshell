flag  = -Wall -Werror -ansi -pedantic -std=c++0x
compilervar = g++
all: rshell

rshell:
	mkdir -p bin
	$(compilervar) $(flag) src/rshell.cpp -o bin/rshell 
