#include "instruction/PopInstruction.h"

#include "CPU.h"
#include "memory/Memory.h"

namespace GameBoy {

using namespace std;

PopInstruction::PopInstruction(unique_ptr<WordAddressable>&& toRef)
    : m_toRef(move(toRef)) {};

PopInstruction::~PopInstruction() = default;

auto PopInstruction::perform_operation(CPU& cpu) -> void
{
    auto stackPointerRef = cpu.get_stack_pointer();

    m_toRef->write16(cpu.memory.deref_word(*stackPointerRef)->read16());
    stackPointerRef->write16(stackPointerRef->read16() + 2);
}

}
