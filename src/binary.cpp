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

long long bits_to_llong(int pos, int count, unsigned char* src, int size)
{
    if(count >= 64)
        throw std::invalid_argument("size is >= 64 ");

    if(pos < 0 || pos >= size * 8)
        throw std::invalid_argument("pos is out of bounds ");

    if(pos + count < 0 || pos + count > size * 8)
        throw std::invalid_argument("pos is out of bounds ");

    // Stores the final result
    long long result = 0;

    // Stores how many bits have been currently read so far
    int current_bits_done = 0;

    // As long as there's some bits to read, the loop goes on
    while(count != 0)
    {
        // We get back the byte we're working on and the offset of our first bit
        // inside the byte
        const int byte_offset        = pos / 8;
        const int bit_offset_in_byte = pos % 8;

        // We count how many bits we read from the current byte
        int readable_bits = 8 - bit_offset_in_byte;
        int bits_to_read  = count;

        // If we have more bits to read than we have on the current byte
        if(count > readable_bits)
        {
            // We read what we can
            count -= readable_bits;
            bits_to_read = readable_bits;
        }
        else
            count = 0;

        // We create a binary value that correspond to the number of bit we're
        // reading from the current byte. This variable will be used as a mask
        // to get only the bits we're interested in the current byte
        long long mask = static_cast<long long>(std::pow(2, bits_to_read) - 1);

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
}    // namespace corgi::binary