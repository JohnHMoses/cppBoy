#pragma once

namespace GameBoy {

class Memory;

// Executes instructions
class CPU
{
public:
    CPU(Memory&);

    void tick();
private:
    Memory& m_memory;
};

}
