#ifndef CORE8_IOCONNECTOR_HPP
#define CORE8_IOCONNECTOR_HPP

#include <array>

#include "Chip8.hpp"

namespace Core8 {

class IoDevice {
  public:
    virtual ~IoDevice() = default;

    virtual void drawScreen(const std::array<Chip8::BYTE, Chip8::DISPLAY_SIZE>& frame) = 0;

    virtual bool isKeyPressed(const Chip8::Key key) const = 0;

    virtual Chip8::Key getPressedKey() const = 0;
};

} // namespace Core8

#endif
