
# Cody Barnson
# Thur Mar 31, 2016
# Makefile for allegro game project

# declaration of variables
CC = g++
CCFLAGS = -Wall -g -std=c++11 -I/usr/include/allegro5

# file names
NONTEST = main.cc main.o

SOURCES = $(filter-out $(NONMAIN), $(wildcard *.cc))
OBJECTS = $(SOURCES:.cc=.o)

LIBDIR = -L/usr/lib/x86_64-linux-gnu

LNFLAGS = -lallegro -lallegro_primitives -lallegro_image -lallegro_font \
-lallegro_ttf
LNFLAGST= -lallegro -lallegro_primitives -lallegro_image -lallegro_font \
-lallegro_ttf -ldl -lcppunit


# main target
all: main

main: $(OBJECTS)
	$(CC) $(LIBDIR) -o $@ $^ $(LNFLAGS)

# pull in dependency info for existing .o files
-include $(OBJECTS:.o=.d) $(OBJECTST:.o=.d)

# compile and generate dependency info
%.o: %.cc
	$(CC) -c $(CCFLAGS) $< -o $@
	$(CC) -M $(CCFLAGS) $*.cc > $*.d

# automatic variables
# $< contains the first dependency file name
# $@ contains the target file name

# phony targets --> avoid conflict with file of the same name, and
#                   improve performance
.PHONY: clean

# clean out the directory but keep executables with command "clean"
clean : 
	rm -f *~ *.o *.d *.gch main




