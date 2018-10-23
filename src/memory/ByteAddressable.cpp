#include "ByteAddressable.h"

#include <iostream>

namespace GameBoy {

ByteAddressable::ByteAddressable() = default;

ByteAddressable::~ByteAddressable() = default;

auto ByteAddressable::read16() -> uint16_t
{
    std::cout << "Attempted to read16() a ByteAddressable, aborting\n";
    abort();
}

auto ByteAddressable::write16(uint16_t) -> void
{
    std::cout << "Attempted to write16() a ByteAddressable, aborting\n";
    abort();
}

}
