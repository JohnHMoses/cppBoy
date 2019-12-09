#include "instruction/LoadByteInstruction.h"

using namespace std;

namespace GameBoy {

LoadByteInstruction::LoadByteInstruction(
    const NewByteReference& to,
    const NewByteReference& from)
    : m_to(to)
    , m_from(from) {};

LoadByteInstruction::~LoadByteInstruction() = default;

auto LoadByteInstruction::perform_operation(CPU& cpu) -> void
{
    m_to = static_cast<uint8_t>(m_from);
}

}
