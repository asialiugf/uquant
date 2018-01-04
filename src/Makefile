CC = g++
CPPFLAGS =  -std=c++11  -O2
CFLAGS =  -std=c++11 -O2 -fPIC  -luWS -lssl -lz -lpthread -lcjson -Wunused-result
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
        ../inc/Psqlpool.h \
        ../inc/Roll.h \
        ../inc/File.h \
        ../inc/Json.h \
        ../inc/strategy.h \
        ../inc/uBEE.h

build:  binary

binary: objs exes

exes: $(EXE)main.x \
	$(EXE)dserver.x \
	$(EXE)wserver.x

objs: $(OBJ)Base.o \
	$(OBJ)File.o \
	$(OBJ)Json.o \
	$(OBJ)ErrLog.o \
	$(OBJ)Webserver.o \
	$(OBJ)Dataserver.o \
	$(OBJ)Psqlpool.o \
	$(OBJ)Main.o 

OBJS:= \
	$(OBJ)Base.o \
	$(OBJ)File.o \
	$(OBJ)Json.o \
    $(OBJ)ErrLog.o \
	$(OBJ)Webserver.o \
	$(OBJ)Dataserver.o \
    $(OBJ)Psqlpool.o \
	$(OBJ)Main.o 

MAINOBJS:= \
	$(OBJ)Base.o \
	$(OBJ)File.o \
    $(OBJ)ErrLog.o \
	$(OBJ)Main.o 

DATASERVER:= \
	$(OBJ)Base.o \
	$(OBJ)File.o \
	$(OBJ)Json.o \
    $(OBJ)ErrLog.o \
	$(OBJ)Dataserver.o 

WEBSERVER:= \
	$(OBJ)Base.o \
	$(OBJ)File.o \
    $(OBJ)ErrLog.o \
	$(OBJ)Webserver.o 

$(EXE)main.x: $(MAINOBJS)
	$(CC) $(CPPFLAGS) -o $(EXE)main.x $(MAINOBJS) $(LIBPATH) -luWS -lssl -lz -lpthread

$(EXE)dserver.x: $(MAINOBJS)
	$(CC) $(CPPFLAGS) -o $(EXE)dserver.x $(DATASERVER) $(LIBPATH) -luWS -lssl -lz -lpthread -lcjson

$(EXE)wserver.x: $(MAINOBJS)
	$(CC) $(CPPFLAGS) -o $(EXE)wserver.x $(WEBSERVER) $(LIBPATH) -luWS -lssl -lz -lpthread

$(OBJ)Main.o: $(DEPS) $(SRC)Main.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)Main.o  $(SRC)Main.cpp

$(OBJ)Dataserver.o: $(DEPS) $(SRC)Dataserver.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)Dataserver.o  $(SRC)Dataserver.cpp

$(OBJ)Webserver.o: $(DEPS) $(SRC)Webserver.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)Webserver.o  $(SRC)Webserver.cpp

$(OBJ)Base.o: $(DEPS) $(SRC)Base.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)Base.o  $(SRC)Base.cpp

$(OBJ)File.o: $(DEPS) $(SRC)File.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)File.o  $(SRC)File.cpp

$(OBJ)Json.o: $(DEPS) $(SRC)Json.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)Json.o  $(SRC)Json.cpp

$(OBJ)ErrLog.o: $(DEPS) $(SRC)ErrLog.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)ErrLog.o  $(SRC)ErrLog.cpp

$(OBJ)Psqlpool.o: $(DEPS) $(SRC)Psqlpool.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)Psqlpool.o  $(SRC)Psqlpool.cpp

