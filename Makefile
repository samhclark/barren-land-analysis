CXX=g++
CXXFLAGS=-Os -s

.PHONY: all
all: barren_land_analysis

barren_land_analysis: main.o Farm_Runner.o
	$(CXX) -o barren_land_analysis main.o Farm_Runner.o $(CXXFLAGS)

Farm_Runner.o: Farm_Runner.cpp Farm_Runner.h Barren.h Farm.h
	$(CXX) -c -o Farm_Runner.o Farm_Runner.cpp $(CXXFLAGS)
