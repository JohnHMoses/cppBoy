#pragma once

#include "instruction/Instruction.h"
#include "memory/ByteAddressable.h"

#include <memory>

namespace GameBoy {

// Reads byte from one reference into another
class LoadByteInstruction : public Instruction {
public:
    LoadByteInstruction(
        std::unique_ptr<ByteAddressable>&& fromRef,
        std::unique_ptr<ByteAddressable>&& toRef);

    ~LoadByteInstruction() override;

private:
    auto perform_operation(CPU&) -> void override;

    std::unique_ptr<ByteAddressable> m_fromRef;
    std::unique_ptr<ByteAddressable> m_toRef;
};

}
