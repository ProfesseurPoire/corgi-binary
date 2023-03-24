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
    dynamic_bitset(int n, bool value);

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

private:
    void find_dimensions(int count);

    /**
     * @brief   Bits are stored here
     */
    std::vector<unsigned char> bytes_;

    int size_;
    int byte_size_;
};
}    // namespace corgi::binary