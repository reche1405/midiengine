#ifndef MIDICONFIG_H
#define MIDICONFIG_H
#include <stdint.h>
#include <memory>
namespace midiio {
    struct midievent {
        uint32_t ump[4]; 
        uint32_t numWords{0};
        uint64_t timeStamp;
        midievent() = default;
        midievent(const uint32_t* words, uint32_t count, uint64_t ts):
        numWords(count), timeStamp(ts) {
            std::memcpy(ump,words, count * sizeof(uint32_t));
        }

    };
}
#endif