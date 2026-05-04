#ifndef MIDIENGINE_H 
#define MIDIENGINE_H
#include "common/listener.h"
#include "backends/midibackend.h"
#include <memory>
#include "./common/midiqueue.h"
#include "./common/midievent.h"
#include "backends/backendfactory.h"
namespace midiio {
    class MidiEngine : public Listener {
        private:
            std::unique_ptr<imidibackend> m_backend;
            midiqueue<midievent, 1024> m_queue;
        public:
            MidiEngine() {
                initialise();
            }
            ~MidiEngine() = default;
            midiqueue<midievent, 1024>& midi_queue() override {
                return m_queue;
            }
            void initialise() {
                m_backend = BackendFactory::create_backend();
                m_backend.get()->set_listener(this);
            }
    };
}
#endif