#include "VM.hpp"

#include <fstream>

#include "IoDevice.hpp"

namespace model
{

VM::VM( IoDevice& ioDevice )
: m_ioDevice{ ioDevice }
, m_cpu{ m_mmu, m_ioDevice, m_rng }
{
}

bool VM::loadRom( const std::string& fileName )
{
    std::ifstream in{ fileName, std::ios::binary };

    if ( in.is_open() )
    {
        m_mmu.load( in, Chip8::init_rom_load_address );
        in.close();
    }

    return true;
}

void VM::cycle()
{
    m_cpu.cycle();
}

} // namespace model
