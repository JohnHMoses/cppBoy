#pragma once

#include "memory/ByteAddressable.h"
#include <memory>

namespace GameBoy {

class BytePointer {
    class _reference {
    public:
        _reference(ByteAddressable&);

        operator uint8_t();
        auto operator=(uint8_t) -> void;

    private:
        ByteAddressable& m_ref;
    };

public:
    BytePointer(std::unique_ptr<ByteAddressable>);

    BytePointer(const BytePointer&);
    auto operator=(const BytePointer&) -> BytePointer& = delete;

    BytePointer(BytePointer&&) = delete;
    auto operator=(BytePointer &&) -> BytePointer& = delete;

    auto operator*() -> _reference;

private:
    std::unique_ptr<ByteAddressable> m_ref;
};

}
