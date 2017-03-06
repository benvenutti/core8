#ifndef CORE8_MERSENNETWISTER_HPP
#define CORE8_MERSENNETWISTER_HPP

#include <random>

#include "Chip8.hpp"

namespace Core8 {

class MersenneByteTwister : public RandomNumberGenerator {
  public:
    MersenneByteTwister() = default;
    virtual ~MersenneByteTwister() = default;

    virtual Chip8::BYTE get() override {
      return m_distribution(m_generator);
    }

  private:
    std::mt19937 m_generator{std::random_device{}()};
    std::uniform_int_distribution<Chip8::BYTE> m_distribution{0x01, 0xFF};
};

} // namespace Core8

#endif