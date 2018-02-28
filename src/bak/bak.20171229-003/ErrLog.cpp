#include "errlog.h"

#include <ctype.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

namespace uBEE
{

static char LOG_FILE_NAME[100]= {"./errlog"} ;
static int MAX_BAK_LOG_SIZE = 20*1024*1024 ;

// int chglog(char cChgCode,char *pcChgStr);
int ErrLog(int iErrCode,char const*message,char device,char const*buf,long length);
void disp_errmsg(int iFileId,char const*message,char const*buf,long length);
void mem_dump(int iFileId,char const*buf,long length);
void DumpHex(int ifile,char const*buf, int len) ;
void DumpLine(int ifile,int addr, char const*buf, int len) ;


int ErrLog(int iErrCode, char const*message, char device, char const*buf, long length)
{
  int iRc = 0 ;
  int iTtyDev,iUcpErLog,iConsole;
  int iRetry;
  int iFileSize;
  char caLogBakFileName[80];

  if((iErrCode < 999) && (iErrCode > 0)) {
    return(0);
  }

  /* output to logfile */
  if(device & RPT_TO_LOG) {
    iRetry=0;
    while((iUcpErLog=open(LOG_FILE_NAME,O_WRONLY | O_CREAT,0777)) == -1) {
      sleep(1);
      if((iRetry ++) > MAX_OPEN_RETRY) {
        printf("errlog.c: fatal error occured !!! error_no is %d\n",errno);
        printf("errlog: %s CANNOT OPEN FOR ERROR LOG !!!\n",LOG_FILE_NAME);
        /* exit(1);*/
      }
    }

    iRetry=0;
    while(lockf(iUcpErLog,F_LOCK,0) == -1) {
      sleep(1);
      if((iRetry ++) > 10) {
        printf("errlog.c: fatal error occured !!! error_no is %d\n",errno);
        printf("errlog:CANNOT LOCK ERROR_LOG %s !!!\n",LOG_FILE_NAME);
        /* exit(1);*/
      }
    }

    if((iFileSize = lseek(iUcpErLog,0,SEEK_END)) ==-1) {
      printf("errlog.c: fatal error occured !!! error_no is %d\n",errno);
      printf("errlog: %s CANNOT JUMP TO END OF FILE !!!\n",LOG_FILE_NAME);
      /* exit(1);*/
    }

    if(iErrCode == NO_ERR) {
      write(iUcpErLog,"@MSG:",5);
      write(iUcpErLog,message,strlen(message));
      write(iUcpErLog,LOG_MSG_SEPERATE,LOG_SEPERATE_LEN);
    } else {
        disp_errmsg(iUcpErLog,message,buf,length);
    }

    if(iFileSize >= MAX_BAK_LOG_SIZE) {
      memset(caLogBakFileName, 0, 80);
      strcpy(caLogBakFileName, LOG_FILE_NAME);
      strcat(caLogBakFileName,(char *) ".bak");

      if((iRc = rename(LOG_FILE_NAME, caLogBakFileName)) < 0) {
        printf("cmserhdl.c: fatal error occured !!! iRc= %d error_no is %d\n"
               ,iRc,errno);
        printf("errlog: %s CANNOT BE RENAMED !!!\n",LOG_FILE_NAME);
      }
    }
    close(iUcpErLog);
  } /* for if (device & RPT_TO_LOG )  */

  if(device & RPT_TO_TTY) {      /* output to tty */
    iTtyDev = 1;
    if(iErrCode == NO_ERR) {
      write(iTtyDev,"@MSG:",5);
      write(iTtyDev,message,strlen(message));
      write(iTtyDev,LOG_MSG_SEPERATE,LOG_SEPERATE_LEN);
    } else {
        disp_errmsg(iTtyDev,message,buf,length);
    }
  }

  if(device & RPT_TO_CON) {      /* output to console */
    if((iConsole=open(CONSOLE,O_WRONLY)) == -1) {
      printf("errlog.c: fatal error occured !!! \n");
      printf("CONSOLE %s CANNOT OPEN FOR ERROR LOG !!!\n",CONSOLE);
      /* exit(1);*/
    } else {
      if(iErrCode == NO_ERR) {
        write(iConsole,"@MSG:",5);
        write(iConsole,message,strlen(message));
        write(iConsole,LOG_MSG_SEPERATE,LOG_SEPERATE_LEN);
      } else {
          disp_errmsg(iConsole,message,buf,length);
      }
      close(iConsole);
    }
  }
  return iRc ;
}


void
disp_errmsg(int iFileId,char const*message,char const*buf,long length)
{
  long lTLoc;
  long lCurTime;
  char caStrBuf[300];

  (lCurTime) = time(&lTLoc);
  memset(caStrBuf,'0',300);
  sprintf(caStrBuf,"^(oo)^|%d|%d|%.24s\n<mark>:%s\n",
          getpid(),1000,ctime(&lCurTime),message);
  write(iFileId,caStrBuf,strlen(caStrBuf));

  /* dump memory to fd */
  if((buf != 0)&&(length > 0)) {
    // mem_dump(iFileId,buf,length);
    DumpHex(iFileId,buf,length);
  }
  write(iFileId,"\n",1);
}


void
mem_dump(int iFileId,char const*buf,long length)
{
  write(iFileId,buf,length);
} /* end of mem_dump   */

void DumpLine(int ifile,int addr, char const*buf, int len)
{
  int i, pos;
  char line[80+1];

  // Address field
  pos = sprintf(line, "%08X ", addr);

  // Hex content
  for(i = 0; i < 16; ++i) {
    if(i % (16/2) == 0) {
      line[pos++] = ' '; // Insert a space
    }

    if(i < len) {
      pos += sprintf(&line[pos], "%02x ", buf[i]);
    } else {
      pos += sprintf(&line[pos], "   ");
    }
  }
  pos += sprintf(&line[pos], "  |");

  // Printable content
  for(i = 0; i < len; ++i) {
    line[pos++] = isprint(buf[i]) ? buf[i] : '.';
  }

  sprintf(&line[pos], "|\n");
//  fprintf(stderr, "%s", line);
  write(ifile,line,strlen(line)) ;

}

void DumpHex(int ifile, char const* buf, int len)
{
  int i;
  for(i = 0; i < (len/16); ++i) {
    DumpLine(ifile, 16*i, &buf[16*i], 16);
  }
  // Dump remaining which len is not 16
  if(len % 16 != 0) {
    DumpLine(ifile, 16*i, &buf[16*i], len % 16);
  }
}
} //end namespace