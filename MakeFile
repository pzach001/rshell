flag  = -ansi -pedantic -Wall -Werrori
compilervar = g++
all: rshell

rshell:
	mkdir -p bin
	$(compilervar) $(flag) src/rshell.cpp -o bin/rshell 
