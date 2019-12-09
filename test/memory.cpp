#include "gtest/gtest.h"

#include "memory/ByteReference.h"
#include "memory/NewByteReference.h"
#include "memory/NewWordReference.h"
#include "memory/CompositeWordReference.h"
#include "memory/Memory.h"
#include "memory/WordReference.h"
#include "Registers.h"

#include <memory>

using namespace GameBoy;
using namespace std;

auto make_cwr(uint8_t& lower, uint8_t& upper) -> std::unique_ptr<CompositeWordReference> {
    auto lowerRef = make_unique<ByteReference>(lower);
    auto upperRef = make_unique<ByteReference>(upper);
    return make_unique<CompositeWordReference>(move(lowerRef), move(upperRef));
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

TEST(NewByteReferenceTest, BytePointerUpdatesValues) {
    uint8_t testValue = 42;
    auto byteRef = std::make_unique<ByteReference>(testValue);

    NewByteReference p1(move(byteRef));
    uint8_t retrievedValue = p1;
    EXPECT_EQ(retrievedValue, 42);

    NewByteReference p2(p1);
    p2 = 10;
    EXPECT_EQ(testValue, 10);

}

TEST(CompositeWordReferenceTest, CompositeWordReferenceReadReflectsReferences) {
    uint8_t lower = 0x34;
    uint8_t upper = 0x12;
    auto cwRef = make_cwr(lower, upper);
    EXPECT_EQ(cwRef->read16(), 0x1234);
}

TEST(CompositeWordReferenceTest, CompositeWordReferenceRead8GetsLower) {
    uint8_t lower = 0x34;
    uint8_t upper = 0x12;
    auto cwRef = make_cwr(lower, upper);
    EXPECT_EQ(cwRef->read8(), 0x34);
}

TEST(CompositeWordReferenceTest, CompositeWordReferenceWriteChangesToCorrectBytes) {
    uint8_t lower = 0x34;
    uint8_t upper = 0x12;
    auto cwRef = make_cwr(lower, upper);
    cwRef->write16(0x5678);
    EXPECT_EQ(cwRef->read16(), 0x5678);
    EXPECT_EQ(lower, 0x78);
    EXPECT_EQ(upper, 0x56);
}

TEST(NewWordReferenceTest, NewWordReferneceHasSameSemanticsAsCWR) {
    uint8_t lower = 0x34;
    uint8_t upper = 0x12;
    auto newWordRef = NewWordReference(move(make_cwr(lower, upper)));
    uint16_t interpretedValue = newWordRef;
    EXPECT_EQ(interpretedValue, 0x1234);
    newWordRef = 0x5678;
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

TEST(MemoryTest, GetReferenceChangesPersist) {
    Memory mem;
    {
        auto testRef = mem.get_ref(0xC000);
        testRef->write8(42);
    }
    {
        auto testRef = mem.get_ref(0xC000);
        EXPECT_EQ(testRef->read8(), 42);
    }
}

TEST(MemoryTest, GetWordReferenceChangesPersist) {
    Memory mem;
    {
        auto testRef = mem.get_word_ref(0xC000);
        EXPECT_EQ(testRef->read16(), 0x0000);
        EXPECT_EQ(testRef->read8(), 0x00);

        testRef->write16(0x1234);
        EXPECT_EQ(testRef->read16(), 0x1234);
        EXPECT_EQ(testRef->read8(), 0x34);
    }
    {
        auto testRef = mem.get_word_ref(0xC000);
        EXPECT_EQ(testRef->read16(), 0x1234);
    }
}

TEST(MemoryTest, OverlappingReferencesEffectEachOther) {
    Memory mem;
    {
        auto testRef = mem.get_word_ref(0xC000);
        testRef->write16(0x1234);
    }
    {
        auto testRef = mem.get_ref(0xC002);
        testRef->write8(0x98);
    }
    {
        auto testRef = mem.get_word_ref(0xC001);
        EXPECT_EQ(testRef->read16(), 0x9812);
    }
}

TEST(MemoryTest, WordRegistersAreComposedOfSubValues) {
    Memory mem;

    auto refB = mem.get_register(Register::B);
    auto refC = mem.get_register(Register::C);

    refB->write8(0x34);
    refC->write8(0x12);

    auto refBC = mem.get_word_register(WordRegister::BC);
    EXPECT_EQ(refBC->read16(), 0x1234);
}

TEST(MemoryTest, DerefPointsToAddressReadFromMemoryLocation) {
    Memory mem;

    auto testRef = mem.get_word_ref(0xCDEF);
    testRef->write16(0x5678);

    auto derefWith = mem.get_word_ref(0xC000);
    derefWith->write16(0xCDEF);

    auto refFromDeref = mem.deref_word(*derefWith);

    EXPECT_EQ(refFromDeref->read16(), testRef->read16());
    EXPECT_EQ(refFromDeref->read8(), testRef->read8());

    testRef->write16(0xABCD);

    EXPECT_EQ(refFromDeref->read16(), testRef->read16());
    EXPECT_EQ(refFromDeref->read8(), testRef->read8());

}

TEST(MemoryTest, DerefInterpretsOffsetCorrectly) {
    Memory mem;

    mem.get_word_ref(0xC100)->write16(0x1234);
    mem.get_word_ref(0xC104)->write16(0x5678);

    auto derefWithBase = mem.get_word_ref(0xC200);
    derefWithBase->write16(0xC102);

    EXPECT_EQ(mem.deref_word(*derefWithBase, -2)->read16(), 0x1234);
    EXPECT_EQ(mem.deref_word(*derefWithBase, 2)->read16(), 0x5678);
}
