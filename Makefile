CC = g++

make: 
	$(CC) main.cpp -o test

clean:
	rm -f test.o
