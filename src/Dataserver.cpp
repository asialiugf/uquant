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
int main(int argc, char **argv)
{

  int rtn;
  int pid;
  uBEE::Daemon(1,0) ;

  pid = getpid();

  uBEE::SaveArgv(argc,argv);
  uBEE::InitSetProcTitle();
  uBEE:: SetProcTitle("=======","dataApi :");

  rtn = ForkApi();

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
  uBEE::ApiHub AH;
  switch(pid) {
  case -1:
    return -1;

  case 0:
    pid = getpid();
    //uBEE::SaveArgv(argc,argv);
    uBEE::InitSetProcTitle();
    uBEE:: SetProcTitle("=======","AAA :");


    AH.Start();
    break;
  default:
    break;
  }
  return 0;
}
