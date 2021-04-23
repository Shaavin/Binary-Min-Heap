a.out:
	g++ -std=c++11 myBinaryMinHeap.hpp
	g++ -std=c++11 test_main.cpp
	./a.out inputs/instance1.txt output.txt

clean:
	rm a.out *.gch output.txt
