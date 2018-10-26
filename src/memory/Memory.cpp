#include "Memory.h"

#include "ByteReference.h"
#include "CompositeWordReference.h"

namespace GameBoy {

constexpr size_t MEM_SIZE = 0x100;

Memory::Memory()
    : m_memory(MEM_SIZE)
{
    m_registers = std::unordered_map<Register, uint8_t> {
        { Register::A, 0 },
        { Register::B, 0 },
        { Register::C, 0 },
        { Register::D, 0 },
        { Register::E, 0 },
        { Register::F, 0 },
        { Register::H, 0 },
        { Register::L, 0 }
    };
}

auto Memory::get_ref(uint16_t address) -> std::unique_ptr<ByteAddressable>
{
    // For now, just assume everything is a big RAM bank
    return std::make_unique<ByteReference>(m_memory.at(address));
}

auto Memory::get_word_ref(uint16_t address) -> std::unique_ptr<WordAddressable>
{
    // TODO: figure out what to do about overflow
    assert(address != MEM_SIZE - 1);

    return std::make_unique<CompositeWordReference>(
        get_ref(address),
        get_ref(address + 1)
    );
}

auto Memory::get_register(Register registerName) -> std::unique_ptr<ByteAddressable> {
    return std::make_unique<ByteReference>(m_registers.at(registerName));
}

auto Memory::get_word_register(WordRegister registerName) -> std::unique_ptr<WordAddressable> {
    switch(registerName)
    {
    case WordRegister::AF:
    case WordRegister::BC:
    case WordRegister::DE:
    case WordRegister::HL:
    case WordRegister::SP:
        //return std::make_unique
    case WordRegister::PC:
        //return std::make_unique<ByteReference>(m_pc);
    default:
        abort();
    }
}

}
