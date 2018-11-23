#include "gtest/gtest.h"

#include "CPU.h"
#include "Registers.h"
#include "memory/Memory.h"
#include "instruction/LoadByteInstruction.h"
#include "instruction/PushInstruction.h"
#include "instruction/PopInstruction.h"
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

TEST_F(InstructionTest, Then) {
    auto refA = mem->get_register(Register::A);
    auto& refToA = *refA;
    auto postOp = [&refToA] () {
        refToA.write8(0x12);
    };

    MockInstruction instr;
    instr.then(postOp);

    EXPECT_EQ(refA->read8(), 0x00);

    instr.execute(*cpu);
    EXPECT_EQ(refA->read8(), 0x12);
}

TEST_F(InstructionTest, Push) {
    auto regHL = mem->get_word_register(WordRegister::HL);
    regHL->write16(0x1234);

    auto stackPointer = cpu->get_stack_pointer();
    stackPointer->write16(0xC002);

    auto refToPushedLocation = mem->get_word_ref(0xC000);

    PushInstruction instr(move(regHL));
    instr.execute(*cpu);

    EXPECT_EQ(refToPushedLocation->read16(), 0x1234);
    EXPECT_EQ(stackPointer->read16(), 0xC000);
}

TEST_F(InstructionTest, Pop) {
    auto regHL = mem->get_word_register(WordRegister::HL);
    auto& refHL = *regHL;

    auto stackPointer = cpu->get_stack_pointer();
    stackPointer->write16(0xC000);

    auto refToPoppedFromLocation = mem->get_word_ref(0xC000);
    refToPoppedFromLocation->write16(0x1234);

    PopInstruction instr(move(regHL));
    instr.execute(*cpu);

    EXPECT_EQ(refHL.read16(), 0x1234);
    EXPECT_EQ(stackPointer->read16(), 0xC002);
}
