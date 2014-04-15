
LSSOLVER_TYPE := lsSolver-unfeasible.cpp
LSSOLVER := lsSolver.cpp $(LSSOLVER_TYPE)

CPSOLVER_TYPE := cpSolver-greedy.cpp
CPSOLVER := cpSolver.cpp $(CPSOLVER_TYPE)

SOURCES := main.cpp graph.cpp solution.cpp $(CPSOLVER) $(LSSOLVER)

BINARY := coloring.bin

# Objs are all the sources, with .cpp replaced by .o
OBJS := $(SOURCES:.cpp=.o)

CC := g++

CFLAGS := -std=c++11 -Wall -O0 -g
#-fopenmp 
LFLAGS := 
#-lpthread

all: $(BINARY)

# Compile the binary by calling the compiler with cflags, lflags, and any libs (if defined) and the list of objects.
$(BINARY): $(OBJS)
	$(CC) $(CFLAGS) -o $(BINARY) $(OBJS) $(LFLAGS) $(LIBS)

# Get a .o from a .cpp by calling compiler with cflags and includes (if defined)
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

clean:
	rm *.o
	rm $(BINARY)
