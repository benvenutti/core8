#include <model/CPU.hpp>

#include <mock/Helper.hpp>

#include <catch2/catch_test_macros.hpp>

namespace
{

struct CpuFixture
{
    Mock::TestKit testKit;
    model::CPU&   cpu = testKit.cpu;
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
                REQUIRE( cpu.pc() == 0xABC );
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
            const auto originalPc = cpu.pc();
            const auto originalSp = cpu.sp();
            cpu.execute( 0x2656 );

            THEN( "the program counter is pushed to the call stack" )
            {
                REQUIRE( cpu.stack().at( originalSp ) == originalPc );
            }
            AND_THEN( "the stack pointer is incremented" )
            {
                REQUIRE( cpu.sp() == originalSp + 1u );
            }
            AND_THEN( "the program counter is updated to the value of NNN" )
            {
                REQUIRE( cpu.pc() == 0x656 );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture, "CPU returns from subroutine with opcode 00EE", "[flow]" )
{
    GIVEN( "A CPU executing a subroutine" )
    {
        cpu.execute( 0x2ABC );
        const auto sp              = cpu.sp();
        const auto previousAddress = cpu.stack().at( sp - 1u );

        WHEN( "the CPU executes a 00EE operation to return from a subroutine" )
        {
            cpu.execute( 0x00EE );

            THEN( "the call stack topmost value is assigned to the program counter" )
            {
                REQUIRE( cpu.pc() == previousAddress );
            }
            AND_THEN( "the stack pointer is decremented" )
            {
                REQUIRE( cpu.sp() == sp - 1u );
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
        cpu.writeRegister( model::chip8::reg::v0, 0x2D );

        WHEN( "the CPU executes an BNNN operation" )
        {
            cpu.execute( 0xB131 );

            THEN( "the program counter is updated to the value of NNN plus V0" )
            {
                REQUIRE( cpu.pc() == 0x15E );
            }
        }
    }
}

} // namespace
