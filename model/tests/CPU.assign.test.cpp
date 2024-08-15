#include <catch2/catch_test_macros.hpp>

#include "mock/Helper.hpp"
#include "model/CPU.hpp"

namespace
{

struct CpuFixture
{
    Mock::TestKit testKit;
    model::CPU&   cpu = testKit.cpu;
};

SCENARIO_METHOD( CpuFixture, "CPU assigns register VA to register V0 using opcode 8XY0", "[assign]" )
{
    GIVEN( "A CPU with an initialized register VA" )
    {
        cpu.writeRegister( model::chip8::reg::va, 0xCC );

        WHEN( "the CPU executes a 80A0 opcode" )
        {
            cpu.execute( 0x80A0 );

            THEN( "the value of register VA is copied to register V0" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v0 ) == 0xCC );
            }
            AND_THEN( "the source register VA remains unchanged" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::va ) == 0xCC );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture, "CPU assigns register VA to register VF using opcode 8XY0", "[assign]" )
{
    GIVEN( "A CPU with an initialized register VA" )
    {
        cpu.writeRegister( model::chip8::reg::va, 0xDD );

        WHEN( "the CPU executes a 8FA0 opcode" )
        {
            cpu.execute( 0x8FA0 );

            THEN( "the value of register VA is copied to register VF" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::vf ) == 0xDD );
            }
            AND_THEN( "the source register VA remains unchanged" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::va ) == 0xDD );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture, "CPU assigns a register to itself using opcode 8XY0", "[assign]" )
{
    GIVEN( "A CPU with an initialized register V1" )
    {
        cpu.writeRegister( model::chip8::reg::v1, 0x1D );

        WHEN( "the CPU executes a 8110 opcode" )
        {
            cpu.execute( 0x8000 );

            THEN( "the source register V0 remains unchanged" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v1 ) == 0x1D );
            }
        }
    }
}

} // namespace
