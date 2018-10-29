#include "gtest/gtest.h"

#include "memory/CompositeWordReference.h"
#include "memory/ByteReference.h"
#include "memory/WordReference.h"

#include <memory>

using namespace GameBoy;
using namespace std;

auto make_cwr(uint8_t& lower, uint8_t& upper) -> CompositeWordReference {
    auto lowerRef = make_unique<ByteReference>(lower);
    auto upperRef = make_unique<ByteReference>(upper);
    return CompositeWordReference(move(lowerRef), move(upperRef));
}

TEST(ByteReferenceTest, ByteReferenceReadReflectsUnderlyingValue) {
    uint8_t testValue;
    ByteReference byteRef(testValue);
    EXPECT_EQ(byteRef.read8(), testValue);
}

TEST(ByteReferenceTest, ByteReferenceReadChangesWhenUnderlyingValueChanges) {
    uint8_t testValue = 0;
    ByteReference byteRef(testValue);
    testValue = 1;
    EXPECT_EQ(byteRef.read8(), 1);
}

TEST(ByteReferenceTest, ByteReferenceWriteChangesUnderlyingValue) {
    uint8_t testValue = 0;
    ByteReference byteRef(testValue);
    byteRef.write8(42);
    EXPECT_EQ(testValue, 42);

}

TEST(CompositeWordReferenceTest, CompositeWordReferenceReadReflectsReferences) {
    uint8_t lower = 0x34;
    uint8_t upper = 0x12;
    auto cwRef = make_cwr(lower, upper);
    EXPECT_EQ(cwRef.read16(), 0x1234);
}

TEST(CompositeWordReferenceTest, CompositeWordReferenceRead8GetsLower) {
    uint8_t lower = 0x34;
    uint8_t upper = 0x12;
    auto cwRef = make_cwr(lower, upper);
    EXPECT_EQ(cwRef.read8(), 0x34);
}

TEST(CompositeWordReferenceTest, CompositeWordReferenceWriteChangesToCorrectBytes) {
    uint8_t lower = 0x34;
    uint8_t upper = 0x12;
    auto cwRef = make_cwr(lower, upper);
    cwRef.write16(0x5678);
    EXPECT_EQ(cwRef.read16(), 0x5678);
    EXPECT_EQ(lower, 0x78);
    EXPECT_EQ(upper, 0x56);
}

TEST(WordReferenceTest, WordReferenceReadReflectsUnderlyingValue) {
    uint16_t testValue;
    WordReference wordRef(testValue);
    EXPECT_EQ(wordRef.read16(), testValue);
}

TEST(WordReferenceTest, WordReferenceReadChangesWhenUnderlyingValueChanges) {
    uint16_t testValue = 0;
    WordReference wordRef(testValue);
    testValue = 0x5678;
    EXPECT_EQ(wordRef.read16(), 0x5678);
}

TEST(WordReferenceTest, WordReferenceWriteChangesUnderlyingValue) {
    uint16_t testValue = 0;
    WordReference wordRef(testValue);
    wordRef.write16(0x1234);
    EXPECT_EQ(testValue, 0x1234);
}
