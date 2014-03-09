SOLVER := dpKnapsackSolver.cpp

SOURCES := main.cpp knapsack.cpp knapsackSolver.cpp $(SOLVER)
# Objs are all the sources, with .cpp replaced by .o
OBJS := $(SOURCES:.cpp=.o)

CC := g++

all: knapsack.bin

# Compile the binary 'knapsack' by calling the compiler with cflags, lflags, and any libs (if defined) and the list of objects.
knapsack.bin: $(OBJS)
	$(CC) $(CFLAGS) -o knapsack.bin $(OBJS) $(LFLAGS) $(LIBS)

# Get a .o from a .cpp by calling compiler with cflags and includes (if defined)
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

clean:
	rm *.o
	rm knapsack
