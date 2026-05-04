#ifndef MIDISERVICEBACKEND_H
#define MIDISERVICEBACKEND_H
#include "../midibackend.h"
#include <winrt/Windows.Foundation.h>
#include <iostream>
#include <winrt/Microsoft.Windows.Devices.Midi2.h>
#include <winrt/Windows.Devices.Enumeration.h>
#include <winrt/Windows.Foundation.Collections.h>
namespace midiio {
    class midiservicebackend : public imidibackend {
        public:
        midiservicebackend() = default;
        ~midiservicebackend()  = default;
        void enumerate_devices() override {
            std::cout << "Beginning enumeration" << std::endl;
            //using namespace winrt::Microsoft::Windows::Devices::Midi2;
            auto endpointList = winrt::Microsoft::Windows::Devices::Midi2::MidiEndpointDeviceInformation::FindAll();
            std::cout << "Devices located" << std::endl;

            if(endpointList.Size() < 1) {
                printf("Unable to find any devices.");
                return;
            }
            for (const auto& endpoint : endpointList) {
                printf("Device: %ls\n", endpoint.Name().c_str());
                printf("  ID: %ls\n", endpoint.EndpointDeviceId().c_str());
            }
        };
        void select_endpoint(midiendpoint ep) override {
            m_selected = ep;
        }
        bool open_device() override {
            std::cerr << "Unimplemented" <<  std::endl;
        }
        void start_device() override {
            std::cerr << "Unimplemented" <<  std::endl;
        }
    };
}
#endif