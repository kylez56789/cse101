#------------------------------------------------------------------------------
# Kyle Zhang
# kmzhang
# CSE101
# pa2
# March 31, 2019
# Makefile
# Description - Makefile for CSE 101 Programming Assignment 2
#
#       make                   makes Arithmetic
#       make ListTest          makes ListTest
#       make BigIntegerTest    makes BigIntegerTest
#------------------------------------------------------------------------------

Arithmetic: Arithmetic.o BigInteger.o List.o
	gcc -o Arithmetic Arithmetic.o BigInteger.o List.o

Arithmetic.o : Arithmetic.c BigInteger.h List.h
	gcc -c -std=c99 -Wall Arithmetic.c

BigIntegerTest: BigIntegerTest.o BigInteger.o List.o
	gcc -o BigIntegerTest BigIntegerTest.o BigInteger.o List.o

BigIntegerTest.o: BigIntegerTest.c BigInteger.h List.h
	gcc -c -std=c99 -Wall BigIntegerTest.c

BigInteger.o : BigInteger.c List.h
	gcc -c -std=c99 -Wall BigInteger.c

ListTest: ListTest.o List.o
	gcc -std=c11 -Wall -o ListTest ListTest.o List.o

ListTest.o : ListTest.c List.h
	gcc -c -std=c99 -Wall ListTest.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f Arithmetic BigIntegerTest ListTest ListTest.o BigIntegerTest.o Arithmetic.o BigInteger.o List.o

memcheck :
	valgrind --leak-check=full --show-leak-kinds=all Arithmetic in3 out
