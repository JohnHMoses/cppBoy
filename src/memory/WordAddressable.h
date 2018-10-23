#pragma once

#include "ByteAddressable.h"

#include <memory>

namespace GameBoy {

// Addressable which supports both 8-bit and 16-bit read/writes
class WordAddressable : public Addressable {
public:
    WordAddressable(std::unique_ptr<ByteAddressable>&& lower, std::unique_ptr<ByteAddressable>&& upper);
    ~WordAddressable() override;

    auto read8() -> uint8_t override;
    auto read16() -> uint16_t override;

    auto write8(uint8_t value) -> void override;
    auto write16(uint16_t value) -> void override;

private:
    std::unique_ptr<ByteAddressable> m_lower;
    std::unique_ptr<ByteAddressable> m_upper;
};

}
