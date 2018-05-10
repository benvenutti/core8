#include <algorithm>
#include <vector>

#include <catch.hpp>

#include "CPU.hpp"
#include "aux/Aux.hpp"

namespace
{

struct CpuFixture
{
    Aux::TestKit testKit;
    model::MMU&  mmu = testKit.mmu;
    model::CPU&  cpu = testKit.cpu;
};

SCENARIO_METHOD( CpuFixture, "CPU sets I to the address NNN using opcode ANNN", "[memory]" )
{
    GIVEN( "A CPU" )
    {
        WHEN( "the CPU executes a ANNN operation" )
        {
            cpu.execute( 0xA123 );
            const auto address1 = cpu.getI();
            cpu.execute( 0xAFFF );
            const auto address2 = cpu.getI();

            THEN( "the address NNN is loaded into the address register I" )
            {
                REQUIRE( 0x123 == address1 );
                REQUIRE( 0xFFF == address2 );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU stores registers V0 to VX in memory starting at address I "
                 "using the FX55 opcode",
                 "[memory]" )
{
    GIVEN( "A CPU with initialized V and I registers" )
    {
        const model::chip8::word_t address{ 1024 };
        cpu.setI( address );

        const std::vector<model::chip8::byte_t> bytes{ 0x10, 0x11, 0x12, 0x13, 0x24, 0x25, 0x26, 0x27,
                                                       0x38, 0x39, 0x3A, 0x3B, 0x4C, 0x4D, 0x4E, 0x4F };
        cpu.loadToRegisters( bytes );

        WHEN( "the CPU executes a FX55 opcode" )
        {
            cpu.execute( 0xFF55 );

            THEN( "the registers from V0 to VX are stored in memory" )
            {
                for ( auto i = 0u; i <= 0xFu; ++i )
                {
                    const auto r = cpu.readRegister( static_cast<model::chip8::reg>( i ) );
                    const auto m = mmu.readByte( address + i );
                    REQUIRE( r == m );
                }
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU fills registers V0 to VX in memory starting at address I "
                 "using the FX65 opcode",
                 "[memory]" )
{
    GIVEN( "A CPU with initialized memory and register I" )
    {
        const model::chip8::word_t address{ 1024 };
        cpu.setI( address );

        const std::vector<model::chip8::byte_t> bytes = { 0x10, 0x11, 0x12, 0x13, 0x24, 0x25 };
        mmu.load( bytes, address );

        WHEN( "the CPU executes a FX65 opcode" )
        {
            cpu.execute( 0xF565 );

            THEN( "registers V0 to VX are filled with values from memory" )
            {
                for ( auto i = 0u; i <= 0x5; ++i )
                {
                    const auto r = cpu.readRegister( static_cast<model::chip8::reg>( i ) );
                    const auto m = mmu.readByte( address + i );
                    REQUIRE( r == m );
                }
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture, "CPU adds register X to register I using FX1E opcode", "[memory]" )
{
    GIVEN( "A CPU with registers V and I initialized" )
    {
        cpu.writeRegister( model::chip8::reg::v0, 10 );
        cpu.writeRegister( model::chip8::reg::ve, 66 );
        cpu.setI( 512 );

        WHEN( "the CPU executes a FX1E opcode" )
        {
            cpu.execute( 0xF01E );
            const auto address1 = cpu.getI();

            cpu.execute( 0xFE1E );
            const auto address2 = cpu.getI();

            THEN( "the value of register VX is added to register I" )
            {
                REQUIRE( 522 == address1 );
                REQUIRE( 588 == address2 );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU sets I to the location of the sprite for the character in VX "
                 "using FX29 opcode",
                 "[memory]" )
{
    GIVEN( "A CPU with initialized registers" )
    {
        cpu.writeRegister( model::chip8::reg::v0, 0x0 );
        cpu.writeRegister( model::chip8::reg::ve, 0xF );

        WHEN( "the CPU executes a FX29 opcode" )
        {
            cpu.execute( 0xF029 );
            const auto address1 = cpu.getI();

            cpu.execute( 0xFE29 );
            const auto address2 = cpu.getI();

            THEN( "register I is updated to the address of the character sprite of VX" )
            {
                REQUIRE( address1 == 0 );
                REQUIRE( address2 == 75 );
            }
        }
    }
}

} // namespace
