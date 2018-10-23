#pragma once

#include "Addressable.h"

#include <memory>
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
    auto operator[](uint16_t address) -> std::unique_ptr<Addressable>;

private:
    std::vector<uint8_t> m_memory;
};

}
