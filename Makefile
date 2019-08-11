all:
	g++ -g -std=c++11 -o main main.cpp -ljsoncpp

.PHONY: clean
clean:
	rm -f main
