#pragma once

#include "../memory/ByteAddressable.h"
#include "Instruction.h"

#include <memory>

namespace GameBoy {

// Reads byte from one reference into another
class LoadByteInstruction : public Instruction {
public:
    LoadByteInstruction(
        std::unique_ptr<ByteAddressable>&& fromRef,
        std::unique_ptr<ByteAddressable>&& toRef);

    ~LoadByteInstruction() override;

    auto execute(CPU&) -> void override;

private:
    std::unique_ptr<ByteAddressable> m_fromRef;
    std::unique_ptr<ByteAddressable> m_toRef;
};

}
