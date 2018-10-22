#pragma once

namespace GameBoy {

class Memory;

// Executes instructions
class CPU {
public:
    CPU(Memory&);

    auto tick() -> void;

private:
    Memory& m_memory;
};

}
