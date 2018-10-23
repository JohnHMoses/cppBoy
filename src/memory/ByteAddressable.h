#pragma once

#include "Addressable.h"

namespace GameBoy {

// Addressable for which only read8/write8 is defined
// Calling read16/write16 is a programmer error
class ByteAddressable : public Addressable {
public:
    ByteAddressable();
    ~ByteAddressable() override;

    auto read16() -> uint16_t override;

    auto write16(uint16_t value) -> void override;
};

}
