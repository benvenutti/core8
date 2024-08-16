#include <model/CPU.hpp>

#include <mock/Helper.hpp>

#include <catch2/catch_test_macros.hpp>

namespace
{

struct CpuFixture
{
    Mock::TestKit                    testKit;
    model::MMU&                      mmu          = testKit.mmu;
    model::CPU&                      cpu          = testKit.cpu;
    Mock::RandomNumberGeneratorMock& rndGenerator = testKit.rndGenerator;
};

SCENARIO_METHOD( CpuFixture,
                 "CPU sets register X to the result of a bitwise AND operation on "
                 "the minimum possible random number generated and NN "
                 "using the CXNN opcode",
                 "[random]" )
{
    GIVEN( "A CPU and the random generated value 0" )
    {
        rndGenerator.setValue( 0x0 );

        WHEN( "the CPU executes a CXNN operation with X equal to 0 and NN equal to FF" )
        {
            cpu.execute( 0xC0FF );

            THEN( "register V0 is set to 0" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::v0 ) == 0x0 );
            }
        }
    }
}

SCENARIO_METHOD( CpuFixture,
                 "CPU sets register X to the result of a bitwise AND operation on "
                 "the maximum possible random number generated and NN "
                 "using the CXNN opcode",
                 "[random]" )
{
    GIVEN( "A CPU and the random generated value FF" )
    {
        rndGenerator.setValue( 0xFF );

        WHEN( "the CPU executes a CXNN operation with X equal to F and NN equal to FF" )
        {
            cpu.execute( 0xCFFF );

            THEN( "register VF is set to FF" )
            {
                REQUIRE( cpu.readRegister( model::chip8::reg::vf ) == 0xFF );
            }
        }
    }
}

} // namespace
