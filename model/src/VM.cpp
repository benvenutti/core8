#include "VM.hpp"

#include <fstream>

#include "IoDevice.hpp"

namespace Core8
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
        m_mmu.load( in, Chip8::INIT_ROM_LOAD_ADDRESS );
        in.close();
    }

    return true;
}

void VM::cycle()
{
    m_cpu.cycle();
}

} // namespace Core8
