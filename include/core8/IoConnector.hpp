#ifndef CORE8_IOCONNECTOR_HPP
#define CORE8_IOCONNECTOR_HPP

#include <array>

#include "Chip8.hpp"

namespace Core8 {

class IoConnector {
  public:
    virtual void drawScreen(const std::array<Chip8::BYTE, Chip8::DISPLAY_SIZE>& frame) = 0;

    virtual bool isKeyPressed(const Chip8::KEY key) const = 0;
};

} // namespace Core8

#endif
