#include <catch.hpp>

#include "mock/Aux.hpp"
#include "model/CPU.hpp"

namespace
{

struct CpuFixture
{
    Mock::TestKit testKit;
    model::CPU&   cpu = testKit.cpu;
};

SCENARIO_METHOD( CpuFixture, "CPUs can execute OR operations on registers with opcode 8XY1", "[bitwise]" )
{
    GIVEN( "A CPU with some initialized registers" )
    {
        cpu.writeRegister( model::chip8::reg::v0, 0b00001000 );
        cpu.writeRegister( model::chip8::reg::v6, 0b01010101 );
        cpu.writeRegister( model::chip8::reg::va, 0b00001111 );
        cpu.writeRegister( model::chip8::reg::ve, 0b11001100 );

        WHEN( "the CPU executes an 8XY1 opcode" )
        {
            cpu.execute( 0x8061 );
            cpu.execute( 0x8AE1 );

            THEN( "the register VX holds the result of VX OR VY" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v0 ) == 0b01011101 );
                REQUIRE( cpu.readRegister( model::chip8::reg::va ) == 0b11001111 );
            }
            AND_THEN( "the register VY remains unchanged" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v6 ) == 0b01010101 );
                REQUIRE( cpu.readRegister( model::chip8::reg::ve ) == 0b11001100 );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture, "CPUs can execute AND operations on registers with opcode 8XY2", "[bitwise]" )
{
    GIVEN( "A CPU with some initialized registers" )
    {
        cpu.writeRegister( model::chip8::reg::v1, 0b01011000 );
        cpu.writeRegister( model::chip8::reg::v7, 0b01010101 );
        cpu.writeRegister( model::chip8::reg::vb, 0b00001111 );
        cpu.writeRegister( model::chip8::reg::vf, 0b11001100 );

        WHEN( "the CPU executes an 8XY2 opcode" )
        {
            cpu.execute( 0x8172 );
            cpu.execute( 0x8BF2 );

            THEN( "the register VX holds the result of VX AND VY" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v1 ) == 0b01010000 );
                REQUIRE( cpu.readRegister( model::chip8::reg::vb ) == 0b00001100 );
            }
            AND_THEN( "the register VY remains unchanged" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v7 ) == 0b01010101 );
                REQUIRE( cpu.readRegister( model::chip8::reg::vf ) == 0b11001100 );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture, "CPUs can execute XOR operations on registers with opcode 8XY3", "[bitwise]" )
{
    GIVEN( "A CPU with some initialized registers" )
    {
        cpu.writeRegister( model::chip8::reg::v2, 0b01011000 );
        cpu.writeRegister( model::chip8::reg::v8, 0b01010101 );
        cpu.writeRegister( model::chip8::reg::vc, 0b00001111 );
        cpu.writeRegister( model::chip8::reg::vd, 0b11001100 );

        WHEN( "the CPU executes an 8XY3 opcode" )
        {
            cpu.execute( 0x8283 );
            cpu.execute( 0x8CD3 );

            THEN( "the register VX holds the result of VX XOR VY" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v2 ) == 0b00001101 );
                REQUIRE( cpu.readRegister( model::chip8::reg::vc ) == 0b11000011 );
            }
            AND_THEN( "the register VY remains unchanged" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v8 ) == 0b01010101 );
                REQUIRE( cpu.readRegister( model::chip8::reg::vd ) == 0b11001100 );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture, "CPUs can shift registers right by one with 8XY6 opcode", "[bitwise]" )
{
    GIVEN( "A CPU with some initialized registers" )
    {
        cpu.writeRegister( model::chip8::reg::v4, 0b01011000 );
        cpu.writeRegister( model::chip8::reg::vd, 0b01010101 );

        WHEN( "the CPU executes an 8XY6 opcode" )
        {
            cpu.execute( 0x8406 );
            const auto vf1 = cpu.readRegister( model::chip8::reg::vf );

            cpu.execute( 0x8D06 );
            const auto vf2 = cpu.readRegister( model::chip8::reg::vf );

            THEN( "the target register VX is shifted right by one" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v4 ) == 0b00101100 );
                REQUIRE( cpu.readRegister( model::chip8::reg::vd ) == 0b00101010 );
            }
            AND_THEN( "VF is set to the LSB of the target register before the shift" )
            {
                REQUIRE( vf1 == 0b0 );
                REQUIRE( vf2 == 0b1 );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture, "CPUs can shift registers left by one with 8XYE opcode", "[bitwise]" )
{
    GIVEN( "A CPU with some initialized registers" )
    {
        cpu.writeRegister( model::chip8::reg::vc, 0b11111111 );
        cpu.writeRegister( model::chip8::reg::vd, 0b01010101 );

        WHEN( "the CPU executes an 8XYE opcode" )
        {
            cpu.execute( 0x8C0E );
            const auto vf1 = cpu.readRegister( model::chip8::reg::vf );

            cpu.execute( 0x8D0E );
            const auto vf2 = cpu.readRegister( model::chip8::reg::vf );

            THEN( "the target register VX is shifted left by one" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::vc ) == 0b11111110 );
                REQUIRE( cpu.readRegister( model::chip8::reg::vd ) == 0b10101010 );
            }
            AND_THEN( "VF is set to the MSB of the target register before the shift" )
            {
                REQUIRE( vf1 == 0b1 );
                REQUIRE( vf2 == 0b0 );
            }
        }
    }
}

} // namespace
