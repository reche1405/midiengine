#ifndef MIDIPROCESSOR_H
#define MIDIPROCESSOR_H
#include "midievent.h"
namespace midiio {
   class midiprocessor {
    public:
    midiprocessor() = default;
    ~midiprocessor() = default;
    virtual void process_midi(const midievent &event);
   };
}
#endif