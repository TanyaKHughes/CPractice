# Makefile for my C practice project; the makefile goes in the same directory as the 
# code; the object files go to a sister directory, as does the executable.

SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .c .o .h

# I couldn't get this path searching thing to work.??
#vpath %.o ../Obj
#VPATH = ../Obj:../Exe

CC = clang

# object directory
odir = ../Obj

# executable directory
edir = ../Exe

objects = main.o temperatures.o binarySearch.o cref.o intList.o crTree.o

# Adds the odir in front of each object file
_objects = $(patsubst %, $(odir)/%, $(objects))

capp : $(objects)
	$(CC) -Wall $(_objects) -o $(edir)/capp -g 

main.o : main.c temperatures.h binarySearch.h cref.h
	$(CC) -Wall -c main.c -o $(odir)/main.o -g

cref.o : cref.c cref.h intList.h crTree.h
	$(CC) -Wall -c cref.c -o $(odir)/cref.o -g

crTree.o : crTree.c crTree.h intList.h
	$(CC) -Wall -c crTree.c -o $(odir)/crTree.o -g

intList.o : intList.c intList.h
	$(CC) -Wall -c intList.c -o $(odir)/intlist.o -g

binarySearch.o : binarySearch.c binarySearch.h
	$(CC) -Wall -c binarySearch.c -o $(odir)/binarySearch.o -g

temperatures.o : temperatures.c temperatures.h
	$(CC) -Wall -c temperatures.c -o $(odir)/temperatures.o -g

.PHONY : clean
clean :
	rm $(edir)/capp $(_objects)
