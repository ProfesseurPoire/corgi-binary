#include <corgi/binary/dynamic_bitset.h>

#include <stdexcept>

namespace
{
constexpr int bits_per_byte = 8;
}

namespace corgi::binary
{
/**
 * @brief   Computes the minimum number of byte needed to store @p bit_count
 *          number of bits
 *
 * @relates dynamic_set
 */
static int compute_byte_count_from_bit_count(int bit_count)
{
    int byte_count = 0;

    auto mod   = bit_count % bits_per_byte;
    byte_count = bit_count / bits_per_byte;

    if(mod > 0)
        byte_count++;

    return byte_count;
}

void dynamic_bitset::set(int pos, bool value)
{
    auto byte_index = pos / bits_per_byte;
    auto bit_index  = pos % bits_per_byte;

    unsigned char mask = 0;
    mask               = bit_index << 1;

    unsigned char cpy = bytes_[byte_index];
}

unsigned long long dynamic_bitset::to_ullong() const
{
    if(bit_size_ > sizeof(unsigned long long))
    {
        throw std::overflow_error("dynamic_bitset : Too much bits in bitset to "
                                  "convert to an unsigned long long");
    }

    unsigned long long result = 0;
    memcpy(&result, bytes_.data(), bytes_.size());
    return result;
}

dynamic_bitset::dynamic_bitset(int count)
    : bit_size_(count)
    , byte_size_(compute_byte_count_from_bit_count(count))
{
    bytes_.resize(byte_size_, 0);
}

dynamic_bitset::dynamic_bitset(int count, bool value)
    : bit_size_(count)
    , byte_size_(compute_byte_count_from_bit_count(count))
{
    if(value)
        bytes_.resize(byte_size_, 0b11111111);
    else
        bytes_.resize(byte_size_, 0);
}

int dynamic_bitset::size() const
{
    return bit_size_;
}

bool dynamic_bitset::test(int pos) const
{
    if(pos < 0 || pos >= bit_size_)
        throw std::invalid_argument("pos argument is out of bound");

    return static_cast<bool>(
        bytes_[pos / bits_per_byte] >> (pos % bits_per_byte) & 1);
}

}    // namespace corgi::binary