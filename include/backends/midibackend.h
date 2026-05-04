#ifndef MIDIBACKEND_H 
#define MIDIBACKEND_H 
#include <string>
#include <vector>
#include "../common/listener.h"
#include "../common/midiendpoint.h"
namespace midiio {
    class imidibackend {
        protected:
            Listener* m_listener;
            midiendpoint m_selected;
            std::vector<midiendpoint> m_available;

        public:

            imidibackend() {};
            ~imidibackend() = default;
            std::vector<midiendpoint> available_devices() const {
                return m_available;
            }
            void set_listener(Listener* listener) {
                m_listener = listener;
            }
            virtual void enumerate_devices() = 0;
            //virtual void set_input_device(std::string deviceId) = 0;
            virtual bool open_device() = 0;
            virtual void start_device() = 0;
            virtual void select_endpoint(midiendpoint ep) = 0;
            //virtual void midi_callback();
            

    };
}
#endif