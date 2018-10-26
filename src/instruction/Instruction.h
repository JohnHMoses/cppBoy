#pragma once

#include <stdint.h>

namespace GameBoy {

class CPU;

class Instruction {
public:
    virtual ~Instruction() = default;
    virtual auto execute(CPU&) -> void = 0;

    auto with_cycles(uint8_t numCycles) -> Instruction&;

protected:
    uint8_t m_cycles = 0;
};

}
