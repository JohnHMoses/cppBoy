#pragma once

#include <memory>
#include <stdint.h>

#include "memory/ByteAddressable.h"

namespace GameBoy {

// Addressable which supports both 8-bit and 16-bit read/writes
class WordAddressable {
public:
    virtual ~WordAddressable();

    virtual auto clone() -> std::unique_ptr<WordAddressable> = 0;

    virtual auto as_byte_address() -> std::unique_ptr<ByteAddressable> = 0;

    virtual auto read8() -> uint8_t = 0;
    virtual auto read16() -> uint16_t = 0;

    virtual auto write8(uint8_t value) -> void = 0;
    virtual auto write16(uint16_t value) -> void = 0;
};

}
