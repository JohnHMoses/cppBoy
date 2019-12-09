#include "memory/CompositeWordReference.h"

#include "memory/ByteAddressable.h"

using namespace std;

namespace GameBoy {

CompositeWordReference::CompositeWordReference(unique_ptr<ByteAddressable>&& lower,
    unique_ptr<ByteAddressable>&& upper)
    : WordAddressable()
    , m_lower(move(lower))
    , m_upper(move(upper)) {};

CompositeWordReference::~CompositeWordReference() = default;

auto CompositeWordReference::clone() -> std::unique_ptr<WordAddressable>
{
    return std::make_unique<CompositeWordReference>(
        move(m_lower->clone()),
        move(m_upper->clone()));
}

auto CompositeWordReference::as_byte_address() -> std::unique_ptr<ByteAddressable>
{
    return m_lower->clone();
}

auto CompositeWordReference::read8() -> uint8_t
{
    return m_lower->read8();
}

auto CompositeWordReference::read16() -> uint16_t
{
    return uint16_t(m_lower->read8()) + (uint16_t(m_upper->read8()) << 8);
}

auto CompositeWordReference::write8(uint8_t value) -> void
{
    m_lower->write8(value);
}

auto CompositeWordReference::write16(uint16_t value) -> void
{
    m_lower->write8(uint8_t(value));
    m_upper->write8(uint8_t(value >> 8));
}

}
