#include <cstdint>
#include <istream>
#include <vector>

/// @brief Auxiliary tools for unit testing Core8.
namespace Aux {

/// @brief Simulates a byte stream from a std::vector<std::uint8_t>.
class ByteStream : public std::istream {
  public:
    ByteStream(std::vector<std::uint8_t>& data)
        : std::istream{&byteBuffer},
          byteBuffer{data.data(), data.size()} {
      rdbuf(&byteBuffer);
    }

  private:
    class ByteBuffer : public std::basic_streambuf<char> {
      public:
        ByteBuffer(std::uint8_t* data, std::size_t size) {
          setg(
              reinterpret_cast<char*>(data),
              reinterpret_cast<char*>(data),
              reinterpret_cast<char*>(data) + size
          );
        }
    };

    ByteBuffer byteBuffer;
};

} // namespace Aux