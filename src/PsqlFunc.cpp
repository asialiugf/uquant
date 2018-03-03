#include <iostream>
#include <thread>
#include <fstream>
#include <sstream>
#include "Psqlpool.h"
#include "PsqlFunc.h"
#include <iostream>
#include <string.h>

namespace uBEE
{


void createBarTable(std::shared_ptr<uBEE::DBPool> dbpool,const char * future, const char * period)
{
  auto conn = dbpool->getDBConn();
  PGresult   *res;
  PGconn     *connx;
  connx = conn->getConn().get() ;

  char       ca_state[4096];
  memset(ca_state,'\0',4096);

  const unsigned char strSrc[]="\
  datetime        VARCHAR(10) NOT NULL,\
  serials         VARCHAR UNIQUE NOT NULL,\
  high            DOUBLE PRECISION NOT NULL,\
  open            DOUBLE PRECISION NOT NULL,\
  close		      DOUBLE PRECISION NOT NULL,\
  low		      DOUBLE PRECISION NOT NULL,\
  open_oi	      DOUBLE PRECISION NOT NULL,\
  close_oi        DOUBLE PRECISION NOT NULL,\
  volume          DOUBLE PRECISION NOT NULL,\
  PRIMARY KEY(datetime)\
  ";

  sprintf(ca_state,"CREATE TABLE BAR_%s_%s(%s); ",future,period,strSrc);
  std::cout << ca_state << std::endl;

  res = PQexec(connx, ca_state);
  if(PQresultStatus(res) != PGRES_COMMAND_OK) {
    fprintf(stderr, " BEGIN command failed: %s", PQerrorMessage(connx));
    PQclear(res);
    //exit_nicely(connx);
    PQfinish(connx);
    exit(1);
  }
  PQclear(res);

  dbpool->freeDBConn(conn);
}

void createTickTable(std::shared_ptr<uBEE::DBPool> dbpool,const char * future)
{
  auto conn = dbpool->getDBConn();
  PGresult   *res;
  PGconn     *connx;
  connx = conn->getConn().get() ;

  char       ca_state[4096];
  memset(ca_state,'\0',4096);

  const unsigned char strSrc[]="\
  datetime        VARCHAR(10) NOT NULL,\
  millisecond     VARCHAR(10) NOT NULL,\
  serials         VARCHAR UNIQUE NOT NULL,\
  trading_day     VARCHAR(10),\
  highest         DOUBLE PRECISION NOT NULL,\
  lowest          DOUBLE PRECISION NOT NULL,\
  last_price      DOUBLE PRECISION NOT NULL,\
  ask_price1      DOUBLE PRECISION NOT NULL,\
  ask_volume1     DOUBLE PRECISION NOT NULL,\
  bid_price1      DOUBLE PRECISION NOT NULL,\
  bid_volume1     DOUBLE PRECISION NOT NULL,\
  open_interest   DOUBLE PRECISION NOT NULL,\
  volume          DOUBLE PRECISION NOT NULL,\
  PRIMARY KEY(datetime, ms)\
  ";
  sprintf(ca_state,"CREATE TABLE TICK_%s(%s); ",future,strSrc);
  std::cout << ca_state << std::endl;

  /*
  res = PQexec(connx, ca_state);
  if(PQresultStatus(res) != PGRES_COMMAND_OK) {
    fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(connx));
    PQclear(res);
    //exit_nicely(connx);
    PQfinish(connx);
    exit(1);
  }
  PQclear(res);
  */
  dbpool->freeDBConn(conn);
}

} //end namesapce
