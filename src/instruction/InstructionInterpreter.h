#pragma once

#include <memory>

namespace GameBoy::InstructionInterpreter {

class Instruction;
class Memory;

auto interpret_next_intstruction(Memory&) -> std::unique_ptr<Instruction>;

}
