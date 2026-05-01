#ifndef MIDIBACKEND_H 
#define MIDIBACKEND_H 
#include <string>
namespace midiio {
    class imidibackend {
        private:

        public:
            imidibackend() {};
            ~imidibackend() = default;
            virtual void enumerate_devices() = 0;
            virtual void set_input_device(std::string deviceId) = 0;
            

    };
}
#endif