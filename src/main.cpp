#include <iostream>
#include <boost/asio.hpp>
#include "server.hpp"

int main(int argc, char *argv[]) {
  try {
    // Check command line arguments.
    /*if (argc != 4) {
      std::cerr << "Usage: http_server <address> <port> <doc_root>\n";
      std::cerr << "  For IPv4, try:\n";
      std::cerr << "    receiver 0.0.0.0 80 .\n";
      std::cerr << "  For IPv6, try:\n";
      std::cerr << "    receiver 0::0 80 .\n";
      return 1;
    }*/
    std::string host = (argv[0] != nullptr) ? argv[0] : "0.0.0.0";
    std::string port = (argv[1] != nullptr) ? argv[1] : "2001";
    std::string static_dir = (argv[2] != nullptr) ? argv[2] : ".";
    // Initialise the server.
//    http::server::server s(argv[0], argv[1], argv[2]);
    std::cout << host;
    http::server::server s(host, port, static_dir);

    std::cout << "server started" << std::endl;

    s.set_route("GET", "/test", [](const http::server::request &req, http::server::reply &rep) {
        rep.content = "hello";
        rep.headers.resize(2);
        rep.headers[0].name = "Content-Length";
        rep.headers[0].value = std::to_string(rep.content.size());
        rep.headers[1].name = "Content-Type";
        rep.headers[1].value = "text/html";
    });

    // Run the server until stopped.
    s.run();
  }
  catch (std::exception &e) {
    std::cerr << "exception: " << e.what() << "\n";
  }

  return 0;
}