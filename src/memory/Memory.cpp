#include "memory/Memory.h"

#include "memory/ByteReference.h"
#include "memory/CompositeWordReference.h"
#include "memory/WordReference.h"

namespace GameBoy {

constexpr size_t MEM_SIZE = 0x10000;

Memory::Memory()
    : m_memory(MEM_SIZE)
    , m_stackPointer(0xFFFF)
    , m_programCounter(0)
{
    m_registers = std::unordered_map<Register, uint8_t> {
        { Register::A, 0 },
        { Register::B, 0 },
        { Register::C, 0 },
        { Register::D, 0 },
        { Register::E, 0 },
        { Register::F, 0 },
        { Register::H, 0 },
        { Register::L, 0 }
    };
}

auto Memory::get_ref(uint16_t address) -> std::unique_ptr<ByteAddressable>
{
    // For now, just assume everything is a big RAM bank
    return std::make_unique<ByteReference>(m_memory.at(address));
}

auto Memory::get_word_ref(uint16_t address) -> std::unique_ptr<WordAddressable>
{
    // TODO: figure out what to do about overflow
    assert(address != MEM_SIZE - 1);

    return std::make_unique<CompositeWordReference>(
        get_ref(address),
        get_ref(address + 1));
}

auto Memory::get_register(Register registerName) -> std::unique_ptr<ByteAddressable>
{
    return std::make_unique<ByteReference>(m_registers.at(registerName));
}

auto Memory::get_word_register(WordRegister registerName) -> std::unique_ptr<WordAddressable>
{
    switch (registerName) {
    case WordRegister::AF:
        return std::make_unique<CompositeWordReference>(
            get_register(Register::A),
            get_register(Register::F));
    case WordRegister::BC:
        return std::make_unique<CompositeWordReference>(
            get_register(Register::B),
            get_register(Register::C));
    case WordRegister::DE:
        return std::make_unique<CompositeWordReference>(
            get_register(Register::D),
            get_register(Register::E));
    case WordRegister::HL:
        return std::make_unique<CompositeWordReference>(
            get_register(Register::H),
            get_register(Register::L));
    case WordRegister::SP:
        return std::make_unique<WordReference>(m_stackPointer);
    case WordRegister::PC:
        return std::make_unique<WordReference>(m_programCounter);
    default:
        abort();
    }
}

auto Memory::operator[](Register registerName) -> NewByteReference
{
    return NewByteReference(move(get_register(registerName)));
}

auto Memory::deref(WordAddressable& addressRef, int16_t offset) -> std::unique_ptr<ByteAddressable>
{
    const auto address = addressRef.read16() + offset;
    return get_ref(address);
}

auto Memory::deref_word(WordAddressable& addressRef, int16_t offset) -> std::unique_ptr<WordAddressable>
{
    const auto address = addressRef.read16() + offset;
    return get_word_ref(address);
}

}
