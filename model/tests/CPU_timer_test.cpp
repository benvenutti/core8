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

SCENARIO_METHOD( CpuFixture, "CPU sets register X to the value of the delay timer using FX02 opcode", "[memory]" )
{
    GIVEN( "A CPU with an initialized delay timer" )
    {
        const model::chip8::byte_t delay{ 0x3C };
        cpu.setDelayTimer( delay );

        WHEN( "the CPU executes a FX07 opcode" )
        {
            cpu.execute( 0xF007 );
            cpu.execute( 0xFE07 );

            THEN( "the target register VX holds a copy of the delay timer value" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v0 ) == delay );
                REQUIRE( cpu.readRegister( model::chip8::reg::ve ) == delay );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture, "CPU sets the delay timer to the value of register X using FX15 opcode", "[memory]" )
{
    GIVEN( "A CPU with initialized registers" )
    {
        cpu.writeRegister( model::chip8::reg::v0, 0x2A );
        cpu.writeRegister( model::chip8::reg::vf, 0xCD );

        WHEN( "the CPU executes a FX15 opcode" )
        {
            cpu.execute( 0xF015 );
            const auto delay1 = cpu.getDelayTimer();

            cpu.execute( 0xFF15 );
            const auto delay2 = cpu.getDelayTimer();

            THEN( "the delay timer is updated to the value of the register VX" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v0 ) == delay1 );
                REQUIRE( cpu.readRegister( model::chip8::reg::vf ) == delay2 );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture, "CPU sets the sound timer to the value of register X using FX15 opcode", "[memory]" )
{
    GIVEN( "A CPU with initialized registers" )
    {
        cpu.writeRegister( model::chip8::reg::v0, 0xBE );
        cpu.writeRegister( model::chip8::reg::vf, 0xFE );

        WHEN( "the CPU executes a FX18 opcode" )
        {
            cpu.execute( 0xF018 );
            const auto sound1 = cpu.getSoundTimer();

            cpu.execute( 0xFF18 );
            const auto sound2 = cpu.getSoundTimer();

            THEN( "the sound timer is updated to the value of the register VX" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v0 ) == sound1 );
                REQUIRE( cpu.readRegister( model::chip8::reg::vf ) == sound2 );
            }
        }
    }
}

} // namespace
