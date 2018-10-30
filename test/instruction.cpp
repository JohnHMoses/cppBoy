#include "gtest/gtest.h"

#include "CPU.h"
#include "Registers.h"
#include "memory/Memory.h"
#include "instruction/LoadByteInstruction.h"

#include <memory>

using namespace GameBoy;
using namespace std;

class InstructionTest : public ::testing::Test {
protected:
    void SetUp() override {
        mem = make_unique<Memory>();
        cpu = make_unique<CPU>(*mem);
    }

    unique_ptr<CPU> cpu;
    unique_ptr<Memory> mem;
};

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
