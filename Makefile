SOURCES = $(wildcard src/*.cpp)
COMPILER = g++
FLAGS = -O0 -g -Wall
	
o: $(patsubst src/%.cpp, obj/%.o, $(SOURCES) )

obj/%.o: src/%.cpp $(SOURCES)
	$(COMPILER) $(FLAGS) -c -o $@ $<

clear:
	rm -f obj/*.o

docs:
	doxygen
