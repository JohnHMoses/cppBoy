#include "instruction/LoadWordInstruction.h"

using namespace std;

namespace GameBoy {

LoadWordInstruction::LoadWordInstruction(
    std::unique_ptr<WordAddressable>&& fromRef,
    std::unique_ptr<WordAddressable>&& toRef)
    : m_fromRef(move(fromRef))
    , m_toRef(move(toRef)) {};

LoadWordInstruction::~LoadWordInstruction() = default;

auto LoadWordInstruction::perform_operation(CPU& cpu) -> void
{
    const auto value = m_fromRef->read16();
    m_toRef->write16(value);
}

}
