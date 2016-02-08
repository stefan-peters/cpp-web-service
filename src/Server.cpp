#include "Server.h"
#include <civetweb.h>

using namespace std;

namespace {

    inline Server *server(mg_context *context) {
        return static_cast<Server *>(mg_get_user_data(context));
    }

    inline const Server *server(const mg_context *context) {
        return static_cast<const Server *>(mg_get_user_data(context));
    }

    inline Server *server(mg_connection *connection) {
        return server(mg_get_context(connection));
    }

    inline const Server *server(const mg_connection *connection) {
        return server(mg_get_context(connection));
    }


    int _callback_begin_request(struct mg_connection *connection) {
        server(connection)->on_begin_request(connection);
    }

    void _callback_end_request(const struct mg_connection *connection,
                               int reply_status_code) {
        server(connection)
                ->on_end_request(const_cast<mg_connection *>(connection),
                                 reply_status_code);
    }

    int _callback_log_message(const struct mg_connection *, const char *message) { }

    int _callback_log_access(const struct mg_connection *, const char *message) { }

    int _callback_init_ssl(void *ssl_context, void *user_data) { }

    void _callback_connection_close(const struct mg_connection *) { }

    const char *_callback_open_file(const struct mg_connection *, const char *path,
                                    size_t *data_len) { }

    void _callback_init_lua(const struct mg_connection *, void *lua_context) { }

    void _callback_upload(struct mg_connection *, const char *file_name) { }

    int _callback_http_error(struct mg_connection *, int status) { }

    void _callback_init_context(const struct mg_context *ctx) { }

    void _callback_exit_context(const struct mg_context *ctx) { }

    struct mg_callbacks _callbacks = {
            &_callback_begin_request, &_callback_end_request,
            &_callback_log_message, &_callback_log_access,
            &_callback_init_ssl, &_callback_connection_close,
            &_callback_open_file, &_callback_init_lua,
            &_callback_upload, &_callback_http_error,
            &_callback_init_context, &_callback_exit_context};
}


Server::Server(vector<string> options) : _context(nullptr), _options(options) {

}


Server::~Server() {
    close();
}


void Server::close() {

    if(_context) {
        mg_stop(_context);
        _context = nullptr;
    }
}

bool Server::listen() {

    if(_context) {
        throw Exception("called listen() on a already running server");
    }

    vector<const char *> c_options(_options.size());

    for (auto option : _options) {
        c_options.push_back(option.c_str());
    }

    c_options.push_back('\0');

    _context = mg_start(&_callbacks, this, c_options.data());

    return isListening();
}


bool Server::isListening() const {
    return _context != nullptr;
}


std::vector<int> Server::getListeningPorts() const {

    const int SIZE = 64;

    std::vector<int> ports(SIZE);
    std::vector<int> ssl(SIZE);

    ports.resize(mg_get_ports(_context, ports.size(), &ports[0], &ssl[0]));

    return ports;
}