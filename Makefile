CC = g++
CFLAGS = -Wall -g

main: cpu.o main_class.o  main.o
	$(CC) $(CFLAGS) -o main main_class.o main.o cpu.o

cpu.o: cpu.cc traits.h cpu.h
	$(CC) $(CFLAGS) -c cpu.cc 

main_class.o: main_class.cc main_class.h cpu.h traits.h
	$(CC) $(CFLAGS) -c main_class.cc

main.o: main.cc main_class.h cpu.h system.h
	$(CC) $(CFLAGS) -c main.cc 

debug.o: debug.cc debug.h traits.h
	$(CC) $(CFLAGS) -c debug.cc

clean:
	rm -f main *.o