#ifndef PGBACKEND_H
#define PGBACKEND_H

#include <memory>
#include <mutex>
#include <string>
#include <queue>
#include <condition_variable>
#include <libpq-fe.h>
//#include "pgconnection.h"

class PGConnection
{
public:
    PGConnection();

    std::shared_ptr<PGconn> connection() const;

private:
    void establish_connection();

    const char* m_dbhost = "localhost";
    const char* m_dbport = "5432";
    const char* m_dbname = "demo";
    const char* m_dbuser = "postgres";
    const char* m_dbpass = "postgres";

    std::shared_ptr<PGconn>  m_connection;

};

class PGBackend
{
public:
    PGBackend();
    std::shared_ptr<PGConnection> connection();
    void freeConnection(std::shared_ptr<PGConnection>);

private:
    void createPool();
    
    std::mutex m_mutex;
    std::condition_variable m_condition;
    std::queue<std::shared_ptr<PGConnection>> m_pool;

    const int POOL = 10;


};

#endif //PGBACKEND_H
