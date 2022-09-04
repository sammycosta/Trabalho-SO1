CC = g++
CFLAGS = -Wall -g

main: main_class.cc main_class.h cpu.cc cpu.h traits.h
	$(CC) $(CFLAGS) -o main main_class.cc main_class.h cpu.cc cpu.h traits.h
