#include "VM.hpp"

#include <fstream>
#include <iterator>

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
        const std::vector<chip8::byte_t> data{ std::istream_iterator<chip8::byte_t>{ in },
                                               std::istream_iterator<chip8::byte_t>{} };

        in.close();
        m_mmu.load( data, chip8::init_rom_load_address );
    }

    return true; // TODO this is always returnign true...
}

void VM::cycle()
{
    m_cpu.cycle();
}

} // namespace model
