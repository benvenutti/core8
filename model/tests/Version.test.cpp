#include <model/Version.hpp>

#include <catch2/catch_test_macros.hpp>

SCENARIO( "Semantic versioning major.minor.patch values", "[version]" )
{
    REQUIRE( model::Version::major == 0 );
    REQUIRE( model::Version::minor == 1 );
    REQUIRE( model::Version::patch == 0 );
}

SCENARIO( "Version string holds the name of the project and the correct version", "[version]" )
{
    REQUIRE( model::Version::string == std::string{ "core8 0.1.0" } );
}
