#pragma once

#include "memory/WordAddressable.h"
#include <memory>

namespace GameBoy {

class NewWordReference {
public:
    NewWordReference(std::unique_ptr<WordAddressable>);

    NewWordReference(const NewWordReference&);
    auto operator=(const NewWordReference&) -> NewWordReference& = delete;

    NewWordReference(NewWordReference&&) = delete;
    auto operator=(NewWordReference &&) -> NewWordReference& = delete;

    operator uint16_t();
    auto operator=(uint16_t value) -> void;

private:
    std::unique_ptr<WordAddressable> m_ref;
};

}
