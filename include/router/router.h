#ifndef ROUTER_H
#define ROUTER_H
#include <vector>
#include <memory>
#include "./route.h"

namespace midiio {
    class router {
        private:
            std::vector<std::unique_ptr<route>> routes;
        public:
            void add_route(std::unique_ptr<route> route) {
                routes.push_back(route);
            }
            void route_event(const midievent& event) {
                routes[0]->push_event(event);
            }

    };
}
#endif