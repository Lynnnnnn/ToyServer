#include "connection.hpp"
#include "connection_manager.hpp"
#include <iostream>

namespace http {
    namespace server {

        connection::connection(boost::asio::ip::tcp::socket socket,
                               connection_manager &manager, request_handler &handler, route_manager &r_manager)
                : socket_(std::move(socket)),
                  connection_manager_(manager),
                  request_handler_(handler),
                  route_manager_(r_manager) {
        }

        void connection::start() {
          do_read();
        }

        void connection::stop() {
          socket_.close();
        }

        void connection::do_read() {
          auto self(shared_from_this());
          socket_.async_read_some(boost::asio::buffer(buffer_),
                                  [this, self](boost::system::error_code ec, std::size_t bytes_transferred) {
                                      if (!ec) {
                                        request_parser::result_type result;
                                        std::tie(result, std::ignore) = request_parser_.parse(
                                                request_, buffer_.data(), buffer_.data() + bytes_transferred);

                                        if (result == request_parser::good) {
                                          //request_handler_.handle_request(request_, reply_);
                                          route_manager_.route(request_, reply_);
                                          this->response_back();
                                        } else if (result == request_parser::bad) {
                                          reply_ = reply::stock_reply(reply::bad_request);
                                          do_write();
                                        } else {
                                          do_read();
                                        }
                                      } else if (ec != boost::asio::error::operation_aborted) {
                                        connection_manager_.stop(shared_from_this());
                                      }
                                  });
        }

        void connection::do_write() {
          auto self(shared_from_this());
          boost::asio::async_write(socket_, reply_.to_buffers(),
                                   [this, self](boost::system::error_code ec, std::size_t) {
                                       if (!ec) {
                                         // Initiate graceful connection closure.
                                         boost::system::error_code ignored_ec;
                                         socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
                                                          ignored_ec);
                                       }

                                       if (ec != boost::asio::error::operation_aborted) {
                                         connection_manager_.stop(shared_from_this());
                                       }
                                   });
        }

        void connection::response_back() {
          reply_.add_header("Content-Length", std::to_string(reply_.content.size()));
          std::cout << reply_.content << std::endl;
          do_write();
        }

    } // namespace server
} // namespace http