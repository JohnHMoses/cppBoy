
#include "CPU.h"

#include "Memory.h"

namespace GameBoy {

CPU::CPU(Memory& memory) : m_memory(memory) {}

auto CPU::tick() {
    // FIXME: implement CPU ticking logic
}

}
