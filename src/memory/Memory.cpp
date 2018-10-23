
#include "Memory.h"
#include "Addressable.h"
#include "ByteReference.h"
#include "WordAddressable.h"

namespace GameBoy {

constexpr size_t MEM_SIZE = 0x100;

Memory::Memory()
    : m_memory(MEM_SIZE)
{
}

auto Memory::operator[](uint16_t address) -> std::unique_ptr<Addressable>
{
    // TODO: figure out what to do about overflow
    assert(address != MEM_SIZE - 1);

    // For now, just assume everything is a big RAM bank
    return std::make_unique<WordAddressable>(
        std::make_unique<ByteReference>(m_memory.at(address)),
        std::make_unique<ByteReference>(m_memory.at(address + 1)));
}

}
