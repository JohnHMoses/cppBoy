
#include "Memory.h"

namespace GameBoy {

constexpr size_t MEM_SIZE = 0x100;

Memory::Memory()
    : m_memory(MEM_SIZE) {};

auto Memory::write8(uint8_t value, uint16_t address) -> void
{
    m_memory[address] = value;
};

auto Memory::write16(uint16_t value, uint16_t address) -> void
{
    // TODO: handle overflow
    assert(address != MEM_SIZE - 1);
    write8(uint8_t(value), address);
    write8(uint8_t(value >> 8), address + 1);
};

auto Memory::read8(uint16_t address) -> uint8_t
{
    return m_memory[address];
};

auto Memory::read16(uint16_t address) -> uint16_t
{
    return uint16_t(read8(address)) | uint16_t(read8(address + 1)) << 8;
};

}
