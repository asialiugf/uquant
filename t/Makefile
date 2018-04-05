CCFLAGS =  -std=c++11 -O3 -fPIC  -luWS -lssl -lz -lpthread -lcjson -Wunused-result
LIBPATH = -L/home/riddle/uws -L ./ -L ../../u/lib -L ../lib/seetalib-1.0.0/lib

ALLLIBS = -luBEE -luWS -lssl -lz -lpthread -lcjson -lpq -lsee_talib

CTPLIBS:= ../ctp/thostmduserapi.so \
        ../ctp/thosttraderapi.so

EXE = ../../u/exe/

SRC = ./
INC = ../inc/
OBJ = ../../u/obj/

INCS = -I ../inc -I ./ \
       -I ../lib/seetalib-1.0.0/include \
       -I /usr/include \
       -I /usr/local/include \
	   -I /usr/include/postgresql

default:  exes

exes: $(EXE)main.x \

MAINOBJS:= \
	$(OBJ)Main.o \
	$(OBJ)Index.o 

$(EXE)main.x: $(MAINOBJS)
	$(CXX) $(CCFLAGS) -o $(EXE)main.x $(MAINOBJS) $(LIBPATH) $(ALLLIBS) $(CTPLIBS)

$(OBJ)Main.o: $(SRC)Main.cpp
	$(CXX) -c $(CCFLAGS) $(INCS) -o $(OBJ)Main.o  $(SRC)Main.cpp

$(OBJ)Index.o: $(SRC)Index.cpp
	$(CXX) -c $(CCFLAGS) $(INCS) -o $(OBJ)Index.o  $(SRC)Index.cpp
