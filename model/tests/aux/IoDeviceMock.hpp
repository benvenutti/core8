#ifndef CORE8_IOCONNECTORMOCK_HPP
#define CORE8_IOCONNECTORMOCK_HPP

#include <array>

#include "Chip8.hpp"
#include "IoDevice.hpp"

namespace Aux {

class IoDeviceMock : public Core8::IoDevice {
  public:
    virtual void drawScreen(
        const std::array<Core8::Chip8::byte_t, Core8::Chip8::display_size>& /*frame*/
    ) override { }

    virtual bool isKeyPressed(const Core8::Chip8::key key) const override {
      return key == pressedKey;
    }

    virtual Core8::Chip8::key getPressedKey() const override {
      return pressedKey;
    }

    void setPressedKey(const Core8::Chip8::key key) {
      pressedKey = key;
    }

  private:
    Core8::Chip8::key pressedKey{Core8::Chip8::key::NONE};
};

} // namespace Aux

#endif