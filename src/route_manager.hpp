#ifndef HTTP_ROUTE_MANAGER_HPP
#define HTTP_ROUTE_MANAGER_HPP

#include "reply.hpp"
#include "request.hpp"
#include <boost/function.hpp>

namespace http {
    namespace server {
        struct route_index {
            std::string method;
            std::string path;
        };

        typedef boost::function<void(const request &req, reply &rep)> route_fptr;
        typedef std::map<route_index, route_fptr> route_map;
        typedef std::map<route_index, route_fptr>::iterator route_map_it;


        class route_manager {
        public:
            route_manager();

            void register_route(route_index idx, route_fptr func);

            bool route_exist(route_index idx);

            route_fptr find_route_fptr(route_index idx);

        private:
            route_map map_;
        };
    } // namespace server
} // namespace http
#endif