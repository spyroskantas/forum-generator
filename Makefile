all: forum

forum: main.cpp
	g++ -c main.cpp
	g++ -std=c++11 -c impl.cpp
	g++ main.o impl.o hdr.h -o forum
	
clean:
	rm -f *.o forum
