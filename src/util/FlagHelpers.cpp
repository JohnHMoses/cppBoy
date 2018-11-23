#include "util/FlagHelpers.h"

namespace GameBoy::FlagHelpers {

namespace Add {

    auto should_half_carry(uint8_t a, uint8_t b) -> bool
    {
        // keep only the lower nibble
        a &= 0x0F;
        b &= 0x0F;

        // add the two lower nibbles together. If the upper nibble is non-zero, half-carry
        return 0xF0 & (a + b);
    }

    auto should_carry(uint8_t a, uint8_t b) -> bool
    {
        uint8_t res = a + b;
        return res < a || res < b;
    }
}

}
