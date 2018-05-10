#ifndef CORE8_IOCONNECTORMOCK_HPP
#define CORE8_IOCONNECTORMOCK_HPP

#include <array>

#include "Chip8.hpp"
#include "IoDevice.hpp"

namespace Aux {

class IoDeviceMock : public model::IoDevice {
  public:
    virtual void drawScreen(
        const std::array<model::chip8::byte_t, model::chip8::display_size>& /*frame*/
    ) override { }

    virtual bool isKeyPressed(const model::chip8::key key) const override {
      return key == pressedKey;
    }

    virtual model::chip8::key getPressedKey() const override {
      return pressedKey;
    }

    void setPressedKey(const model::chip8::key key) {
      pressedKey = key;
    }

  private:
    model::chip8::key pressedKey{model::chip8::key::none};
};

} // namespace Aux

#endif