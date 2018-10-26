#include "WordReference.h"

namespace GameBoy {

WordReference::WordReference(uint16_t& value)
    : m_value(value) {};

WordReference::~WordReference() = default;

auto WordReference::read8() -> uint8_t
{
    return uint8_t(m_value);
}

auto WordReference::read16() -> uint16_t
{
    return m_value;
}

auto WordReference::write8(uint8_t value) -> void
{
    auto base = read16();
    base &= 0xFF00; // clear out the low byte
    base |= uint16_t(value); // Add our value we're writing
    write16(base);
}

auto WordReference::write16(uint16_t value) -> void
{
    m_value = value;
}

}
