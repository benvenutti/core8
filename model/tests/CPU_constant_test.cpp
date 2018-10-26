#include <catch.hpp>

#include "aux/Aux.hpp"
#include "model/CPU.hpp"

namespace
{

struct CpuFixture
{
    Aux::TestKit testKit;
    model::CPU&  cpu = testKit.cpu;
};

SCENARIO_METHOD( CpuFixture, "CPU loads constant NN to register VX using opcode 6XNN", "[constant]" )
{
    GIVEN( "A CPU" )
    {
        WHEN( "the CPU executes a 6XNN opcode" )
        {
            cpu.execute( 0x60FF );
            cpu.execute( 0x6F01 );

            THEN( "the constant NN is loaded to register VX" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v0 ) == 0xFF );
                REQUIRE( cpu.readRegister( model::chip8::reg::vf ) == 0x1 );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture, "CPU adds constant NN to register VX using opcode 7XNN", "[constant]" )
{
    GIVEN( "A CPU with initialized registers" )
    {
        cpu.writeRegister( model::chip8::reg::v3, 0x00 );
        cpu.writeRegister( model::chip8::reg::vf, 0xFE );

        WHEN( "the CPU executes a 7XNN opcode" )
        {
            cpu.execute( 0x7301 );
            cpu.execute( 0x7F01 );

            THEN( "the constant NN is added to register VX" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v3 ) == 0x1 );
                REQUIRE( cpu.readRegister( model::chip8::reg::vf ) == 0xFF );
            }
        }
    }
}

} // namespace
