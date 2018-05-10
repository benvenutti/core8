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
    model::MMU&  mmu = testKit.mmu;
};

SCENARIO_METHOD( CpuFixture,
                 "CPU stores in address I the BCD representation of the value 0x0 from a register",
                 "[bcd]" )
{
    GIVEN( "A CPU with V0 set to 0 and register I set to 100" )
    {
        cpu.writeRegister( model::chip8::registers::V0, 0x0 );
        cpu.setI( 100 );

        WHEN( "the CPU executes a FX33 operation with X equal to 0" )
        {
            cpu.execute( 0xF033 );

            THEN( "the memory holds 3 digits with the BCD representation of VX starting at I" )
            {
                REQUIRE( mmu.readByte( 100u ) == 0 );
                REQUIRE( mmu.readByte( 101u ) == 0 );
                REQUIRE( mmu.readByte( 102u ) == 0 );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU stores in address I the BCD representation of the value 0xFF from a register",
                 "[bcd]" )
{
    GIVEN( "A CPU with V0 set to 0xFF and register I set to 200" )
    {
        cpu.writeRegister( model::chip8::registers::VF, 0xFF );
        cpu.setI( 200 );

        WHEN( "the CPU executes a FX33 operation with X equal to F" )
        {
            cpu.execute( 0xFF33 );

            THEN( "the memory holds 3 digits with the BCD representation of VX starting at I" )
            {
                REQUIRE( mmu.readByte( 200u ) == 2 );
                REQUIRE( mmu.readByte( 201u ) == 5 );
                REQUIRE( mmu.readByte( 202u ) == 5 );
            }
        }
    }
}

} // namespace
