#pragma once

namespace GameBoy {

enum class Register {
    A,
    B,
    C,
    D,
    E,
    F,
    H,
    L
};

enum class WordRegister {
    AF,
    BC,
    DE,
    HL,
    SP,
    PC
};

}
