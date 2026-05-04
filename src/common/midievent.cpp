#include "../../include/common/midievent.h"
namespace midiio {
    eventtype mididecoder::get_event_type(uint8_t status) {
        return static_cast<eventtype>(status & 0xF0);
    }

    midievent mididecoder::decode(uint32_t dwParam1, uint32_t dwParam2, uint64_t timestamp) {
        midievent event;
        uint8_t status = dwParam1 & 0xFF;
        event.timestamp = timestamp;
        event.type = get_event_type(status);
        event.channel = status & 0x0F;
        switch (event.type) {
            case eventtype::NoteOn:
            case eventtype::NoteOff:
            case eventtype::PolyAftertouch:
            case eventtype::ControlChange:
            case eventtype::PitchBend:
                event.data1 = (dwParam1 >> 8) & 0xFF;
                event.data2 = (dwParam1 >> 16) & 0xFF;
                break;
            case eventtype::ProgramChange:
            case eventtype::ChannelAftertouch:
                event.data1 = (dwParam1 >> 8) & 0xFF;
                event.data2 = 0;
                break;
            default:
                event.data1 = 0;
                event.data2 = 0;
                break;
        }
        return event;
    }

    uint32_t midiencoder::encode(const midievent& event) {
        uint32_t result = 0;
        uint8_t status = static_cast<uint8_t>(event.type) | (event.channel & 0x0F);
        
        result |= status;
        result |= (event.data1 << 8);
        result |= (event.data2 << 16);
        
        return result;
    }
}