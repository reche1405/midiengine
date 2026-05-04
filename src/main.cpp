#include "../include/backends/windows/winmmbackend.h"
#include <iostream>
    int main() {
        std::cout << "Initialising application" << std::endl;
        
        midiio::winmmbackend backend;
        backend.enumerate_devices();
        auto devs = backend.available_devices();
        std::cout << "Please select a Midi Endpoint by entering a valid integer." << std::endl;
        int selected;
        for(int i =0; i < devs.size(); i++) {
            std::cout << "    " << i << ": " << devs[i].name << std::endl;
        }
        std::cin >> selected;
        backend.select_endpoint(devs[selected]);
        backend.open_device();
        backend.start_device(); 
        while(true) {
            Sleep(5000);
            std::cout << ".";
        }
        return 1;
    }

