#ifndef BACKENDFACTORY_H
#define BACKENDFACTORY_H
#include <memory>
#include "./midibackend.h"
#ifdef _WIN32:
    #include "windows/winmmbackend.h"
#endif
namespace midiio {
    class BackendFactory {
        public:
        static std::unique_ptr<imidibackend> create_backend(backendtype type = backendtype::Auto) {
            if(type == backendtype::Auto) {

                #ifdef _WIN32:
                    return std::make_unique<winmmbackend>();
                #endif   
            }
            // Case specific implementations will go here
            // e.g. A user wants to switch midi service at runtime.
        }
    };
}
#endif