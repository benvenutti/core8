#ifndef CORE8_RANDOMNUMBERGENERATORMOCK_HPP
#define CORE8_RANDOMNUMBERGENERATORMOCK_HPP

#include "RandomNumberGenerator.hpp"

namespace Aux {

class RandomNumberGeneratorMock : public model::RandomNumberGenerator {
  public:
    RandomNumberGeneratorMock() = default;
    virtual ~RandomNumberGeneratorMock() = default;

    virtual model::Chip8::byte_t get() override {
      return m_value;
    }

    void setValue(const model::Chip8::byte_t value) {
      m_value = value;
    }

  private:
    model::Chip8::byte_t m_value{0u};
};

} // namespace Aux

#endif