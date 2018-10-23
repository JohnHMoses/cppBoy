#include "ByteReference.h"

namespace GameBoy {

auto ByteReference::read8() -> uint8_t
{
    return m_value;
}

auto ByteReference::write8(uint8_t value) -> void
{
    m_value = value;
}

}
