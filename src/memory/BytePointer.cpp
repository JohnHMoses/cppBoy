#include "memory/BytePointer.h"

namespace GameBoy {

BytePointer::_reference::_reference(ByteAddressable& ref)
    : m_ref(ref) {};

BytePointer::_reference::operator uint8_t()
{
    return m_ref.read8();
}

auto BytePointer::_reference::operator=(uint8_t value) -> void
{
    m_ref.write8(value);
}

BytePointer::BytePointer(std::unique_ptr<ByteAddressable> ref)
    : m_ref(move(ref)) {};

BytePointer::BytePointer(const BytePointer& other)
    : m_ref(move(other.m_ref->clone())) {};

auto BytePointer::operator*() -> BytePointer::_reference
{
    return BytePointer::_reference(*m_ref);
}

}
