#include "Instruction.h"

namespace GameBoy {

auto Instruction::with_cycles(uint8_t numCycles) -> Instruction&
{
    m_cycles = numCycles;
    return *this;
}

}
