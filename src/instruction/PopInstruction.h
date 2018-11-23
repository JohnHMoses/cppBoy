#pragma once

#include "instruction/Instruction.h"
#include "memory/WordAddressable.h"

#include <memory>

namespace GameBoy {

class PopInstruction : public Instruction {
public:
    PopInstruction(
        std::unique_ptr<WordAddressable>&& toRef);

    ~PopInstruction() override;

private:
    auto perform_operation(CPU&) -> void override;

    std::unique_ptr<WordAddressable> m_toRef;
};

}
