#include "Memory.h"

#include "ByteReference.h"
#include "WordReference.h"

namespace GameBoy {

constexpr size_t MEM_SIZE = 0x100;

Memory::Memory()
    : m_memory(MEM_SIZE)
{
    m_registers = std::unordered_map<Register, uint8_t>{
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

auto Memory::get_word_ref(uint16_t address) -> std::unique_ptr<WordAddressable>
{
    // TODO: figure out what to do about overflow
    assert(address != MEM_SIZE - 1);

    // For now, just assume everything is a big RAM bank
    return std::make_unique<WordReference>(
        std::make_unique<ByteReference>(m_memory.at(address)),
        std::make_unique<ByteReference>(m_memory.at(address + 1)));
}

}
