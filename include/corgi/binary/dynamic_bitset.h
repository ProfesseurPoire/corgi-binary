#pragma once

#include <vector>

namespace corgi::binary
{

/**
 * @brief   std::bitset but dynamic. Basically a container that stores
 *		    and manipulates bits.
 *
 *          Also this is totally inspired of boost dynamic_set but I just
 *          didn't want to pull boost only for that
 */
class dynamic_bitset
{
public:
    /**
     * @brief   Constructs a new dynamic bitset with @p count bits set to 0.
     *
     * @param count The number of bits stored by the container.
     */
    explicit dynamic_bitset(int count);

    /**
     * @brief   Constructs a new dynamic bitset with @p count bits sets
     *          to @p value
     *
     * @param count The number of bits stored by the container.
     * @param value The default value for every bit in the container.
     */
    dynamic_bitset(int count, bool value);

    /**
     * @brief   Returns the number of bits in the container.
     * @return  The number of bit in the container.
     */
    int size() const;

    /**
     * @brief   Returns the number of bytes used by the container.
     * @return  The number of byte used by the container.
     */
    int byte_size() const;

    /**
     * @brief   Returns a pointer to the array storing the packed bits.
     * @return  The pointer to the array
     */
    unsigned char* data();

    /**
     * @brief   Returns the bit's value located at @p pos
     *
     * @param pos The position of the bit to test
     *
     * @retval true  : Bit located at @p pos is set
     * @retval false : Bit located at @p pos isn't set
     */
    bool test(int pos) const;

    /**
     * @brief   Sets the bit located at @p pos to @p value
     *
     * @param pos   The position of the bit to set
     * @param value The value to set the bit to
     */
    void set(int pos, bool value = true);

    /**
     * @brief   Sets all bits to @p value
     */
    void set(bool value = true);

    /**
     * @brief   Flips the bit located at @p pos
     *
     *          If a bit is equals to zero, it becomes 1, and if a bit is equal
     *          to one it becomes zero.
     *
     * @param pos The position of the bit to flip
     */
    void flip(int pos);

    /**
     * @brief Flips every bits
     */
    void flip();

    /**
     * @brief   Sets the bit located at @p pos to false
     *
     * @param pos The position of the bit to set to false
     */
    void reset(int pos);

    /**
     * @brief   Sets all the bits to false
     */
    void reset();

    /**
     * @brief   Converts the bits to a ullong value.
     *
     *          This function will throw a std::overflow_error if the value
     *          cannot be converted to a unsigned long long. IE, it has more
     *          than 64 bits.
     *
     * @return The converted value
     */
    unsigned long long to_ullong() const;

private:
    /**
     * @brief   Checks if @p bit_index is in range.
     *
     *          In range means bit_index is > 0 and < to bit_size
     *
     * @retval true     bit_index is in range
     * @retval false    bit_index isn't in range
     */
    bool in_range(int bit_index) const;

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