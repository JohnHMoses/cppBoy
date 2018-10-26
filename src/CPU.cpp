
#include "CPU.h"

#include "instruction/Instruction.h"
#include "memory/Memory.h"

namespace GameBoy {

CPU::CPU(Memory& memory)
    : m_memory(memory)
{
}

auto CPU::tick() -> void
{
    // FIXME: implement CPU ticking logic
}

}
