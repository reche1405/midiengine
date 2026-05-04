#ifndef MIDIENDPOINT_H
#define MIDIENDPOINT_H
#include <string>
namespace midiio {
    struct midiendpoint {
        midiendpoint() = default; 
        ~midiendpoint() = default;
        std::string deviceId;   
        std::string name;           
        std::string manufacturer;   
        std::string model;  
        int fallbackId;
    };
}
#endif