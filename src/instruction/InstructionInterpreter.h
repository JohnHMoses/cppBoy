#pragma once

#include <memory>

namespace GameBoy {
class Instruction;
class Memory;
}

namespace GameBoy::InstructionInterpreter {

auto interpret_next_intstruction(Memory&) -> std::unique_ptr<Instruction>;

}
