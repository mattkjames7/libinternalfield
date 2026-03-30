CXX ?= g++
CXXFLAGS ?= -std=c++17 -O3

TARGET = coeff_registry_codegen
SOURCES = main.cc schmidt.cc scalegh.cc

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
