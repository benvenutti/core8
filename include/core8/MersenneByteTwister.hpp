#ifndef CORE8_MERSENNETWISTER_HPP
#define CORE8_MERSENNETWISTER_HPP

#include <random>

#include "Chip8.hpp"

namespace Core8 {

class MersenneTwister : public RandomNumberGenerator {
  public:
    MersenneTwister() = default;
    virtual ~MersenneTwister() = default;

    virtual Chip8::BYTE get() override {
      return m_distribution(m_generator);
    }

  private:
    std::random_device m_device;
    std::mt19937 m_generator{m_device};
    std::uniform_int_distribution<Chip8::BYTE> m_distribution{0x01, 0xFF};
};

} // namespace Core8

#endif