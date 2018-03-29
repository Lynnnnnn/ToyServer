#include "route_manager.hpp"

namespace http {
  namespace server {
    route_manager::route_manager() {
    }

    void route_manager::route_register(std::string method, std::string path, invoker_function invoker) {
      if(route_exist(method, path))
        return;

      map_.insert(std::pair<std::string, invoker_function>(method + path, invoker));
    }

    bool route_manager::route_exist(std::string method, std::string path) {
      route_map_it it = map_.find(method + path);
      return (it == map_.end());
    }

    invoker_function route_manager::find_route_invoker(std::string method, std::string path) {
      route_map_it it = map_.find(method + path);
      return (it == map_.end()) ? NULL : it->second;
    }
  } // namespace server
} // namespace http
