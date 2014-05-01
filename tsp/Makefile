
SOLVER := solver-3opt.cpp solver-2opt.cpp

SOURCES := main.cpp data.cpp solution.cpp solver-greedy.cpp $(SOLVER)

GPU_SOURCES := 

BINARY := tsp.bin

# Objs are all the sources, with .cpp replaced by .o
CPU_OBJS := $(SOURCES:.cpp=.o)
GPU_OBJS := $(GPU_SOURCES:.cu=.o)
OBJS := $(GPU_OBJS) $(CPU_OBJS)

CC := g++

CFLAGS := -std=c++11 -Wall -O3 -g -fopenmp 
LFLAGS := -lpthread 
#-lcudart

all: $(BINARY)

# Compile the binary by calling the compiler with cflags, lflags, and any libs (if defined) and the list of objects.
$(BINARY): $(OBJS)
	$(CC) $(CFLAGS) -o $(BINARY) $(OBJS) $(LFLAGS) $(LIBS)

# Get a .o from a .cpp by calling compiler with cflags and includes (if defined)
%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<
	
%.o: %.cu
	nvcc -c -code=sm_30 -arch=compute_30 $<

clean:
	rm *.o
	rm $(BINARY)
