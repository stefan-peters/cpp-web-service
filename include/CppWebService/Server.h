#ifndef CPPWEBSERVICE_SERVER_H
#define CPPWEBSERVICE_SERVER_H

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

struct mg_connection;
struct mg_context;

struct Connection {
    Connection(mg_connection*) {}
};

class Server {

public:

    struct Option {

        enum Type {
            UNKNOWN = 0x0,
            NUMBER = 0x1,
            STRING = 0x2,
            FILE = 0x3,
            DIRECTORY = 0x4,
            BOOLEAN = 0x5,
            EXT_PATTERN = 0x6
        };

        Type getType() const;

        static std::vector<Option> all();

        std::string name;
        std::string value;
    };

    struct Exception : public std::runtime_error  {
        Exception(const std::string &msg) : std::runtime_error(msg) {}
    };

    Server(std::vector<std::string> options = std::vector<std::string>());
    virtual ~Server();

    /**
     * its not allowed to copy the object, because the address of the object
     * is internally coupled to the civetweb structures
     */
    Server(const Server& other) = delete;

    void close();
    bool listen();

    bool isListening() const;
    std::vector<int> getListeningPorts() const;


    virtual int on_begin_request(Connection connection) {}

    virtual void on_end_request(const Connection connection,
                        int reply_status_code) const {}

    virtual int on_log_message(const Connection connection, const char *message) {}

    virtual int on_log_access(const Connection connection, const char *message) {}

    virtual int on_init_ssl(void *ssl_context, void *user_data) {}

    virtual void on_connection_close(const Connection connection) {}

    virtual const char *on_open_file(const Connection connection, const char *path,
                             size_t *data_len) {}

    virtual void on_init_lua(const Connection connection, void *lua_context) {}

    virtual void on_upload(Connection connection, const char *file_name) {}

    virtual int on_http_error(Connection connection, int status) {}

    virtual void on_init_context(const struct mg_context *ctx) {}

    virtual void on_exit_context(const struct mg_context *ctx) {}


private:
    mg_context* _context;
    std::vector<std::string> _options;
};

#endif