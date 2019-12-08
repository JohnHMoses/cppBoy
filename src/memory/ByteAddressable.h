#pragma once

#include <memory>
#include <stdint.h>

namespace GameBoy {

// Addressable for which only read8/write8 is defined
class ByteAddressable {
public:
    virtual ~ByteAddressable();

    virtual auto clone() -> std::unique_ptr<ByteAddressable> = 0;

    virtual auto read8() -> uint8_t = 0;
    virtual auto write8(uint8_t value) -> void = 0;
};

}
