#include "route_manager.hpp"

namespace http {
    namespace server {
        route_manager::route_manager() {
        }

        void route_manager::register_route(route_index idx, route_fptr func) {
            if (route_exist(idx))
                return;

            map_.insert(std::pair<route_index, route_fptr>(idx, func));
        }

        bool route_manager::route_exist(route_index idx) {
            route_map_it it = map_.find(idx);
            return (it == map_.end());
        }

        route_fptr route_manager::find_route_fptr(route_index idx) {
            route_map_it it = map_.find(idx);
            return (it == map_.end()) ? nullptr : it->second;
        }
    } // namespace server
} // namespace http
