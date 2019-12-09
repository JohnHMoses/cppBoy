#include "memory/NewByteReference.h"

namespace GameBoy {

NewByteReference::operator uint8_t()
{
    return m_ref->read8();
}

auto NewByteReference::operator=(uint8_t value) -> void
{
    m_ref->write8(value);
}

NewByteReference::NewByteReference(std::unique_ptr<ByteAddressable> ref)
    : m_ref(move(ref)) {};

NewByteReference::NewByteReference(const NewByteReference& other)
    : m_ref(move(other.m_ref->clone())) {};

}
