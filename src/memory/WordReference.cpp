#include "WordReference.h"

using namespace std;

namespace GameBoy {

WordReference::WordReference(unique_ptr<ByteAddressable>&& lower,
    unique_ptr<ByteAddressable>&& upper)
    : WordAddressable()
    , m_lower(move(lower))
    , m_upper(move(upper)) {};

WordReference::~WordReference() = default;

auto WordReference::read8() -> uint8_t
{
    return m_lower->read8();
}

auto WordReference::read16() -> uint16_t
{
    return uint16_t(m_lower->read8()) + (uint16_t(m_upper->read8()) << 8);
}

auto WordReference::write8(uint8_t value) -> void
{
    m_lower->write8(value);
}

auto WordReference::write16(uint16_t value) -> void
{
    m_lower->write8(uint8_t(value));
    m_upper->write8(uint8_t(value >> 8));
}

}
