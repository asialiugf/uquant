#include "uBEE.h"
#include <thread>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>

extern char **environ;
int ForkApi();
int ForkBck();
int ForkCtp();
int ForkSim();
int main(int argc, char **argv)
{

  int rtn;
  int pid;
  uBEE::Daemon(1,0) ;

  pid = getpid();

  uBEE::SaveArgv(argc,argv);
  uBEE::InitSetProcTitle();
  uBEE:: SetProcTitle("AAA","DataServer:");

  rtn = ForkApi();
  sleep(1);
  rtn = ForkBck();
  sleep(1);
  rtn = ForkCtp();
  sleep(1);
  rtn = ForkSim();
  sleep(1);

  while(true) {
    sleep(100);
  }

}

int ForkApi()
{
  int rc;
  int pid;
  int i = 0;
  char ca_futures[1024];
  pid = fork();
  uBEE::HubApi hub;
  switch(pid) {
  case -1:
    return -1;

  case 0:
    pid = getpid();
    uBEE::InitSetProcTitle();
    uBEE:: SetProcTitle("HubApi","AAA :");
    hub.Init();
    hub.Start();
    break;
  default:
    break;
  }
  return 0;
}

int ForkBck()
{
  int rc;
  int pid;
  int i = 0;
  pid = fork();
  uBEE::HubBck hub;
  switch(pid) {
  case -1:
    return -1;

  case 0:
    pid = getpid();
    uBEE::InitSetProcTitle();
    uBEE:: SetProcTitle("HubBck:","AAA :");
    hub.Init();
    hub.Start();
    break;
  default:
    break;
  }
  return 0;
}

int ForkCtp()
{
  int rc;
  int pid;
  pid = fork();

  switch(pid) {
  case -1:
    return -1;
  case 0: {
    const char *brMsg = "This will be broadcasted!";
    size_t brMsgLength = strlen(brMsg);
    uBEE::HubCtp hub;
    pid = getpid();
    uBEE::InitSetProcTitle();
    uBEE:: SetProcTitle("HubCtp:","AAA :");
    hub.Init();
    sleep(2);

    std::thread t([&hub,&brMsg,&brMsgLength] {
      while(1)
      {
        std::cout << " will broadcast !! " << std::endl;
        hub.sg->broadcast(brMsg, brMsgLength, uWS::OpCode::TEXT);
        sleep(1);
      }
    });  /* thread t */
    t.detach();
    hub.Start();

    break;
  }
  default:
    break;
  }
  return 0;
}

int ForkSim()
{
  int rc;
  int pid;
  int i = 0;
  pid = fork();
  uBEE::HubSim hub;
  switch(pid) {
  case -1:
    return -1;

  case 0:
    pid = getpid();
    uBEE::InitSetProcTitle();
    uBEE:: SetProcTitle("HubSim:","AAA :");
    hub.Init();
    hub.Start();
    break;
  default:
    break;
  }
  return 0;
}
