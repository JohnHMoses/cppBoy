#include "instruction/PushInstruction.h"

#include "CPU.h"
#include "memory/Memory.h"

namespace GameBoy {

using namespace std;

PushInstruction::PushInstruction(unique_ptr<WordAddressable>&& fromRef)
    : m_fromRef(move(fromRef)) {};

PushInstruction::~PushInstruction() = default;

auto PushInstruction::perform_operation(CPU& cpu) -> void
{
    auto stackPointerRef = cpu.get_stack_pointer();
    stackPointerRef->write16(stackPointerRef->read16() - 2);

    cpu.memory.deref_word(*stackPointerRef)->write16(m_fromRef->read16());
}

}
