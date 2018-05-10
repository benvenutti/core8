#ifndef CORE8_IOCONNECTORMOCK_HPP
#define CORE8_IOCONNECTORMOCK_HPP

#include <array>

#include "Chip8.hpp"
#include "IoDevice.hpp"

namespace Aux {

class IoDeviceMock : public model::IoDevice {
  public:
    virtual void drawScreen(
        const std::array<model::Chip8::byte_t, model::Chip8::display_size>& /*frame*/
    ) override { }

    virtual bool isKeyPressed(const model::Chip8::key key) const override {
      return key == pressedKey;
    }

    virtual model::Chip8::key getPressedKey() const override {
      return pressedKey;
    }

    void setPressedKey(const model::Chip8::key key) {
      pressedKey = key;
    }

  private:
    model::Chip8::key pressedKey{model::Chip8::key::NONE};
};

} // namespace Aux

#endif