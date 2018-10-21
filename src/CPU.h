#pragma once

namespace GameBoy {

class Memory;

// Executes instructions
class CPU {
public:
    CPU(Memory&);

    auto tick();

private:
    Memory& m_memory;
};

}
