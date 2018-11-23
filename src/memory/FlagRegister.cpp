#include "memory/FlagRegister.h"

#include <bitset>

namespace GameBoy {

using namespace std;

FlagRegister::FlagRegister(std::unique_ptr<ByteAddressable>&& flagRef)
    : m_flagRef(move(flagRef)) {};

auto FlagRegister::set_zero(bool value) -> void
{
    set_bit(7, value);
}

auto FlagRegister::set_substract(bool value) -> void
{
    set_bit(6, value);
}

auto FlagRegister::set_half_carry(bool value) -> void
{
    set_bit(5, value);
}

auto FlagRegister::set_carry(bool value) -> void
{
    set_bit(4, value);
}

auto FlagRegister::set_bit(size_t pos, bool value) -> void
{
    bitset<8> flagBits { m_flagRef->read8() };
    flagBits.set(pos, value);
    auto newFlagValue = uint8_t(flagBits.to_ulong());
    m_flagRef->write8(newFlagValue);
}

}
