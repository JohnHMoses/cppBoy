#pragma once

#include "../memory/ByteReference.h"
#include "Instruction.h"

#include <memory>

namespace GameBoy {

// Reads byte from one reference into another
class LoadByteInstruction : public Instruction {
public:
    LoadByteInstruction(
        std::unique_ptr<ByteReference>&& fromRef,
        std::unique_ptr<ByteReference>&& toRef);

    ~LoadByteInstruction() override;

    auto execute(CPU&) -> void override;

private:
    std::unique_ptr<ByteReference> m_fromRef;
    std::unique_ptr<ByteReference> m_toRef;
};

}
