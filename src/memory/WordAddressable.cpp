#include "WordAddressable.h"

using namespace std;

namespace GameBoy {

WordAddressable::WordAddressable(unique_ptr<ByteAddressable>&& lower,
    unique_ptr<ByteAddressable>&& upper)
    : m_lower(move(lower))
    , m_upper(move(upper)) {};

WordAddressable::~WordAddressable() = default;

auto WordAddressable::read8() -> uint8_t
{
    return m_lower->read8();
}

auto WordAddressable::read16() -> uint16_t
{
    return uint16_t(m_lower->read8()) + (uint16_t(m_upper->read8()) << 8);
}

auto WordAddressable::write8(uint8_t value) -> void
{
    m_lower->write8(value);
}

auto WordAddressable::write16(uint16_t value) -> void
{
    m_lower->write8(uint8_t(value));
    m_upper->write8(uint8_t(value >> 8));
}

}
