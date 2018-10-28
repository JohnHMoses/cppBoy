#include "instruction/Instruction.h"

namespace GameBoy {

auto Instruction::with_cycles(uint8_t numCycles) -> Instruction&
{
    m_cycles = numCycles;
    return *this;
}

auto Instruction::with_instruction_length(uint16_t numBytes) -> Instruction&
{
    m_numBytes = numBytes;
    return *this;
}

}
