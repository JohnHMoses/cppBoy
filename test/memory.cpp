#include "gtest/gtest.h"
#include "memory/ByteReference.h"

using namespace GameBoy;

TEST(MemoryTest, ByteReferenceCanRead) {
    uint8_t testValue = 0;
    ByteReference byteRef(testValue);
    EXPECT_EQ(byteRef.read8(), testValue);
}
