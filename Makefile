GCC = g++
GCC_FLAGS = -I include -std=c++11 -g
EXECUTABLE = exec

all: clean $(EXECUTABLE)

$(EXECUTABLE): functions.o tabu.o main.o
	$(GCC) $(GCC_FLAGS) -o build/$(EXECUTABLE) main.o tabu.o functions.o 

main.o: src/main.cpp 
	$(GCC) $(GCC_FLAGS) -c src/main.cpp 

tabu.o: src/tabu.cpp include/tabu.hpp 
	$(GCC) $(GCC_FLAGS) -c src/tabu.cpp 

functions.o: src/functions.cpp include/functions.hpp include/utils.hpp
	$(GCC) $(GCC_FLAGS) -c src/functions.cpp

clean:
	rm -f *.o
	rm -f build/$(EXECUTABLE)
	rm -f build/out.txt
