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

SCENARIO_METHOD( CpuFixture,
                 "CPU skips the next instruction with opcode 3XNN when "
                 "register X is equal to the constant NN",
                 "[conditional]" )
{
    GIVEN( "A CPU with initialized register" )
    {
        cpu.writeRegister( model::Chip8::registers::V4, 0x35 );
        const auto originalPc = cpu.getPc();

        WHEN( "the CPU executes a 3XNN opcode where register X equals NN" )
        {
            cpu.execute( 0x3435 );

            THEN( "the CPUs program counter is updated" )
            {
                REQUIRE( cpu.getPc() == originalPc + model::Chip8::instruction_size_in_bytes );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU does not skip the next instruction with opcode 3XNN when "
                 "register X is not equal to the constant NN",
                 "[conditional]" )
{
    GIVEN( "A CPU with initialized register" )
    {
        cpu.writeRegister( model::Chip8::registers::V4, 0x35 );
        const auto originalPc = cpu.getPc();

        WHEN( "the CPU executes a 3XNN opcode where register X is not equal to NN" )
        {
            cpu.execute( 0x3434 );

            THEN( "the CPUs program counter is remains unchanged" )
            {
                REQUIRE( cpu.getPc() == originalPc );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU skips the next instruction with opcode 4XNN when "
                 "register X is not equal to the constant NN",
                 "[conditional]" )
{
    GIVEN( "A CPU with initialized register" )
    {
        cpu.writeRegister( model::Chip8::registers::VA, 0x1A );
        const auto originalPc = cpu.getPc();

        WHEN( "the CPU executes a 4XNN opcode where register X is not equal to NN" )
        {
            cpu.execute( 0x4A1B );

            THEN( "the CPUs program counter is updated" )
            {
                REQUIRE( cpu.getPc() == originalPc + model::Chip8::instruction_size_in_bytes );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU does not skip the next instruction with opcode 4XNN when "
                 "register X is equal to the constant NN",
                 "[conditional]" )
{
    GIVEN( "A CPU with initialized register" )
    {
        cpu.writeRegister( model::Chip8::registers::VA, 0x1A );
        const auto originalPc = cpu.getPc();

        WHEN( "the CPU executes a 4XNN opcode where register X equals NN" )
        {
            cpu.execute( 0x4A1A );

            THEN( "the CPUs program counter is remains unchanged" )
            {
                REQUIRE( cpu.getPc() == originalPc );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU skips the next instruction with opcode 5XY0 when "
                 "register X is equal to register Y",
                 "[conditional]" )
{
    GIVEN( "A CPU with initialized registers" )
    {
        cpu.writeRegister( model::Chip8::registers::V0, 0x47 );
        cpu.writeRegister( model::Chip8::registers::VF, 0x47 );
        const auto originalPc = cpu.getPc();

        WHEN( "the CPU executes a 5XY0 opcode where register X equals register Y" )
        {
            cpu.execute( 0x50F0 );

            THEN( "the CPUs program counter is updated" )
            {
                REQUIRE( cpu.getPc() == originalPc + model::Chip8::instruction_size_in_bytes );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU does not skip the next instruction with opcode 5XY0 when "
                 "register X is not equal to register Y",
                 "[conditional]" )
{
    GIVEN( "A CPU with initialized registers" )
    {
        cpu.writeRegister( model::Chip8::registers::V0, 0x47 );
        cpu.writeRegister( model::Chip8::registers::VF, 0x48 );
        const auto originalPc = cpu.getPc();

        WHEN( "the CPU executes a 5XY0 opcode where register X is not equal to register Y" )
        {
            cpu.execute( 0x50F0 );

            THEN( "the CPUs program counter is remains unchanged" )
            {
                REQUIRE( cpu.getPc() == originalPc );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU skips the next instruction with opcode 9XY0 when "
                 "register X is not equal to register Y",
                 "[conditional]" )
{
    GIVEN( "A CPU with initialized registers" )
    {
        cpu.writeRegister( model::Chip8::registers::V0, 0xFF );
        cpu.writeRegister( model::Chip8::registers::VF, 0xFE );
        const auto originalPc = cpu.getPc();

        WHEN( "the CPU executes a 9XY0 opcode where register X is not equal to register Y" )
        {
            cpu.execute( 0x90F0 );

            THEN( "the CPUs program counter is updated" )
            {
                REQUIRE( cpu.getPc() == originalPc + model::Chip8::instruction_size_in_bytes );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU does not skip the next instruction with opcode 9XY0 when "
                 "register X is equal to register Y",
                 "[conditional]" )
{
    GIVEN( "A CPU with initialized registers" )
    {
        cpu.writeRegister( model::Chip8::registers::V0, 0xAD );
        cpu.writeRegister( model::Chip8::registers::VF, 0xAD );
        const auto originalPc = cpu.getPc();

        WHEN( "the CPU executes a 9XY0 opcode where register X equals register Y" )
        {
            cpu.execute( 0x90F0 );

            THEN( "the CPUs program counter is remains unchanged" )
            {
                REQUIRE( cpu.getPc() == originalPc );
            }
        }
    }
}

} // namespace
