bin/testListArray: testListArray.cpp ListArray.h List.h
	mkdir -p bin
	g++ -std=gnu++17 -Wall -Wextra -O2 -o bin/testListArray testListArray.cpp

clean:
	rm -rf *.o *.gch bin

