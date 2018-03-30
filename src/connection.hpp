#ifndef HTTP_CONNECTION_HPP
#define HTTP_CONNECTION_HPP

#include "reply.hpp"
#include "request.hpp"
#include "request_handler.hpp"
#include "request_parser.hpp"
#include "route_manager.hpp"
#include <array>
#include <boost/asio.hpp>
#include <memory>

namespace http {
    namespace server {

        class connection_manager;

        /// Represents a single connection from a client.
        class connection
                : public std::enable_shared_from_this<connection> {
        public:
            connection(const connection &) = delete;

            connection &operator=(const connection &) = delete;

            /// Construct a connection with the given socket.
            explicit connection(boost::asio::ip::tcp::socket socket,
                                connection_manager &manager, request_handler &handler, route_manager &r_manager);

            /// Start the first asynchronous operation for the connection.
            void start();

            /// Stop all asynchronous operations associated with the connection.
            void stop();

        private:
            /// Perform an asynchronous read operation.
            void do_read();

            /// Perform an asynchronous write operation.
            void do_write();

            /// Socket for the connection.
            boost::asio::ip::tcp::socket socket_;

            /// The manager for this connection.
            connection_manager &connection_manager_;

            route_manager &route_manager_;

            /// The handler used to process the incoming request.
            request_handler &request_handler_;

            /// Buffer for incoming data.
            std::array<char, 8192> buffer_;

            /// The incoming request.
            request request_;

            /// The parser for the incoming request.
            request_parser request_parser_;

            /// The reply to be sent back to the client.
            reply reply_;
        };

        typedef std::shared_ptr<connection> connection_ptr;

    } // namespace server
} // namespace http

#endif // HTTP_CONNECTION_HPP