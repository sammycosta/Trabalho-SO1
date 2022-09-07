CC = g++
CFLAGS = -Wall -g

main: main_class.cc main_class.h cpu.o main.cc
	$(CC) $(CFLAGS) -o main main_class.cc main.cc cpu.o

cpu.o: cpu.cc traits.h cpu.h
	$(CC) $(CFLAGS) -c cpu.cc 

clean:
	rm -f main *.o