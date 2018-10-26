#include "LoadByteInstruction.h"

using namespace std;

namespace GameBoy {

LoadByteInstruction::LoadByteInstruction(
    std::unique_ptr<ByteReference>&& fromRef,
    std::unique_ptr<ByteReference>&& toRef)
    : m_fromRef(move(fromRef))
    , m_toRef(move(toRef)) {};

LoadByteInstruction::~LoadByteInstruction() = default;

auto LoadByteInstruction::execute(CPU& cpu) -> void
{
    const auto value = m_fromRef->read8();
    m_toRef->write8(value);

    //TODO: move stack pointer
    //      tick until m_cycles done
}

}
