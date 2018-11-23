
#include "CPU.h"

#include "instruction/Instruction.h"
#include "memory/Memory.h"

using namespace std;

namespace GameBoy {

CPU::CPU(Memory& memory)
    : memory(memory)
{
}

auto CPU::tick() -> void
{
    // FIXME: implement CPU ticking logic
}

auto CPU::get_program_counter() -> unique_ptr<WordAddressable>
{
    return memory.get_word_register(WordRegister::PC);
}

auto CPU::get_stack_pointer() -> unique_ptr<WordAddressable>
{
    return memory.get_word_register(WordRegister::SP);
}

auto CPU::get_flags() -> FlagRegister
{
    return FlagRegister(move(memory.get_register(Register::F)));
}

}
