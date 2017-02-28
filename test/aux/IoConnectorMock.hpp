#ifndef CORE8_IOCONNECTORMOCK_HPP
#define CORE8_IOCONNECTORMOCK_HPP

#include <array>

#include "Chip8.hpp"
#include "IoDevice.hpp"

namespace Aux {

class IoConnectorMock : public Core8::IoConnector {
  public:
    virtual void drawScreen(
        const std::array<Core8::Chip8::BYTE, Core8::Chip8::DISPLAY_SIZE>& /*frame*/
    ) override { }

    virtual bool isKeyPressed(const Core8::Chip8::KEY key) const override {
      return key == pressedKey;
    }

    virtual Core8::Chip8::KEY getPressedKey() const override {
      return pressedKey;
    }

    void setPressedKey(const Core8::Chip8::KEY key) {
      pressedKey = key;
    }

  private:
    Core8::Chip8::KEY pressedKey{Core8::Chip8::KEY::NONE};
};

} // namespace Aux

#endif