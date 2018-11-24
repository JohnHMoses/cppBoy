#pragma once

#include "instruction/Instruction.h"
#include "memory/ByteAddressable.h"

#include <memory>

namespace GameBoy {

class AddByteInstruction : public Instruction {
public:
    AddByteInstruction(std::unique_ptr<ByteAddressable>&& fromRef, std::unique_ptr<ByteAddressable>&& toRef);

    ~AddByteInstruction() override;

private:
    auto perform_operation(CPU&) -> void override;

    std::unique_ptr<ByteAddressable> m_fromRef;
    std::unique_ptr<ByteAddressable> m_toRef;
};

}
