#pragma once

#include <stdint.h>

namespace GameBoy::FlagHelpers {

namespace Add {

    auto should_half_carry(uint8_t, uint8_t) -> bool;
    auto should_carry(uint8_t, uint8_t) -> bool;

}

}
