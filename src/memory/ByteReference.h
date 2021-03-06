#pragma once

#include "memory/ByteAddressable.h"

namespace GameBoy {

// References a naked byte, allows reading and writing the byte
class ByteReference : public ByteAddressable {
public:
    ByteReference(uint8_t& value);
    ~ByteReference() override;

    auto clone() -> std::unique_ptr<ByteAddressable> override;

    auto read8() -> uint8_t override;

    auto write8(uint8_t value) -> void override;

private:
    uint8_t& m_value;
};

}
