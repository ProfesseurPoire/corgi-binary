#include <corgi/binary/dynamic_bitset.h>

#include <cstring>
#include <stdexcept>
namespace
{
constexpr int           bits_per_byte = 8;
constexpr unsigned char byte_all_set  = 0b11111111;
}    // namespace

namespace corgi::binary
{
/**
 * @brief   Computes the minimum number of byte needed to store @p bit_count
 *          number of bits
 *
 * @relates dynamic_set
 */
static std::size_t compute_byte_count_from_bit_count(std::size_t bit_count)
{
    std::size_t byte_count = 0;

    auto mod   = bit_count % bits_per_byte;
    byte_count = bit_count / bits_per_byte;

    if(mod > 0)
        byte_count++;

    return byte_count;
}

bool dynamic_bitset::any() const noexcept
{
    if(empty())
        return false;

    std::size_t bits   = bit_size_;
    std::size_t offset = 0;

    // We read bits 8 by 8 as much as we can
    while(bits > 0)
    {
        // How many bits we read
        auto size = std::min(static_cast<std::size_t>(8), bits);

        // Sets size bits to 1
        unsigned char val = (1 << size) - 1;

        // We get back the byte index
        auto byte_index = offset / 8;

        // We compare check if at least one bit is set
        if((bytes_[byte_index] & val) != 0)
            return true;

        offset += size;
        bits -= size;
    }
    return false;
}

bool dynamic_bitset::all() const noexcept
{
    if(empty())
        return true;

    std::size_t bits   = bit_size_;
    std::size_t offset = 0;

    // We read bits 8 by 8 as much as we can
    while(bits > 0)
    {
        // How many bits we read
        auto size = std::min(static_cast<std::size_t>(8ULL), bits);

        // Value the byte must have for every bit to be set

        // Sets size bits to 1
        unsigned char val = (1 << size) - 1;

        // we get back the byte index
        auto byte_index = offset / 8;

        // We compare the expected value with what we have in the array
        if((bytes_[byte_index] & val) != val)
            return false;

        offset += size;
        bits -= size;
    }
    return true;
}

bool dynamic_bitset::none() const noexcept
{
    return !any();
}

bool dynamic_bitset::empty() const noexcept
{
    return bit_size_ == 0;
}

void dynamic_bitset::push_back(bool value)
{
    if(byte_size() * 8 < bit_size_ + 1)
        bytes_.push_back(0);

    bit_size_++;
    set(bit_size_ - 1, value);
}

bool dynamic_bitset::in_range(std::size_t bit_index) const
{
    return (bit_index >= 0 && bit_index < bit_size_);
}

void dynamic_bitset::set(bool value)
{
    for(auto& byte : bytes_)
        value ? byte = byte_all_set : byte = 0;
}

dynamic_bitset dynamic_bitset::slice(std::size_t begin, std::size_t len)
{
    return dynamic_bitset(begin, len);
}

void dynamic_bitset::set(std::size_t pos, bool value)
{
    auto byte_index = pos / bits_per_byte;
    auto bit_index  = pos % bits_per_byte;

    // Clears the bit we want to set
    // (bytes_[byte_index] & ~(1UL << bit_index))
    //
    // Sets the bits with the given value
    // (value << bit_index)
    bytes_[byte_index] =
        (bytes_[byte_index] & ~(1UL << bit_index)) | (value << bit_index);

    // This was my implementation,
    // unsigned char mask = 0;
    // mask               = static_cast<unsigned char>(1 << bit_index);
    // if(value)
    //     bytes_[byte_index] |= mask;
    // else
    //     bytes_[byte_index] &= ~mask;
}

unsigned long long dynamic_bitset::to_ullong() const
{
    if(bit_size_ > (sizeof(unsigned long long) * 8))
    {
        throw std::overflow_error("dynamic_bitset : Too much bits in bitset to "
                                  "convert to an unsigned long long");
    }

    unsigned long long result = 0;
    memcpy(&result, bytes_.data(), bytes_.size());
    return result;
}

void dynamic_bitset::clear()
{
    bit_size_ = 0;
}

std::size_t dynamic_bitset::byte_size() const noexcept
{
    return static_cast<int>(bytes_.size());
}

dynamic_bitset::dynamic_bitset(std::size_t count, bool value)
{
    // This won't always be detected depending on vector<unsigned
    // char>::max_size
    if(count > max_size())
        throw std::length_error("Bit count is greater than bitset limit");

    bit_size_        = count;
    auto bytes_count = compute_byte_count_from_bit_count(count);

    if(value)
        bytes_.resize(bytes_count, 0b11111111);
    else
        bytes_.resize(bytes_count, 0);
}

std::size_t dynamic_bitset::size() const noexcept
{
    return bit_size_;
}

bool dynamic_bitset::test(std::size_t pos) const
{
    if(pos < 0 || pos >= bit_size_)
        throw std::invalid_argument("pos argument is out of bound");

    return static_cast<bool>(
        bytes_[pos / bits_per_byte] >> (pos % bits_per_byte) & 1);
}

}    // namespace corgi::binary