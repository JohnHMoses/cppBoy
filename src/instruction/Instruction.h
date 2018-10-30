#pragma once

#include <stdint.h>

namespace GameBoy {

class CPU;

class Instruction {
public:
    virtual ~Instruction() = default;
    virtual auto execute(CPU&) -> void;

    auto with_cycles(uint8_t numCycles) -> Instruction&;
    auto with_instruction_length(uint16_t numBytes) -> Instruction&;

private:
    virtual auto perform_operation(CPU&) -> void = 0;
    virtual auto move_program_counter(CPU&) -> void;
    virtual auto tick_clock(CPU&) -> void;

protected:
    uint8_t m_cycles = 0;
    uint16_t m_numBytes = 0;
};

}
