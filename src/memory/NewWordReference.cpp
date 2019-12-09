#include "memory/NewWordReference.h"

namespace GameBoy {

NewWordReference::NewWordReference(std::unique_ptr<WordAddressable> ref)
    : m_ref(move(ref)) {};

NewWordReference::NewWordReference(const NewWordReference& other)
    : m_ref(move(other.m_ref->clone())) {};

NewWordReference::operator uint16_t()
{
    return m_ref->read16();
}

auto NewWordReference::operator=(uint16_t value) -> void
{
    m_ref->write16(value);
}

}
