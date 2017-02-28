#include "VM.hpp"

#include <fstream>

#include "IoConnector.hpp"

namespace Core8 {

VM::VM(IoConnector& ioConnector)
    : m_ioConnector{ioConnector},
      m_cpu{m_mmu, m_ioConnector, m_rng} { }

bool VM::loadRom(const std::string& fileName) {
  std::ifstream in{fileName, std::ios::binary};

  if (in.is_open()) {
    m_mmu.load(in, Chip8::INIT_ROM_LOAD_ADDRESS);
    in.close();
  }

  return true;
}

void VM::cycle() {
  m_cpu.fetch();
  m_cpu.decode();
  m_cpu.execute();
  m_cpu.updateDelayTimer();
  m_cpu.updateSoundTimer();
}

} // namespace Core8
