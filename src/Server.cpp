#include "Server.h"
#include <civetweb.h>


Connection::Connection(mg_connection *connection) : _connection(connection) {}


struct Server {
    Server() {}

    int on_begin_request(Connection connection) {}

    void on_end_request(const Connection connection,
                        int reply_status_code) const {}

    int on_log_message(const Connection connection, const char *message) {}

    int on_log_access(const Connection connection, const char *message) {}

    int on_init_ssl(void *ssl_context, void *user_data) {}

    void on_connection_close(const Connection connection) {}

    const char *on_open_file(const Connection connection, const char *path,
                             size_t *data_len) {}

    void on_init_lua(const Connection connection, void *lua_context) {}

    void on_upload(Connection connection, const char *file_name) {}

    int on_http_error(Connection connection, int status) {}

    void on_init_context(const struct mg_context *ctx) {}

    void on_exit_context(const struct mg_context *ctx) {}

private:
    mg_context *_context;
};

// inline Connection *connection(mg_connection *connection) {
//  return static_cast<Connection *>(mg_get_user_connection_data(connection));
//}

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

int _callback_log_message(const struct mg_connection *, const char *message) {}

int _callback_log_access(const struct mg_connection *, const char *message) {}

int _callback_init_ssl(void *ssl_context, void *user_data) {}

void _callback_connection_close(const struct mg_connection *) {}

const char *_callback_open_file(const struct mg_connection *, const char *path,
                                size_t *data_len) {}

void _callback_init_lua(const struct mg_connection *, void *lua_context) {}

void _callback_upload(struct mg_connection *, const char *file_name) {}

int _callback_http_error(struct mg_connection *, int status) {}

void _callback_init_context(const struct mg_context *ctx) {}

void _callback_exit_context(const struct mg_context *ctx) {}

struct mg_callbacks _callbacks = {
        &_callback_begin_request, &_callback_end_request,
        &_callback_log_message,   &_callback_log_access,
        &_callback_init_ssl,      &_callback_connection_close,
        &_callback_open_file,     &_callback_init_lua,
        &_callback_upload,        &_callback_http_error,
        &_callback_init_context,  &_callback_exit_context};

