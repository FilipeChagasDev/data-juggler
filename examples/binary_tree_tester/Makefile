DATAJUGGLER_SRC = $(wildcard ../../src/*.cpp)
DATAJUGGLER_H = -I ../../ -I /../../src/
COMPILER = g++
FLAGS = -O0 -g -Wall $(DATAJUGGLER_H)

all:
	$(COMPILER) $(FLAGS) $(DATAJUGGLER_SRC) main.cpp -o program.elf

run: all
	clear
	./program.elf

clear:
	rm program.elf
