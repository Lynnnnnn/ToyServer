#ifndef HTTP_ROUTE_MANAGER_HPP
#define HTTP_ROUTE_MANAGER_HPP

#include "reply.hpp"
#include "request.hpp"
#include <boost/function.hpp>

namespace http {
    namespace server {
        typedef boost::function<void(const request &req, reply &rep)> invoker_function;
        typedef std::map<std::string, invoker_function> route_map;
        typedef std::map<std::string, invoker_function>::iterator route_map_it;

        class route_manager {
        public:
            route_manager();

            void route_register(std::string method, std::string path, invoker_function invoker);

            bool route_exist(std::string method, std::string path);

            invoker_function find_route_invoker(std::string method, std::string path);

            void route(const request &req, reply &rep);

        private:
            route_map map_;
        };
    } // namespace server
} // namespace http
#endif