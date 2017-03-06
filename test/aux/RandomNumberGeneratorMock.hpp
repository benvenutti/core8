#ifndef CORE8_RANDOMNUMBERGENERATORMOCK_HPP
#define CORE8_RANDOMNUMBERGENERATORMOCK_HPP

#include "RandomNumberGenerator.hpp"

namespace Aux {

class RandomNumberGeneratorMock : public Core8::RandomNumberGenerator {
  public:
    RandomNumberGeneratorMock() = default;
    virtual ~RandomNumberGeneratorMock() = default;

    virtual Core8::Chip8::BYTE get() override {
      return m_value;
    }

    void setValue(const Core8::Chip8::BYTE value) {
      m_value = value;
    }

  private:
    Core8::Chip8::BYTE m_value{0u};
};

} // namespace Aux

#endif