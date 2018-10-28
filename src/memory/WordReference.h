#pragma once

#include "memory/WordAddressable.h"

#include <stdint.h>

namespace GameBoy {

// class which wraps a reference to a uint16_t
class WordReference : public WordAddressable {
public:
    WordReference(uint16_t& value);
    ~WordReference() override;

    auto read8() -> uint8_t override;
    auto read16() -> uint16_t override;

    auto write8(uint8_t value) -> void override;
    auto write16(uint16_t value) -> void override;

private:
    uint16_t& m_value;
};

}
