# Name of the final executable
exec = kscript.out

# All C++ source files
sources = $(wildcard src/*.cpp)

# Corresponding object files
objects = $(sources:.cpp=.o)

# Compiler flags (debug info for now)
flags = -g

# C++ compiler
CXX = g++

# How to create the final executable
$(exec): $(objects)
	$(CXX) $(objects) $(flags) -o $(exec)

# How to compile each .cpp file into a .o file
%.o: %.cpp include/%.h
	$(CXX) -c $(flags) $< -o $@

install:
	make
	cp ./kscript.out /usr/local/bin/kscript
#now the kscript binary is available on your system globally
# now on just typing kscript in terminal you get the output as
#"Hello World!"

# Clean up everything
clean:
	-rm *.out
	-rm *.o
	-rm src/*.o
