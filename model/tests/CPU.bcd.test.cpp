#include <model/CPU.hpp>

#include <mock/Helper.hpp>

#include <catch2/catch_test_macros.hpp>

namespace
{

struct CpuFixture
{
    Mock::TestKit testKit;
    model::CPU&   cpu = testKit.cpu;
    model::MMU&   mmu = testKit.mmu;
};

SCENARIO_METHOD( CpuFixture,
                 "CPU stores in address I the BCD representation of the value 0x0 from a register",
                 "[bcd]" )
{
    GIVEN( "A CPU with V0 set to 0 and register I set to 100" )
    {
        cpu.writeRegister( model::chip8::reg::v0, 0x0 );
        cpu.iaddr( 100 );

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
        cpu.writeRegister( model::chip8::reg::vf, 0xFF );
        cpu.iaddr( 200 );

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
