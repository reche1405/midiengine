#ifndef LISTENER_H
#define LISTENER_H
#include "midiqueue.h"
#include "midievent.h"
#include <memory>
namespace midiio {
    struct Listener {
        virtual void on_midi_message() = 0;
        virtual  midiqueue<midievent, 1024>& midi_queue();
    };
}
#endif