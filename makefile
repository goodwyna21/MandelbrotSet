CXX=g++

main: Source/main.cpp Source/ConfigParser.h
	$(CXX) -o $@ $^
