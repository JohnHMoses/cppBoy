#pragma once

#include "Addressable.h"

namespace GameBoy {

// Addressable for which only read8/write8 is defined
class ByteAddressable {
public:
    ByteAddressable();
    virtual ~ByteAddressable();

    virtual auto read8() -> uint8_t = 0;
    virtual auto write8(uint8_t value) -> void = 0;
};

}
