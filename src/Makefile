CC = g++
CPPFLAGS =  -std=c++11  -O2
CFLAGS =  -std=c++11 -O2 -fPIC  -luWS -lssl -lz -lpthread -Wunused-result
LIBPATH = -L/home/riddle/uws 
LINK =  $(CC)

EXE = ../../u/exe/

SRC = ../src/
OBJ = ../../u/obj/

INCS = -I ../inc \
       -I /usr/include \
       -I /usr/local/include \
	   -I /usr/include/postgresql

DEPS = ../inc/Base.h \
	    ../inc/Echo.h  \
	    ../inc/ErrLog.h \
        ../inc/Psqlconn.h \
        ../inc/Roll.h \
        ../inc/strategy.h \
        ../inc/uBEE.h

build:  binary

binary: objs exes

exes: $(EXE)main.x \
	$(EXE)webs.a \
	$(EXE)web.s

objs: $(OBJ)Base.o \
	$(OBJ)ErrLog.o \
	$(OBJ)Psqlconn.o \
	$(OBJ)Main.o 

OBJS:= \
	$(OBJ)Base.o \
    $(OBJ)ErrLog.o \
    $(OBJ)Psqlconn.o \
	$(OBJ)Main.o 

MAINOBJS:= \
	$(OBJ)Base.o \
    $(OBJ)ErrLog.o \
	$(OBJ)Main.o 

$(EXE)main.x: $(MAINOBJS)
	$(CC) $(CPPFLAGS) -o $(EXE)main.x $(MAINOBJS) $(LIBPATH) -luWS -lssl -lz -lpthread

$(OBJ)Main.o: $(DEPS) $(SRC)Main.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)Main.o  $(SRC)Main.cpp

$(OBJ)Base.o: $(DEPS) $(SRC)Base.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)Base.o  $(SRC)Base.cpp

$(OBJ)ErrLog.o: $(DEPS) $(SRC)ErrLog.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)ErrLog.o  $(SRC)ErrLog.cpp

$(OBJ)Psqlconn.o: $(DEPS) $(SRC)Psqlconn.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)Psqlconn.o  $(SRC)Psqlconn.cpp

