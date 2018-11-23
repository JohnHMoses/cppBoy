#pragma once

#include "memory/ByteAddressable.h"

#include <memory>

namespace GameBoy {

class FlagRegister {
public:
    FlagRegister(std::unique_ptr<ByteAddressable>&& flagRef);

    auto set_zero(bool) -> void;
    auto set_substract(bool) -> void;
    auto set_half_carry(bool) -> void;
    auto set_carry(bool) -> void;

private:
    auto set_bit(size_t pos, bool) -> void;

    std::unique_ptr<ByteAddressable> m_flagRef;
};

}
