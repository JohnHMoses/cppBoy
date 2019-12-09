#pragma once

#include "instruction/Instruction.h"
#include "memory/NewByteReference.h"

#include <memory>

namespace GameBoy {

// Reads byte from one reference into another
class LoadByteInstruction : public Instruction {
public:
    LoadByteInstruction(
        const NewByteReference& m_to,
        const NewByteReference& m_from);

    ~LoadByteInstruction() override;

private:
    auto perform_operation(CPU&) -> void override;

    NewByteReference m_to;
    NewByteReference m_from;
};

}
