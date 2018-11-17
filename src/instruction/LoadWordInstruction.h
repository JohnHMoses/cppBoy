#pragma once

#include "instruction/Instruction.h"
#include "memory/WordAddressable.h"

#include <memory>

namespace GameBoy {

// Reads 2 bytes from one reference into another
class LoadWordInstruction : public Instruction {
public:
    LoadWordInstruction(
        std::unique_ptr<WordAddressable>&& fromRef,
        std::unique_ptr<WordAddressable>&& toRef);

    ~LoadWordInstruction() override;

private:
    auto perform_operation(CPU&) -> void override;

    std::unique_ptr<WordAddressable> m_fromRef;
    std::unique_ptr<WordAddressable> m_toRef;
};

}
