#pragma once

#include "ByteAddressable.h"

namespace GameBoy {

// References a naked byte, allows reading and writing the byte
class ByteReference : public ByteAddressable {
public:
    ByteReference(uint8_t& value)
        : m_value(value) {};
    ~ByteReference() override = default;

    auto read8() -> uint8_t override;
    auto read16() -> uint16_t override { return 1; }

    auto write8(uint8_t value) -> void override;
    auto write16(uint16_t valie) -> void override { ; }

private:
    uint8_t& m_value;
};

}
