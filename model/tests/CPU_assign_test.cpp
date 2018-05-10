#include <catch.hpp>

#include "CPU.hpp"
#include "Chip8.hpp"
#include "aux/Aux.hpp"

namespace
{

struct CpuFixture
{
    Aux::TestKit testKit;
    model::CPU&  cpu = testKit.cpu;
};

SCENARIO_METHOD( CpuFixture, "CPU assigns register VA to register V0 using opcode 8XY0", "[assign]" )
{
    GIVEN( "A CPU with an initialized register VA" )
    {
        cpu.writeRegister( model::Chip8::registers::VA, 0xCC );

        WHEN( "the CPU executes a 80A0 opcode" )
        {
            cpu.execute( 0x80A0 );

            THEN( "the value of register VA is copied to register V0" )
            {
                REQUIRE( cpu.readRegister( model::Chip8::registers::V0 ) == 0xCC );
            }
            AND_THEN( "the source register VA remains unchanged" )
            {
                REQUIRE( cpu.readRegister( model::Chip8::registers::VA ) == 0xCC );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture, "CPU assigns register VA to register VF using opcode 8XY0", "[assign]" )
{
    GIVEN( "A CPU with an initialized register VA" )
    {
        cpu.writeRegister( model::Chip8::registers::VA, 0xDD );

        WHEN( "the CPU executes a 8FA0 opcode" )
        {
            cpu.execute( 0x8FA0 );

            THEN( "the value of register VA is copied to register VF" )
            {
                REQUIRE( cpu.readRegister( model::Chip8::registers::VF ) == 0xDD );
            }
            AND_THEN( "the source register VA remains unchanged" )
            {
                REQUIRE( cpu.readRegister( model::Chip8::registers::VA ) == 0xDD );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture, "CPU assigns a register to itself using opcode 8XY0", "[assign]" )
{
    GIVEN( "A CPU with an initialized register V1" )
    {
        cpu.writeRegister( model::Chip8::registers::V1, 0x1D );

        WHEN( "the CPU executes a 8110 opcode" )
        {
            cpu.execute( 0x8000 );

            THEN( "the source register V0 remains unchanged" )
            {
                REQUIRE( cpu.readRegister( model::Chip8::registers::V1 ) == 0x1D );
            }
        }
    }
}

} // namespace
