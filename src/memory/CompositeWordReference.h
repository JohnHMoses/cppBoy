#pragma once

#include "memory/ByteAddressable.h"
#include "memory/WordAddressable.h"

#include <memory>

namespace GameBoy {

class ByteAddressable;

class CompositeWordReference : public WordAddressable {
public:
    CompositeWordReference(std::unique_ptr<ByteAddressable>&& lower, std::unique_ptr<ByteAddressable>&& upper);
    ~CompositeWordReference() override;

    auto clone() -> std::unique_ptr<WordAddressable> override;

    auto as_byte_address() -> std::unique_ptr<ByteAddressable> override;

    auto read8() -> uint8_t override;
    auto read16() -> uint16_t override;

    auto write8(uint8_t value) -> void override;
    auto write16(uint16_t value) -> void override;

private:
    std::unique_ptr<ByteAddressable> m_lower;
    std::unique_ptr<ByteAddressable> m_upper;
};

}
