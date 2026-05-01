#ifndef MIDIQUEUE_H
#define MIDIQUEUE_H
#include <atomic>
#include <vector>

namespace midiio {
    template<typename T, size_t Capacity>
    class midiqueue {
        private:
            alignas(64) std::atomic<int> readPos{0};
            alignas(64) std::atomic<int> writePos{0};
            alignas(64) std::array<T, Capacity> buffer;
            
        public:
        
            bool push(const T& item) {
                size_t w = writePos.load(std::memory_order_acquire);
                size_t r = readPos.load(std::memory_order_acquire);
                size_t next = (w + 1) % Capacity;
                
                if (next == r) {
                    return false;  // Queue full
                }
                
                buffer[w] = item; 
                writePos.store(next, std::memory_order_release);
                return true;
            }
            
            bool pop(T& item) {
                size_t r = readPos.load(std::memory_order_acquire);
                size_t w = writePos.load(std::memory_order_acquire);
                
                if (r == w) {
                    return false;  // Queue empty
                }
                
                item = buffer[r]; 
                readPos.store((r + 1) % Capacity, std::memory_order_release);
                return true;
            }
            
            size_t size() const {
                size_t w = writePos.load(std::memory_order_acquire);
                size_t r = readPos.load(std::memory_order_acquire);
                return (w >= r) ? (w - r) : (Capacity - r + w);
            }
            
            bool empty() const {
                return readPos.load(std::memory_order_acquire) == 
                    writePos.load(std::memory_order_acquire);
            }
    };
}

#endif