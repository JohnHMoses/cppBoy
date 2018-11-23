#include "gtest/gtest.h"

#include "util/FlagHelpers.h"

#include <stdint.h>

TEST(FlagHelpersTest, AddHalfCarry) {
    using namespace GameBoy::FlagHelpers::Add;

    EXPECT_EQ(should_half_carry(0x0F, 0x01), true);
    EXPECT_EQ(should_half_carry(0xFF, 0x01), true);
    EXPECT_EQ(should_half_carry(0x0F, 0x0F), true);
    EXPECT_EQ(should_half_carry(0b0000'1000, 0b0000'1000), true);
    EXPECT_EQ(should_half_carry(0b0000'1111, 0b0000'0111), true);

    EXPECT_EQ(should_half_carry(0x0E, 0x01), false);
    EXPECT_EQ(should_half_carry(0xF0, 0x10), false);
    EXPECT_EQ(should_half_carry(0b0000'0111, 0b0000'0111), false);
}

TEST(FlagHelpersTest, AddCarry) {
    using namespace GameBoy::FlagHelpers::Add;

    EXPECT_EQ(should_carry(0xFF, 0x01), true);
    EXPECT_EQ(should_carry(0xFF, 0xFF), true);
    EXPECT_EQ(should_carry(0b1000'0000, 0b1000'0000), true);

    EXPECT_EQ(should_carry(0x0F, 0x0F), false);
    EXPECT_EQ(should_carry(0xFE, 0x01), false);
    EXPECT_EQ(should_carry(0b0111'0111, 0b0001'0001), false);
}
