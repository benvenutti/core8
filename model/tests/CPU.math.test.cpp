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

SCENARIO_METHOD( CpuFixture,
                 "CPU adds register Y to register X using 8XY4 opcode "
                 "without the need for a carry",
                 "[math]" )
{
    GIVEN( "A CPU with some initialized registers" )
    {
        cpu.writeRegister( model::chip8::reg::v1, 0x11 );
        cpu.writeRegister( model::chip8::reg::v4, 0x35 );

        WHEN( "the CPU executes a 8XY4 opcode" )
        {
            cpu.execute( 0x8144 );

            THEN( "the value of VY is added to VX" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v1 ) == 0x46 );
            }
            AND_THEN( "VF is set to 0 since there is no need for a carry" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::vf ) == 0x0 );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU adds register Y to register X using 8XY4 opcode "
                 "with the need for a carry",
                 "[math]" )
{
    GIVEN( "A CPU with some initialized registers" )
    {
        cpu.writeRegister( model::chip8::reg::v1, 0x11 );
        cpu.writeRegister( model::chip8::reg::v5, 0xFE );

        WHEN( "the CPU executes a 8XY4 opcode" )
        {
            cpu.execute( 0x8154 );

            THEN( "the value of VY is added to VX (with an overflow)" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v1 ) == 0xF );
            }
            AND_THEN( "VF is set to 1 since there is a carry" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::vf ) == 0x1 );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU subtracts register Y from register X using 8XY5 opcode "
                 "without the need for a borrow",
                 "[math]" )
{
    GIVEN( "A CPU with some initialized registers" )
    {
        cpu.writeRegister( model::chip8::reg::va, 0xA3 );
        cpu.writeRegister( model::chip8::reg::vb, 0x15 );

        WHEN( "the CPU executes a 8XY5 opcode" )
        {
            cpu.execute( 0x8AB5 );

            THEN( "the value of VY is subtracted from VX" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::va ) == 0x8E );
            }
            AND_THEN( "VF is set to 1 since there is no borrow" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::vf ) == 0x1 );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU subtracts register Y from register X using 8XY5 opcode "
                 "with the need for a borrow",
                 "[math]" )
{
    GIVEN( "A CPU with some initialized registers" )
    {
        cpu.writeRegister( model::chip8::reg::va, 0xA3 );
        cpu.writeRegister( model::chip8::reg::vc, 0xFF );

        WHEN( "the CPU executes a 8XY5 opcode" )
        {
            cpu.execute( 0x8AC5 );

            THEN( "the value of VY is subtracted from VX" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::va ) == 0xA4 );
            }
            AND_THEN( "VF is set to 0 since there is a borrow" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::vf ) == 0x0 );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU executes opcode 8XY7 to "
                 "subtract register X from register Y (storing the result in VX) "
                 "without the need for a borrow",
                 "[math]" )
{
    GIVEN( "A CPU with some initialized registers" )
    {
        cpu.writeRegister( model::chip8::reg::v3, 0x3F );
        cpu.writeRegister( model::chip8::reg::v4, 0xBB );

        WHEN( "the CPU executes a 8XY7 opcode" )
        {
            cpu.execute( 0x8347 );

            THEN( "the the result of VY minus VX is stored in VX" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v3 ) == 0x7C );
            }
            AND_THEN( "VF is set to 1 since there is no borrow" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::vf ) == 0x1 );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU executes opcode 8XY7 to "
                 "subtract register X from register Y (storing the result in VX) "
                 "with the need for a borrow",
                 "[math]" )
{
    GIVEN( "A CPU with some initialized registers" )
    {
        cpu.writeRegister( model::chip8::reg::v4, 0xBB );
        cpu.writeRegister( model::chip8::reg::v5, 0xFF );

        WHEN( "the CPU executes a 8XY7 opcode" )
        {
            cpu.execute( 0x8547 );

            THEN( "the the result of VY minus VX is stored in VX" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v5 ) == 0xBC );
            }
            AND_THEN( "VF is set to 1 since there is a borrow" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::vf ) == 0x0 );
            }
        }
    }
}

} // namespace
