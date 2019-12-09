#pragma once

#include "memory/ByteAddressable.h"
#include <memory>

namespace GameBoy {

class NewByteReference {
public:
    NewByteReference(std::unique_ptr<ByteAddressable>);

    NewByteReference(const NewByteReference&);
    auto operator=(const NewByteReference&) -> NewByteReference& = delete;

    NewByteReference(NewByteReference&&) = delete;
    auto operator=(NewByteReference &&) -> NewByteReference& = delete;

    operator uint8_t();
    auto operator=(uint8_t value) -> void;

private:
    std::unique_ptr<ByteAddressable> m_ref;
};

}
