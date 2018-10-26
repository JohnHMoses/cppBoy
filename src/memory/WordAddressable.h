#pragma once

#include <stdint.h>

namespace GameBoy {

// Addressable which supports both 8-bit and 16-bit read/writes
class WordAddressable {
public:
    virtual ~WordAddressable();

    virtual auto read8() -> uint8_t = 0;
    virtual auto read16() -> uint16_t = 0;

    virtual auto write8(uint8_t value) -> void = 0;
    virtual auto write16(uint16_t value) -> void = 0;
};

}
