#include "InstructionInterpreter.h"

#include "../memory/Memory.h"
#include "Instruction.h"

namespace GameBoy::InstructionInterpreter {

auto interpret_next_instruction(Memory& memory) -> std::unique_ptr<Instruction>
{
    // TODO
}

}
