#pragma once

#include <limits>
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
    using size_t = long long;

    /**
     * @brief   Maximum number of bits the element can hold.
     */
    static inline constexpr size_t max_size() noexcept
    {
        std::vector<unsigned char> c;
        return c.max_size();
    }

    /**
     * @brief   Constructs a new dynamic bitset with @p count bits sets
     *          to @p value
     *
     * @param count The number of bits stored by the container.
     * @param value The default value for every bit in the container.
     *
     * @throws std::invalid_argument if count is less than 0
     */
    dynamic_bitset(size_t count = 0, bool value = false);

    /**
     * @brief   Constructs and returns a new dynamic_bitset that is a subset of
     * the current dynamic_bitset.
     *
     * The newly constructed dynamic_bitset starts at @p begin and contains @p
     * len elements
     *
     * @throws std::invalid_argument Thrown if @p begin is out of bound
     * @throws std::invalid_argument Thrown if @p len is greater than begin +
     * bit_size_
     */
    dynamic_bitset slice(dynamic_bitset::size_t begin,
                         dynamic_bitset::size_t len);

    /**
     * @brief   Adds a bit to the set
     * @param value The value of the new bit added to the set
     */
    void push_back(bool value);

    /**
     * @brief   Returns true if not bits have been stored
     * @retval  True if no bits are stored
     * @retval  False if at least 1 bit is stored
     */
    bool empty() const noexcept;

    /**
     * @brief   Returns true if all bits are set
     *
     * If the set is empty, returns true. (follows std::all_of() convention)
     *
     * @retval  True if every bit is set
     * @retval  False if every bit is set
     */
    bool all() const noexcept;

    /**
     * @brief   Returns true if any bit is set
     *
     * If the set is empty, returns false. (follows std::any_of() convention)
     *
     * @retval  True if at least one bit is set
     * @retval  False if no bit is set
     */
    bool any() const noexcept;

    /**
     * @brief   Returns true if every bit isn't set
     *
     * If the set is empty, returns true. (follows std::none_of() convention)
     *
     * @retval  True if every bit isn't set
     * @retval  False if at least one bit is set
     */
    bool none() const noexcept;

    /**
     * @brief   Returns the number of bits in the container.
     * @return  The number of bit in the container.
     */
    dynamic_bitset::size_t size() const noexcept;

    /**
     * @brief   Returns the number of bytes used by the container.
     * @return  The number of byte used by the container.
     */
    dynamic_bitset::size_t byte_size() const noexcept;

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
    bool test(dynamic_bitset::size_t pos) const;

    /**
     * @brief   Sets the bit located at @p pos to @p value
     *
     * @param pos   The position of the bit to set
     * @param value The value to set the bit to
     */
    void set(dynamic_bitset::size_t pos, bool value = true);

    /**
     * @brief   Sets all bits to @p value
     */
    void set(bool value = true);

    /**
     * @brief   Flips the bit located at @p pos
     *
     * If a bit is equals to zero, it becomes 1, and if a bit is equal
     * to one it becomes zero.
     *
     * @param pos The position of the bit to flip
     */
    void flip(dynamic_bitset::size_t pos);

    /**
     * @brief Flips every bits
     */
    void flip();

    /**
     * @brief   Sets the bit located at @p pos to false
     *
     * @param pos The position of the bit to set to false
     */
    void reset(dynamic_bitset::size_t pos);

    /**
     * @brief   Sets all the bits to false
     */
    void reset();

    /**
     * @brief   Converts the bits to a ullong value.
     *
     * This function will throw a std::overflow_error if the value
     * cannot be converted to a unsigned long long. IE, it has more
     * than 64 bits.
     *
     * @return The converted value
     */
    unsigned long long to_ullong() const;

private:
    /**
     * @brief   Checks if @p bit_index is in range.
     *
     * In range means bit_index is > 0 and < to bit_size
     *
     * @retval true     bit_index is in range
     * @retval false    bit_index isn't in range
     */
    bool in_range(dynamic_bitset::size_t bit_index) const;

    /**
     * @brief   Bits are stored here
     */
    std::vector<unsigned char> bytes_;

    /**
     * @brief How many bits are stored by the bitset
     */
    size_t bit_size_;
};
}    // namespace corgi::binary