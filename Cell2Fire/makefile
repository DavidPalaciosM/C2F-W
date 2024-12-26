# Compiler
CXX = g++-12

# Compiler and linker flags
CXXFLAGS = -m64 -fPIC -fno-strict-aliasing -fexceptions -fopenmp -DNDEBUG -DIL_STD -std=c++14 -O3 -I /usr/include -I /usr/include/eigen3
LDFLAGS = -m64 -fPIC -fno-strict-aliasing -fexceptions -fopenmp -DNDEBUG -DIL_STD -lm -lpthread -ltiff 

# Source files
SRCS = Cell2Fire.cpp Cells.cpp FuelModelSpain.cpp FuelModelPortugal.cpp FuelModelKitral.cpp FuelModelFBP.cpp Spotting.cpp ReadCSV.cpp ReadArgs.cpp Lightning.cpp WriteCSV.cpp Ellipse.cpp DataGenerator.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Target executable
TARGET = Cell2Fire

# Build rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

DESTDIR = /usr/local/bin
install: all
	cp $(TARGETS) $(DESTDIR)
uninstall: all
	rm $(DESTDIR)/$(TARGETS) 
