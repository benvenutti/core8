#include <model/MMU.hpp>

#include <mock/Helper.hpp>

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <cstdint>
#include <numeric>
#include <vector>

namespace
{

SCENARIO( "Creating a MMU with the default constructor", "[mmu]" )
{
    GIVEN( "A null context" )
    {
        WHEN( "a MMU object is created" )
        {
            model::MMU mmu;

            THEN( "its size is equal the Chip-8 ram size" )
            {
                REQUIRE( mmu.size() == model::chip8::ram_size );
            }
            AND_THEN( "its memory is cleared (filled with zeros)" )
            {
                REQUIRE( std::accumulate( mmu.begin(), mmu.end(), 0u ) == 0u );
            }
        }
    }
}

SCENARIO( "Comparing two identical MMUs using the equal operator", "[mmu]" )
{
    GIVEN( "Two MMUs with the same values in memory" )
    {
        model::MMU mmu1;
        model::MMU mmu2;
        std::ranges::fill( mmu1, static_cast< model::chip8::byte_t >( 0xFFu ) );
        std::ranges::fill( mmu2, static_cast< model::chip8::byte_t >( 0xFFu ) );

        WHEN( "the MMUs are compared using the equal operator" )
        {
            const auto areEqual = mmu1 == mmu2;

            THEN( "the operation returns true" )
            {
                REQUIRE( areEqual );
            }
        }
    }
}

SCENARIO( "Comparing two different MMUs using the equal operator", "[mmu]" )
{
    GIVEN( "Two MMUs with different values in memory" )
    {
        model::MMU mmu1;
        model::MMU mmu2;
        mmu1.writeByte( 0x01, 0x0 );

        WHEN( "the MMUs are compared using the equal operator" )
        {
            const auto areEqual = mmu1 == mmu2;

            THEN( "the operation returns false" )
            {
                REQUIRE_FALSE( areEqual );
            }
        }
    }
}

SCENARIO( "MMU writes a byte into a valid address", "[mmu]" )
{
    GIVEN( "A MMU" )
    {
        model::MMU mmu;

        WHEN( "the MMU writes a byte to a valid address" )
        {
            mmu.writeByte( 0x11, 0x0 );
            mmu.writeByte( 0xFF, 0xFFF );

            THEN( "the byte is copied into memory at that address" )
            {
                REQUIRE( 0x11 == mmu.readByte( 0x0 ) );
                REQUIRE( 0xFF == mmu.readByte( 0xFFF ) );
            }
        }
    }
}

SCENARIO( "MMU reads a byte from a valid address", "[mmu]" )
{
    GIVEN( "A MMU with initialized values" )
    {
        model::MMU mmu;
        mmu.writeByte( 0x11, 0x0 );
        mmu.writeByte( 0xFF, 0xFFF );

        WHEN( "the MMU reads a byte from a valid address" )
        {
            const auto byte1 = mmu.readByte( 0x0 );
            const auto byte2 = mmu.readByte( 0xFFF );

            THEN( "the MMU will return the byte at that address" )
            {
                REQUIRE( 0x11 == byte1 );
                REQUIRE( 0xFF == byte2 );
            }
        }
    }
}

SCENARIO( "MMU reads a word from a valid address", "[mmu]" )
{
    GIVEN( "A MMU with initialized values" )
    {
        model::MMU mmu;
        mmu.writeByte( 0x1A, 0x80 );
        mmu.writeByte( 0xF1, 0x81 );
        mmu.writeByte( 0xCC, 0xFFE );
        mmu.writeByte( 0xDD, 0xFFF );

        WHEN( "the MMU reads a word from a valid address" )
        {
            const auto word1 = mmu.readWord( 0x80 );
            const auto word2 = mmu.readWord( 0xFFE );

            THEN( "the MMU will return the big-endian word starting at that address" )
            {
                REQUIRE( 0x1AF1 == word1 );
                REQUIRE( 0xCCDD == word2 );
            }
        }
    }
}

SCENARIO( "MMU loads a rom that fits at the given valid address", "[mmu]" )
{
    GIVEN( "A rom and a MMU" )
    {
        std::vector< std::uint8_t > data{ 0xFF, 0x11, 0xCC, 0x33 };
        model::MMU                  mmu;

        WHEN( "the MMU loads the rom at a valid address with enough memory space" )
        {
            mmu.load( data, 0x100 );

            THEN( "the whole rom is copied into memory starting at the given address" )
            {
                REQUIRE( 0xFF == mmu.readByte( 0x100 ) );
                REQUIRE( 0x11 == mmu.readByte( 0x101 ) );
                REQUIRE( 0xCC == mmu.readByte( 0x102 ) );
                REQUIRE( 0x33 == mmu.readByte( 0x103 ) );
            }
        }
    }
}

SCENARIO( "MMU loads a rom that does not fit at the given valid address", "[mmu]" )
{
    GIVEN( "A rom and a MMU" )
    {
        std::vector< std::uint8_t > data{ 0xFF, 0x11, 0xCC, 0x33 };
        model::MMU                  mmu;

        WHEN( "the MMU loads the rom at a valid address without enough space" )
        {
            mmu.load( data, 0xFFD );

            THEN( "only the rom part that fits is copied into memory at the given address" )
            {
                REQUIRE( 0xFF == mmu.readByte( 0xFFD ) );
                REQUIRE( 0x11 == mmu.readByte( 0xFFE ) );
                REQUIRE( 0xCC == mmu.readByte( 0xFFF ) );
            }
        }
    }
}

SCENARIO( "MMU loads a rom to an invalid memory address", "[mmu]" )
{
    GIVEN( "A rom and a MMU" )
    {
        std::vector< std::uint8_t > data{ 0xFF, 0x11, 0xCC, 0x33 };
        model::MMU                  mmu;
        model::MMU                  originalMmu{ mmu };

        WHEN( "the MMU loads the rom at an invalid address" )
        {
            mmu.load( data, 0x1000 );
        }
        THEN( "nothing is copied and the MMU remains unchanged" )
        {
            REQUIRE( mmu == originalMmu );
        }
    }
}

SCENARIO( "MMU clears its memory", "[mmu]" )
{
    GIVEN( "A MMU with initialized values" )
    {
        model::MMU mmu;
        std::ranges::fill( mmu, static_cast< model::chip8::byte_t >( 0xFFu ) );

        WHEN( "the MMU clears the memory" )
        {
            mmu.clear();

            THEN( "all bytes in memory are set to zero" )
            {
                REQUIRE( std::accumulate( mmu.begin(), mmu.end(), 0u ) == 0u );
            }
        }
    }
}

} // namespace
