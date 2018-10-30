#include "instruction/LoadByteInstruction.h"

using namespace std;

namespace GameBoy {

LoadByteInstruction::LoadByteInstruction(
    std::unique_ptr<ByteAddressable>&& fromRef,
    std::unique_ptr<ByteAddressable>&& toRef)
    : m_fromRef(move(fromRef))
    , m_toRef(move(toRef)) {};

LoadByteInstruction::~LoadByteInstruction() = default;

auto LoadByteInstruction::perform_operation(CPU& cpu) -> void
{
    const auto value = m_fromRef->read8();
    m_toRef->write8(value);
}

}
