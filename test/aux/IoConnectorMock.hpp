#ifndef CORE8_IOCONNECTORMOCK_HPP
#define CORE8_IOCONNECTORMOCK_HPP

#include <array>

#include "Chip8.hpp"
#include "IoConnector.hpp"

namespace Aux {

class IoConnectorMock : public Core8::IoConnector {
  public:
    virtual void drawScreen(
        const std::array<Core8::Chip8::BYTE, Core8::Chip8::DISPLAY_SIZE>& /*frame*/
    ) override {

    }

    virtual bool isKeyPressed(const Core8::Chip8::BYTE /*key*/) const override {
      return key == pressedKey;
    }
};

} // namespace Aux

#endif