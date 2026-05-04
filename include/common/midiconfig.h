#ifndef MIDICONFIG_H
#define MIDICONFIG_H
#include <stdint.h>
#include <memory>
namespace midiio {

    enum class eventtype : uint8_t {
        NoteOff = 0x80,
        NoteOn = 0x90,
        PolyAftertouch = 0xA0,
        ControlChange = 0xB0,
        ProgramChange = 0xC0,
        ChannelAftertouch = 0xD0,
        PitchBend = 0xE0,
        SysEx = 0xF0,
        MTCQuarterFrame = 0xF1,
        SongPosition = 0xF2,
        SongSelect = 0xF3,
        TuneRequest = 0xF6,
        SysExEnd = 0xF7,
        TimingClock = 0xF8,
        Start = 0xFA,
        Continue = 0xFB,
        Stop = 0xFC,
        ActiveSensing = 0xFE,
        SystemReset = 0xFF
    };
    enum class backendtype {
        Auto,
        WinMM,
        MIDIService,
        CoreMIDI,
        ALSAMIDI
    };

}
#endif