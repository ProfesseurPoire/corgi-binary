#include <corgi/binary/dynamic_bitset.h>

#include <stdexcept>

void corgi::binary::dynamic_bitset::find_dimensions(int count)
{
    size_ = count;

    auto mod   = size_ % 8;
    byte_size_ = size_ / sizeof(unsigned char) * 8;

    if(mod > 0)
        byte_size_++;
}

corgi::binary::dynamic_bitset::dynamic_bitset(int count)
    : size_(count)
{
    find_dimensions(count);
    bytes_.resize(byte_size_, 0);
}

corgi::binary::dynamic_bitset::dynamic_bitset(int count, bool value)
{
    find_dimensions(count);
    if(value)
        bytes_.resize(byte_size_, 0b11111111);
    else
        bytes_.resize(byte_size_, 0);
}

int corgi::binary::dynamic_bitset::size() const
{
    return size_;
}

bool corgi::binary::dynamic_bitset::test(int pos) const
{
    if(pos < 0 || pos >= size_)
        throw std::invalid_argument("pos argument is out of bound");

    auto a = bytes_[pos / 8];
    a      = a >> (pos % 8);
    a      = a & 1;
    return a;
}
