#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 6
#  Kyle Zhang
#  kmzhang
#  CSE101
#  pa6
#  May 20, 2020
#
#  make                     makes Order
#  make WordFrequency       makes WordFrequency
#  make clean               removes all binaries
#  make check1              checks WordFrequency for memory leaks
#  make check2              checks Order for memory leaks on in
#------------------------------------------------------------------------------

TOP              = Order
TOP_OBJ          = $(TOP).o
TOP_SRC          = $(TOP).c
ADT              = Dictionary
TEST             = WordFrequency
TEST_OBJ         = $(TEST).o
TEST_SRC         = $(TEST).c
ADT_OBJ          = $(ADT).o
ADT_SRC          = $(ADT).c
ADT_HDR          = $(ADT).h
COMPILE          = gcc -std=c11 -Wall -c 
LINK             = gcc -std=c11 -Wall -o
REMOVE           = rm -f
MEMCHECK         = valgrind --leak-check=full

$(TOP) : $(TOP_OBJ) $(ADT_OBJ)
	$(LINK) $(TOP) $(TOP_OBJ) $(ADT_OBJ)

$(TEST) : $(TEST_OBJ) $(ADT_OBJ)
	$(LINK) $(TEST) $(TEST_OBJ) $(ADT_OBJ)

$(TOP_OBJ) : $(TOP_SRC) $(ADT_HDR)
	$(COMPILE) $(TOP_SRC)

$(TEST_OBJ) : $(TEST_SRC) $(ADT_HDR)
	$(COMPILE) $(TEST_SRC)

$(ADT_OBJ) : $(ADT_SRC) $(ADT_HDR)
	$(COMPILE) $(ADT_SRC)

clean :
	$(REMOVE) $(TOP) $(TOP_OBJ) $(TEST) $(TEST_OBJ) $(ADT_OBJ)

check1 : $(TEST)
	$(MEMCHECK) $(TEST) in out

check2 : $(TOP)
	$(MEMCHECK) $(TOP) in out


