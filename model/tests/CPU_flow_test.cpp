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

SCENARIO_METHOD( CpuFixture, "CPU executes an unconditional jump to address NNN with opcode 1NNN", "[flow]" )
{
    GIVEN( "A CPU" )
    {
        WHEN( "the CPU executes an 1NNN opcode" )
        {
            cpu.execute( 0x1ABC );

            THEN( "the program counter is updated to the value of NNN" )
            {
                REQUIRE( cpu.getPc() == 0xABC );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture, "CPU calls a subroutine with opcode 2NNN", "[flow]" )
{
    GIVEN( "A CPU" )
    {
        WHEN( "the CPU calls a subroutine executing a 2NNN opcode" )
        {
            const auto originalPc = cpu.getPc();
            const auto originalSp = cpu.getSp();
            cpu.execute( 0x2656 );

            THEN( "the program counter is pushed to the call stack" )
            {
                REQUIRE( cpu.getStack().at( originalSp ) == originalPc );
            }
            AND_THEN( "the stack pointer is incremented" )
            {
                REQUIRE( cpu.getSp() == originalSp + 1u );
            }
            AND_THEN( "the program counter is updated to the value of NNN" )
            {
                REQUIRE( cpu.getPc() == 0x656 );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture, "CPU returns from subroutine with opcode 00EE", "[flow]" )
{
    GIVEN( "A CPU executing a subroutine" )
    {
        cpu.execute( 0x2ABC );
        const auto sp              = cpu.getSp();
        const auto previousAddress = cpu.getStack().at( sp - 1u );

        WHEN( "the CPU executes a 00EE operation to return from a subroutine" )
        {
            cpu.execute( 0x00EE );

            THEN( "the call stack topmost value is assigned to the program counter" )
            {
                REQUIRE( cpu.getPc() == previousAddress );
            }
            AND_THEN( "the stack pointer is decremented" )
            {
                REQUIRE( cpu.getSp() == sp - 1u );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU executes an unconditional jump with opcode BNNN"
                 "to address NNN plus register V0",
                 "[flow]" )
{
    GIVEN( "A CPU with initialized register" )
    {
        cpu.writeRegister( model::Chip8::registers::V0, 0x2D );

        WHEN( "the CPU executes an BNNN operation" )
        {
            cpu.execute( 0xB131 );

            THEN( "the program counter is updated to the value of NNN plus V0" )
            {
                REQUIRE( cpu.getPc() == 0x15E );
            }
        }
    }
}

} // namespace
