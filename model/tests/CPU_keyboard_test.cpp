#include <catch.hpp>

#include "CPU.hpp"
#include "aux/Aux.hpp"

namespace
{

struct CpuFixture
{
    Aux::TestKit       testKit;
    model::CPU&        cpu      = testKit.cpu;
    Aux::IoDeviceMock& ioDevice = testKit.ioDevice;
};

SCENARIO_METHOD( CpuFixture,
                 "CPU skips next instruction with EX9E opcode "
                 "when the key pressed is equal to register VX",
                 "[keyboard]" )
{
    GIVEN( "A CPU with V0 set to 0 and an i/o connector with the key 0 pressed" )
    {
        cpu.writeRegister( model::chip8::reg::v0, 0u );
        ioDevice.setPressedKey( model::chip8::key::k0 );
        const auto originalPc = cpu.getPc();

        WHEN( "the CPU executes an EX9E operation with X equal to 0" )
        {
            cpu.execute( 0xE09E );

            THEN( "the program counter is updated to skip the next instruction" )
            {
                REQUIRE( cpu.getPc() == originalPc + model::chip8::instruction_size_in_bytes );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU does not skip next instruction with EX9E opcode "
                 "when the key pressed is not equal to register VX",
                 "[keyboard]" )
{
    GIVEN( "A CPU with V0 set to 0 and an i/o connector with the key 1 pressed" )
    {
        cpu.writeRegister( model::chip8::reg::v0, 0u );
        ioDevice.setPressedKey( model::chip8::key::k1 );
        const auto originalPc = cpu.getPc();

        WHEN( "the CPU executes an EX9E operation with X equal to 0" )
        {
            cpu.execute( 0xE09E );

            THEN( "the program counter remains unchanged" )
            {
                REQUIRE( cpu.getPc() == originalPc );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU skips next instruction with EXA1 opcode "
                 "when the key pressed is not equal to register VX",
                 "[keyboard]" )
{
    GIVEN( "A CPU with V0 set to 1 and an i/o connector with the key 0 pressed" )
    {
        cpu.writeRegister( model::chip8::reg::v0, 1u );
        ioDevice.setPressedKey( model::chip8::key::k0 );
        const auto originalPc = cpu.getPc();

        WHEN( "the CPU executes an EXA1 operation with X equal to 0" )
        {
            cpu.execute( 0xE0A1 );

            THEN( "the program counter is updated to skip the next instruction" )
            {
                REQUIRE( cpu.getPc() == originalPc + model::chip8::instruction_size_in_bytes );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU does not skip next instruction with EXA1 opcode "
                 "when the key pressed is equal to register VX",
                 "[keyboard]" )
{
    GIVEN( "A CPU with V0 set to 0 and an i/o connector with the key 0 pressed" )
    {
        cpu.writeRegister( model::chip8::reg::v0, 0u );
        ioDevice.setPressedKey( model::chip8::key::k0 );
        const auto originalPc = cpu.getPc();

        WHEN( "the CPU executes an EXA1 operation with X equal to 0" )
        {
            cpu.execute( 0xE0A1 );

            THEN( "the program counter is updated to skip the next instruction" )
            {
                REQUIRE( cpu.getPc() == originalPc );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU does not update the program counter with FX0A opcode "
                 "when there is no key pressed",
                 "[keyboard]" )
{
    GIVEN( "A CPU and an i/o connector with no key pressed" )
    {
        ioDevice.setPressedKey( model::chip8::key::none );
        const auto originalPc = cpu.getPc();
        const auto originalV0 = cpu.readRegister( model::chip8::reg::v0 );

        WHEN( "the CPU executes an FX0A" )
        {
            cpu.execute( 0xF00A );

            THEN( "the program counter remains unchanged (the CPU is halted)" )
            {
                REQUIRE( cpu.getPc() == originalPc );
            }
            AND_THEN( "register V0 remains unchanged" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v0 ) == originalV0 );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "A halted CPU (after a FX0A opcode) does not update the program counter "
                 "when the CPU executes another instruction",
                 "[keyboard]" )
{
    GIVEN( "A halted CPU and an i/o connector with no key pressed" )
    {
        ioDevice.setPressedKey( model::chip8::key::none );
        cpu.execute( 0xF00A );
        const auto originalPc = cpu.getPc();
        const auto originalV0 = cpu.readRegister( model::chip8::reg::v0 );

        WHEN( "the CPU cycles" )
        {
            cpu.execute( 0xF00A );

            THEN( "the program counter remains unchanged (the CPU is halted)" )
            {
                REQUIRE( cpu.getPc() == originalPc );
            }
            AND_THEN( "register V0 remains unchanged" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v0 ) == originalV0 );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU sets register X to the value of the pressed key "
                 "after any key is pressed during a FX0A operation",
                 "[keyboard]" )
{
    GIVEN( "A CPU and an i/o connector with the key F pressed" )
    {
        ioDevice.setPressedKey( model::chip8::key::kf );
        const auto originalPc = cpu.getPc();

        WHEN( "the CPU executes an FX0A opcode" )
        {
            cpu.execute( 0xF00A );

            THEN( "the pressed key is stored in V0" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v0 ) == 0xF );
            }
        }
    }
}

} // unnamed namespace
