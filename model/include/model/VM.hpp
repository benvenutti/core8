#pragma once

#include <string>

#include "CPU.hpp"
#include "MMU.hpp"
#include "MersenneByteTwister.hpp"

namespace model
{

class IoDevice;

class VM
{
public:
    explicit VM( IoDevice& ioDevice );

    bool loadRom( const std::string& fileName );

    void cycle();

    const MMU& getMMU() const
    {
        return m_mmu;
    }

    const CPU& getCPU() const
    {
        return m_cpu;
    }

    CPU& getCPU()
    {
        return m_cpu;
    }

private:
    IoDevice&           m_ioDevice;
    MMU                 m_mmu;
    MersenneByteTwister m_rng;
    CPU                 m_cpu;
};

} // namespace model
