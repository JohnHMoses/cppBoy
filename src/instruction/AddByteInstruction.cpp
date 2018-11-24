#include "instruction/AddByteInstruction.h"
#include "CPU.h"
#include "memory/FlagRegister.h"
#include "util/FlagHelpers.h"

namespace GameBoy {

using namespace std;

AddByteInstruction::AddByteInstruction(unique_ptr<ByteAddressable>&& fromRef, unique_ptr<ByteAddressable>&& toRef)
    : m_fromRef(move(fromRef))
    , m_toRef(move(toRef)) {};

AddByteInstruction::~AddByteInstruction() = default;

auto AddByteInstruction::perform_operation(CPU& cpu) -> void
{
    using namespace FlagHelpers::Add;

    auto fromValue = m_fromRef->read8();
    auto toValue = m_toRef->read8();
    auto flagRegister = cpu.get_flags();
    auto res = fromValue + toValue;

    flagRegister.set_zero(res == 0);
    flagRegister.set_substract(false);
    flagRegister.set_half_carry(should_half_carry(fromValue, toValue));
    flagRegister.set_carry(should_carry(fromValue, toValue));

    m_toRef->write8(res);
}

}
