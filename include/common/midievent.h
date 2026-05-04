#ifndef MIDIEVENT_H
#define MIDIEVENT_H
#include "./midiconfig.h"
#include <vector>
namespace midiio {
    struct midievent {
        eventtype type;
        uint8_t channel;      // 0-15 (only for channel messages)
        uint8_t data1;        // Note number, controller number, etc.
        uint8_t data2;        // Velocity, value, etc.
        uint64_t timestamp;   // In samples or microseconds
        std::vector<uint8_t> sysExData;  // For SysEx messages only
        
        // Helper methods
        bool isNoteOn() const { return type == eventtype::NoteOn && data2 > 0; }
        bool isNoteOff() const { return type == eventtype::NoteOff || (type == eventtype::NoteOn && data2 == 0); }
        int noteNumber() const { return data1; }
        int velocity() const { return data2; }
        int controllerNumber() const { return data1; }
        int controllerValue() const { return data2; }
        int pitchBendValue() const { return (data2 << 7) | data1; }
    };
    class mididecoder {
        public:
            static midievent decode(uint32_t dwParam1, uint32_t dwParam2, uint64_t timestamp);
            //static midievent decodeSysEx(const uint8_t* data, size_t size, uint64_t timestamp);
            static eventtype get_event_type(uint8_t status);
        
    };
    class midiencoder {
        public:
            static uint32_t encode(const midievent& event);  // For dwParam1 format
            //static void encodeSysEx(const midievent& event, std::vector<uint8_t>& output);
    };
}
#endif