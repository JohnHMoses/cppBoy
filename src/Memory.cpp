
#include "Memory.h"

namespace GameBoy {

Memory::Memory()
    : m_memory(0x100) {};

void Memory::write8(uint8_t value, uint16_t address)
{
    m_memory[address] = value;
};

void Memory::write16(uint16_t value, uint16_t address)
{
    write8(uint8_t(value), address);
    write8(uint8_t(value >> 8), address + 1);
};

uint8_t Memory::read8(uint16_t address)
{
    return m_memory[address];
};

uint16_t Memory::read16(uint16_t address)
{
    return uint16_t(read8(address)) | uint16_t(read8(address + 1)) << 8;
};

}
