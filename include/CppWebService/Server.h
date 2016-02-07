#ifndef CPPWEBSERVICE_SERVER_H
#define CPPWEBSERVICE_SERVER_H

struct mg_connection;
struct mg_context;


struct Connection {

    Connection(mg_connection *connection);


private:
    mg_connection *_connection;
};

#endif