#------------------------------------------------------------------------------
#  Kyle Zhang
#  kmzhang
#  CSE101
#  pa3
#  April 25, 2020
#  Makefile for CMPS 101 Programming Assignment 3
#
#  make                     makes FindPath
#  make GraphTest           makes GraphTest
#  make clean               removes binaries
#  make checkFind           tests FindPath for memory leaks on in3
#  make checkTest           tests GraphTest for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -c -std=c11 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

FindPath : FindPath.o $(BASE_OBJECTS)
	$(LINK) FindPath FindPath.o $(BASE_OBJECTS)

GraphTest : GraphTest.o $(BASE_OBJECTS)
	$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

FindPath.o : FindPath.c $(HEADERS)
	$(COMPILE) FindPath.c

GraphTest.o : GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) FindPath GraphTest FindPath.o GraphTest.o $(BASE_OBJECTS)

checkFind : FindPath
	$(MEMCHECK) FindPath in out

checkClient : GraphTest
	$(MEMCHECK) GraphTest
