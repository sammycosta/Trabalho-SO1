CC = g++
CFLAGS = -Wall -g

main: cpu.o main_class.o main.o debug.o system.o thread.o
	$(CC) $(CFLAGS) -o main main_class.o main.o cpu.o debug.o system.o thread.o

cpu.o: cpu.cc traits.h cpu.h
	$(CC) $(CFLAGS) -c cpu.cc 

main_class.o: main_class.cc main_class.h cpu.h traits.h
	$(CC) $(CFLAGS) -c main_class.cc

main.o: main.cc main_class.h cpu.h system.h
	$(CC) $(CFLAGS) -c main.cc 

debug.o: debug.cc debug.h traits.h
	$(CC) $(CFLAGS) -c debug.cc

system.o: system.cc traits.h
	$(CC) $(CFLAGS) -c system.cc

thread.o: thread.cc thread.h traits.h list.h
	$(CC) $(CFLAGS) -c thread.cc

semaphore.o: semaphore.cc semaphore.h traits.h thread.h
	$(CC) $(CFLAGS) -c semaphore.cc

clean:
	rm -f main *.o