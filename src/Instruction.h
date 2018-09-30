#pragma once

namespace GameBoy {

class CPU;

class Instruction
{
public:
    void execute(CPU&) const = 0;
};

}
