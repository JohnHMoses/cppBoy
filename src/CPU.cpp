
#include "CPU.h"

#include "instruction/Instruction.h"
#include "memory/Memory.h"

using namespace std;

namespace GameBoy {

CPU::CPU(Memory& memory)
    : m_memory(memory)
{
}

auto CPU::tick() -> void
{
    // FIXME: implement CPU ticking logic
}

auto CPU::get_program_counter() -> unique_ptr<WordAddressable>
{
    return m_memory.get_word_register(WordRegister::PC);
}

auto CPU::get_stack_pointer() -> unique_ptr<WordAddressable>
{
    return m_memory.get_word_register(WordRegister::SP);
}

}
