# Compiler
CXX = g++-12

# Compiler and linker flags
CXXFLAGS = -m64 -fPIC -fno-strict-aliasing -fexceptions -fopenmp -DNDEBUG -DIL_STD -std=c++14 -O3 -I /usr/include -I /usr/include/eigen3 -I /usr/include/catch2
LDFLAGS = -m64 -fPIC -fno-strict-aliasing -fexceptions -fopenmp -DNDEBUG -DIL_STD -lm -lpthread -ltiff
LDFLAGS  += $(shell pkg-config --libs catch2-with-main)
# Source files
SRCS = Cell2Fire.cpp Cells.cpp FuelModelSpain.cpp FuelModelKitral.cpp FuelModelFBP.cpp Spotting.cpp ReadCSV.cpp ReadArgs.cpp Lightning.cpp WriteCSV.cpp Ellipse.cpp DataGenerator.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Target executable
TARGET = Cell2Fire
TEST_DIR = ../test/unit_tests
TEST_TARGET = test_cell2fire

# Test source files
TEST_FILES = $(TEST_DIR)/test_kitral.cpp FuelModelKitral.cpp
#TODO: poner bien los archivos test

# Build rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

tests: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_FILES) $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_FILES)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TEST_TARGET)

DESTDIR = /usr/local/bin
install: all
	cp $(TARGETS) $(DESTDIR)
uninstall: all
	rm $(DESTDIR)/$(TARGETS) 
