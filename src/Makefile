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
	    ../inc/Echo.h \
	    ../inc/Title.h \
	    ../inc/ErrLog.h \
	    ../inc/Daemon.h \
	    ../inc/HubCtp.h \
	    ../inc/HubApi.h \
	    ../inc/HubSim.h \
	    ../inc/HubBck.h \
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
	$(EXE)tqdata.x \
	$(EXE)wserver.x

objs: $(OBJ)Base.o \
	$(OBJ)File.o \
	$(OBJ)Json.o \
	$(OBJ)Title.o \
	$(OBJ)ErrLog.o \
	$(OBJ)Daemon.o \
	$(OBJ)HubApi.o \
	$(OBJ)HubCtp.o \
	$(OBJ)HubSim.o \
	$(OBJ)HubBck.o \
	$(OBJ)Webserver.o \
	$(OBJ)Dataserver.o \
	$(OBJ)Tqdata.o \
	$(OBJ)Psqlpool.o \
	$(OBJ)Main.o 

OBJS:= \
	$(OBJ)Base.o \
	$(OBJ)File.o \
	$(OBJ)Json.o \
	$(OBJ)Title.o \
    $(OBJ)ErrLog.o \
    $(OBJ)Daemon.o \
    $(OBJ)HubApi.o \
	$(OBJ)HubCtp.o \
	$(OBJ)HubSim.o \
	$(OBJ)HubBck.o \
	$(OBJ)Webserver.o \
	$(OBJ)Dataserver.o \
	$(OBJ)Tqdata.o \
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
    $(OBJ)Title.o \
    $(OBJ)ErrLog.o \
    $(OBJ)Daemon.o \
    $(OBJ)HubApi.o \
	$(OBJ)HubCtp.o \
	$(OBJ)HubSim.o \
	$(OBJ)HubBck.o \
	$(OBJ)Dataserver.o 

TQDATA:= \
	$(OBJ)Base.o \
	$(OBJ)File.o \
	$(OBJ)Json.o \
    $(OBJ)ErrLog.o \
	$(OBJ)Tqdata.o 

WEBSERVER:= \
	$(OBJ)Base.o \
	$(OBJ)File.o \
    $(OBJ)ErrLog.o \
	$(OBJ)Webserver.o 

$(EXE)main.x: $(MAINOBJS)
	$(CC) $(CPPFLAGS) -o $(EXE)main.x $(MAINOBJS) $(LIBPATH) -luWS -lssl -lz -lpthread

$(EXE)dserver.x: $(MAINOBJS)
	$(CC) $(CPPFLAGS) -o $(EXE)dserver.x $(DATASERVER) $(LIBPATH) -luWS -lssl -lz -lpthread -lcjson

$(EXE)tqdata.x: $(MAINOBJS)
	$(CC) $(CPPFLAGS) -o $(EXE)tqdata.x $(TQDATA) $(LIBPATH) -luWS -lssl -lz -lpthread -lcjson

$(EXE)wserver.x: $(MAINOBJS)
	$(CC) $(CPPFLAGS) -o $(EXE)wserver.x $(WEBSERVER) $(LIBPATH) -luWS -lssl -lz -lpthread

$(OBJ)Main.o: $(DEPS) $(SRC)Main.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)Main.o  $(SRC)Main.cpp

$(OBJ)HubApi.o: $(DEPS) $(SRC)HubApi.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)HubApi.o  $(SRC)HubApi.cpp

$(OBJ)HubCtp.o: $(DEPS) $(SRC)HubCtp.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)HubCtp.o  $(SRC)HubCtp.cpp

$(OBJ)HubSim.o: $(DEPS) $(SRC)HubSim.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)HubSim.o  $(SRC)HubSim.cpp

$(OBJ)HubBck.o: $(DEPS) $(SRC)HubBck.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)HubBck.o  $(SRC)HubBck.cpp

$(OBJ)Dataserver.o: $(DEPS) $(SRC)Dataserver.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)Dataserver.o  $(SRC)Dataserver.cpp

$(OBJ)Tqdata.o: $(DEPS) $(SRC)Tqdata.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)Tqdata.o  $(SRC)Tqdata.cpp

$(OBJ)Webserver.o: $(DEPS) $(SRC)Webserver.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)Webserver.o  $(SRC)Webserver.cpp

$(OBJ)Base.o: $(DEPS) $(SRC)Base.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)Base.o  $(SRC)Base.cpp

$(OBJ)File.o: $(DEPS) $(SRC)File.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)File.o  $(SRC)File.cpp

$(OBJ)Json.o: $(DEPS) $(SRC)Json.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)Json.o  $(SRC)Json.cpp

$(OBJ)Title.o: $(DEPS) $(SRC)Title.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)Title.o  $(SRC)Title.cpp

$(OBJ)ErrLog.o: $(DEPS) $(SRC)ErrLog.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)ErrLog.o  $(SRC)ErrLog.cpp

$(OBJ)Daemon.o: $(DEPS) $(SRC)Daemon.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)Daemon.o  $(SRC)Daemon.cpp

$(OBJ)Psqlpool.o: $(DEPS) $(SRC)Psqlpool.cpp
	$(CC) -c $(CPPFLAGS) $(INCS) -o $(OBJ)Psqlpool.o  $(SRC)Psqlpool.cpp

