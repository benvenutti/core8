#include <array>
#include <cstdint>
#include <istream>
#include <vector>

#include "IoDeviceMock.hpp"
#include "RandomNumberGeneratorMock.hpp"
#include "model/CPU.hpp"
#include "model/Chip8.hpp"
#include "model/MMU.hpp"

/// @brief Auxiliary tools for unit testing Core8.
namespace Aux
{

/// @brief Bundle of objects necessary to test the CPU.
struct TestKit
{
    model::MMU                     mmu;
    Aux::IoDeviceMock              ioDevice;
    Aux::RandomNumberGeneratorMock rndGenerator;
    model::CPU                     cpu{ mmu, ioDevice, rndGenerator };
};

/// @brief Simulates a byte stream from a std::vector<std::uint8_t>.
class ByteStream : public std::istream
{
public:
    ByteStream( std::vector<std::uint8_t>& data )
    : std::istream{ &byteBuffer }
    , byteBuffer{ data.data(), data.size() }
    {
        rdbuf( &byteBuffer );
    }

private:
    class ByteBuffer : public std::basic_streambuf<char>
    {
    public:
        ByteBuffer( std::uint8_t* data, std::size_t size )
        {
            setg( reinterpret_cast<char*>( data ),
                  reinterpret_cast<char*>( data ),
                  reinterpret_cast<char*>( data ) + size );
        }
    };

    ByteBuffer byteBuffer;
};

} // namespace Aux
