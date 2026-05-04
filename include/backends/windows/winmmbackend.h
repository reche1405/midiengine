#ifndef WINMMBACKEND_H
#define WINMMBACKEND_H
#include "../midibackend.h"
#include <windows.h>
#include <mmeapi.h>
#include <iostream>
namespace midiio {
    class winmmbackend : public imidibackend {
        private:
            HMIDIIN g_midiInHandle = nullptr;
        public:
            winmmbackend() {
                initialise();
            }
            void initialise() {
                enumerate_devices();
                std::cout << "Please select a Midi Endpoint by entering a valid integer." << std::endl;
                int selected;
                for(int i =0; i < m_available.size(); i++) {
                    std::cout << "    " << i << ": " << m_available[i].name << std::endl;
                }
                std::cin >> selected;
                select_endpoint(m_available[selected]);
                open_device();
                start_device(); 
            }
            void enumerate_devices() override {
                std::vector<midiendpoint> endpoints;
                int devNum = midiInGetNumDevs();
                if (devNum < 1) {
                    std::cout << "There are no midi input devices" << std::endl;   
                    return;
                }
                for(int i =0; i < devNum; i++) {
                    midiendpoint ep;
                    MIDIINCAPS caps;
                    UINT cbmc = sizeof(caps); 
                    MMRESULT mr = midiInGetDevCapsA(i, &caps,cbmc);
                    if(mr != MMSYSERR_NOERROR ) {
                        std::cout << "There has been an error with device " << i << std::endl;
                        continue;
                    }
                    std::cout << "Product Name\n    - " <<caps.szPname << std::endl;
                    ep.name = std::string(caps.szPname);
                    ep.deviceId = std::to_string(i);
                    ep.fallbackId = i;
                    //ep.manufacturer = std::string((char*)caps.wMid);
                    //ep.model = std::string((char*)caps.wPid);
                    endpoints.push_back(ep);
                }
                m_available = endpoints;

            }
            
            void select_endpoint(midiendpoint ep) override {
                m_selected = ep;
            }

            bool open_device() override  {
                int deviceId;
                if(!m_selected.fallbackId) {
                    deviceId = 1;

                } else {
                    deviceId = m_selected.fallbackId;
                }
                MMRESULT res = midiInOpen(
                    &g_midiInHandle,
                    deviceId,
                    reinterpret_cast<DWORD_PTR>(&midi_callback),
                    (DWORD_PTR) this,
                    CALLBACK_FUNCTION
                );
                if (res != MMSYSERR_NOERROR) {
                    std::cerr << "Failed to open MIDI device. Error: " << res << std::endl;
                    return false;
                }
                std::cout << "Successfully opened MIDI device ID: " << deviceId << std::endl;
                return true;
            }

            void start_device() override {
                if (g_midiInHandle) {
                    midiInStart(g_midiInHandle);
                    std::cout << "MIDI input started - listening for messages" << std::endl;
                }
            }
            
            static void CALLBACK midi_callback(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, 
            DWORD_PTR dwParam1, DWORD_PTR dwParam2)  {
                winmmbackend* pThis = reinterpret_cast<winmmbackend*>(dwInstance);
            
                if (pThis) {
                    pThis->handle_midi_message(hMidiIn, wMsg, dwParam1, dwParam2);
                   
                } else {
                    std::cout << "Unable to recast backend from dwInstance" << std::endl;
                }
            }
                    
            void handle_midi_message(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2) {
                switch (wMsg) {
                case MIM_DATA:
                    printf("MIDI message: 0x%08X\n", (DWORD)dwParam1);
                    break;
                case MIM_OPEN:
                    printf("MIDI device opened\n");
                    break;
                case MIM_CLOSE:
                    printf("MIDI device closed\n");
                    break;
                }
                LARGE_INTEGER now;
                QueryPerformanceCounter(&now);
                midievent event = mididecoder::decode(dwParam1, dwParam2,now.QuadPart);
                m_listener->midi_queue().push(event);
            }
        
    };

}
#endif