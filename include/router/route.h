#ifndef ROUTE_H
#define ROUTE_H
#include <vector>
#include <memory>
#include "../common/midiprocessor.h"
#include "../common/midiqueue.h"
namespace midiio {
    class router;
    class route {
        protected:
            std::vector<std::shared_ptr<midiprocessor>> m_processors;
            midiqueue<midievent, 2046> m_queue;
            

        public:
            void push_event(const midievent& event) {
                m_queue.push(event);
            }
            void process_midi() {
                midievent event;
                while(m_queue.pop(event)) {

                    for(auto processor : m_processors) {
                        processor.get()->process_midi(event);
                    }
                }
            }
            void add_processor(std::shared_ptr<midiprocessor> processor) {
                m_processors.push_back(processor);
            }

    };
}
#endif