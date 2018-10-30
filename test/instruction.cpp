#include "gtest/gtest.h"

#include "CPU.h"
#include "Registers.h"
#include "memory/Memory.h"
#include "instruction/LoadByteInstruction.h"
#include "instruction/Instruction.h"

#include <memory>

using namespace GameBoy;
using namespace std;

// Mock instruction for testing inherited behavior from instruction
class MockInstruction : public Instruction {
public:
    // NO-OP perform_operation
    auto perform_operation(CPU& cpu) -> void override { };
};

class InstructionTest : public ::testing::Test {
protected:
    void SetUp() override {
        mem = make_unique<Memory>();
        cpu = make_unique<CPU>(*mem);
    }

    unique_ptr<CPU> cpu;
    unique_ptr<Memory> mem;
};

TEST_F(InstructionTest, BaseInstructionCanMoveProgramCounter) {
    auto pcRef = mem->get_word_register(WordRegister::PC);
    const auto beforeExecutePC = pcRef->read16();

    MockInstruction instr;
    instr.with_instruction_length(0x42);

    instr.execute(*cpu);

    const auto afterExecutePC = pcRef->read16();

    EXPECT_EQ(beforeExecutePC + 0x42, afterExecutePC);
}

TEST_F(InstructionTest, LoadByte) {
    {
        auto refA = mem->get_register(Register::A);
        auto refB = mem->get_register(Register::B);

        refA->write8(0x12);
        refB->write8(0x34);

        LoadByteInstruction instr(move(refA), move(refB));
        instr.execute(*cpu);
    }

    auto refA = mem->get_register(Register::A);
    auto refB = mem->get_register(Register::B);

    EXPECT_EQ(refA->read8(), 0x12);
    EXPECT_EQ(refB->read8(), 0x12);
}
