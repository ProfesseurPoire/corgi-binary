#include <corgi/binary/binary.h>

#include <cassert>
#include <cmath>
#include <stdexcept>

namespace corgi::binary
{

int bit(int pos, unsigned char* src, int size)
{
    if(pos < 0 || pos >= size * 8)
        return -1;

    // We first get back the byte the bit lives in src at (pos/8). From this, we
    // move the bit of (pos % 8) position so it becomes the most least
    // significant bit. From there, we only have to AND it with the value
    // 0b00000001 to get the bit value. (the &1) part
    return src[pos / 8] >> pos % 8 & (1);
}

template<class T>
T bits_to_type(std::size_t    pos,
               std::size_t    len,
               unsigned char* src,
               std::size_t    size)
{
    if(len >= sizeof(T) * 8)
        throw std::invalid_argument("Argument len is greater than sizeof(T)");

    if(pos < 0 || pos >= size * 8)
        throw std::invalid_argument("Argument pos is out of bounds ");

    if(pos + len < 0 || pos + len > size * 8)
        throw std::invalid_argument("Argument pos is out of bounds ");

    // Stores the final result
    T result = 0;

    // Stores how many bits have been currently read so far
    std::size_t current_bits_done = 0;

    // As long as there's some bits to read, the loop goes on
    while(len != 0)
    {
        // We get back the byte we're working on and the offset of our first bit
        // inside the byte
        const std::size_t byte_offset        = pos / 8;
        const std::size_t bit_offset_in_byte = pos % 8;

        // We count how many bits we read from the current byte
        std::size_t readable_bits = 8 - bit_offset_in_byte;
        std::size_t bits_to_read  = len;

        // If we have more bits to read than we have on the current byte
        if(len > readable_bits)
        {
            // We read what we can
            len -= readable_bits;
            bits_to_read = readable_bits;
        }
        else
            len = 0;

        // We create a binary value that correspond to the number of bit we're
        // reading from the current byte. This variable will be used as a mask
        // to get only the bits we're interested in the current byte
        T mask = static_cast<T>(std::pow(2, bits_to_read) - 1);

        // We shift it so it's starts at the right position
        mask <<= bit_offset_in_byte;

        // We AND the mask and the content of the byte to only get the bits we
        // want
        mask &= src[byte_offset];

        // We add the bits we recuperated to the result at the right position
        result = result + ((mask >> (bit_offset_in_byte) << current_bits_done));

        pos += bits_to_read;
        current_bits_done += bits_to_read;
    }
    return result;
}

int bits_to_int(std::size_t    pos,
                std::size_t    len,
                unsigned char* src,
                std::size_t    size)
{
    return bits_to_type<int>(pos, len, src, size);
}

unsigned long long bits_to_ullong(std::size_t    pos,
                                  std::size_t    len,
                                  unsigned char* src,
                                  std::size_t    size)
{
    return bits_to_type<unsigned long long>(pos, len, src, size);
}

long long bits_to_llong(std::size_t    pos,
                        std::size_t    count,
                        unsigned char* src,
                        std::size_t    size)
{
    return bits_to_type<long long>(pos, count, src, size);
}
}    // namespace corgi::binary