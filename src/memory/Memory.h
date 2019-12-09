#pragma once

#include "Registers.h"
#include "memory/ByteAddressable.h"
#include "memory/WordAddressable.h"
#include "memory/BytePointer.h"

#include <memory>
#include <unordered_map>
#include <vector>

namespace GameBoy {

/*
Memory Model:
     Interrupt Enable Register
    --------------------------- FFFF
     Internal RAM
    --------------------------- FF80
     Empty but unusable for I/O
    --------------------------- FF4C
     I/O ports
    --------------------------- FF00
     Empty but unusable for I/O
    --------------------------- FEA0
     Sprite Attrib Memory (OAM)
    --------------------------- FE00
     Echo of 8kB Internal RAM
    --------------------------- E000
     8kB Internal RAM
    --------------------------- C000
     8kB switchable RAM bank
    --------------------------- A000
     8kB Video RAM
    --------------------------- 8000 --
     16kB switchable ROM bank         |
    --------------------------- 4000  |= 32kB Cartrigbe
     16kB ROM bank #0                 |
    --------------------------- 0000 --
*/
class Memory {
public:
    Memory();

    // Returns a pointer to an interface that allows reading and writing
    auto get_ref(uint16_t address) -> std::unique_ptr<ByteAddressable>;
    auto get_word_ref(uint16_t address) -> std::unique_ptr<WordAddressable>;

    auto get_register(Register registerName) -> std::unique_ptr<ByteAddressable>;
    auto get_word_register(WordRegister registerName) -> std::unique_ptr<WordAddressable>;

    auto operator[](Register registerName) -> BytePointer;

    auto deref(WordAddressable& addressRef, int16_t offset = 0) -> std::unique_ptr<ByteAddressable>;
    auto deref_word(WordAddressable& addressRef, int16_t offset = 0) -> std::unique_ptr<WordAddressable>;

private:
    std::vector<uint8_t> m_memory;
    uint16_t m_stackPointer;
    uint16_t m_programCounter;
    std::unordered_map<Register, uint8_t> m_registers;
};

}
