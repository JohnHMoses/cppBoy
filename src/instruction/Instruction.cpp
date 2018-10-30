#include "instruction/Instruction.h"

#include "memory/WordAddressable.h"
#include "CPU.h"

namespace GameBoy {

auto Instruction::execute(CPU& cpu) -> void {
    perform_operation(cpu);
    move_program_counter(cpu);
    tick_clock(cpu);
}

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

auto Instruction::move_program_counter(CPU& cpu) -> void {
    auto pcRef = cpu.get_program_counter();
    auto pcValue = pcRef->read16();
    pcValue += m_numBytes;
    pcRef->write16(pcValue);
}

auto Instruction::tick_clock(CPU& cpu) -> void {
    auto cyclesTicked = 0;
    while (cyclesTicked++ <= m_cycles)
    {
        cpu.tick();
    }
}

}
