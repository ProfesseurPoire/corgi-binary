#pragma once

#include <vector>

namespace corgi::binary
{

/**
 * @brief	see std::bitset but dynamic. Basically a container that stores
 *		and manipulates bits.
 *
 *              Also this is totally inspired of boost dynamic_set but I just
 *              didn't want to pull boost only for that
 */
class dynamic_bitset
{
public:
    /**
     * @brief   Constructs a new dynamic bitset that contains @p count bits set
     *          to 0.
     */
    explicit dynamic_bitset(int count);

    /**
     * @brief   Constructs a new dynamic bitset that contains @p count bits sets
     *          to @p value
     */
    dynamic_bitset(int count, bool value);

    /**
     * @brief   Returns how many bits are stored
     */
    int size() const;

    /**
     * @brief   Returns the bit value located at @p pos
     */
    bool test(int pos) const;

    /**
     * @brief   Sets the bit located at @p pos to @p value
     */
    void set(int pos, bool value);

    /**
     * @brief   Converts the bits to a ullong value.
     *
     *          This function will throw a std::overflow_error if the value
     *          cannot be converted to a unsigned long long. IE, it has more
     *          than 64 bits.
     */
    unsigned long long to_ullong() const;

private:
    /**
     * @brief   Bits are stored here
     */
    std::vector<unsigned char> bytes_;

    /**
     * @brief How many bits are stored by the bitset
     */
    int bit_size_;

    /**
     * @brief How many bytes are used to store the @a bit_size_ bits
     */
    int byte_size_;
};
}    // namespace corgi::binary