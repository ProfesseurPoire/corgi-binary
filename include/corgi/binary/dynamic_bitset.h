#pragma once

#include <iostream>
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
    /**
     * @brief   Maximum number of bits the element can hold.
     */
    static inline std::size_t max_size() noexcept
    {
        const std::vector<unsigned char> c;
        return c.max_size();
    }

    /**
     * @brief Constructs a new dynamic bitset with @p count bits sets to
     * @p value
     *
     * @param count The number of bits stored by the container.
     * @param value The default value for every bit in the container.
     *
     * @throws std::invalid_argument if count is less than 0
     */
    explicit dynamic_bitset(std::size_t count = 0, bool value = false);

    /**
     * @brief Constructs a new dynamic_bitset with values inside @p bits
     *
     * @param bits Bits inserted to the dynamic_bitset
     *
     * @throws std::length_error Thrown if @p bits is greater than @p max_size
     */
    dynamic_bitset(std::initializer_list<bool> bits);

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
    dynamic_bitset slice(std::size_t begin, std::size_t len);

    /**
     * @brief Erases every bit from the container
     *
     * Warning, this doesn't resize the container
     */
    void clear();

    /**
     * @brief Insert @p len bits equals to @p val before @p pos.
     *
     * Existing bits at @p pos are shifted to the right
     *
     * @param pos Position where we insert the bits
     * @param len How many bits are inserted at the @p pos location
     * @param val Value of inserted bits
     *
     * @throws std::out_of_range Thrown if @p pos is out of range
     */
    void insert(std::size_t pos, std::size_t len, bool val);

    /**
     * @brief Insert new bit equals to @p val before @p pos
     *
     * @param pos Position where we insert the new bit
     * @param val Value of the inserted bit
     *
     * @throws std::out_of_range Thrown if @p pos is out of range
     */
    void insert(std::size_t pos, bool val);

    /**
     * @brief Insert the @p bits before @p pos
     *
     * @param pos Position where we insert the bits
     * @param bits Bits to insert inside the container
     *
     * @throws std::out_of_range Thrown if @p pos is out of range
     */
    void insert(std::size_t pos, std::initializer_list<bool> bits);

    /**
     * @brief Erase the bit located at @p pos
     *
     * The function will copy every bit after @p pos to their new position.
     * The function doesn't change memory allocation
     *
     * @param pos Position of the bit to remove
     *
     * @throws std::out_of_range Thrown if @p pos is out range
     */
    void erase(std::size_t pos);

    /**
     * @brief Erase the bits from @p start to @p end
     *
     * @param start First bit to erase
     * @param end   Last bit to erase
     *
     * @throws std::out_of_range Thrown if @p start or @p end is out of range
     * @throws std::invalid_argument Thrown if @p start is bigger than @p end
     */
    void erase(std::size_t start, std::size_t end);

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
     * @brief Erase the last bit from the container.
     */
    void pop_back();

    /**
     * @brief Resize the container so it holds @p len bits. New bits are
     * equals to @p value
     *
     * Does nothing if len == bit_size_
     * @param len
     */
    void resize(std::size_t len, bool value = true);

    /**
     * @brief Resize the container so it can hold up to @p len bits
     */
    void reserve(std::size_t len);

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
    std::size_t size() const noexcept;

    /**
     * @brief   Returns the number of bytes used by the container.
     * @return  The number of byte used by the container.
     */
    std::size_t byte_size() const noexcept;

    /**
     * @brief   Returns a pointer to the array storing the packed bits.
     * @return  The pointer to the array
     */
    unsigned char* data();

    /**
     * @brief   Returns a copy of the bit value located at @p pos with bound
     * checking
     *
     * @param pos Locationg of the bit we want to access
     * @retval  True if the bit located at @p pos is set
     * @retval  False if the bit located at @p pos isn't set
     *
     * @throws std::out_of_range Thrown if @p index isn't in the [0,size_bit]
     * range
     */
    bool test(std::size_t pos) const;

    /**
     * @brief   Sets the bit located at @p pos to @p value
     *
     * @param pos   The position of the bit to set
     * @param value The value to set the bit to
     */
    void set(std::size_t pos, bool value = true);

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
    void flip(std::size_t pos);

    /**
     * @brief Flips every bits
     */
    void flip();

    /**
     * @brief   Sets the bit located at @p pos to false
     *
     * @param pos The position of the bit to set to false
     */
    void reset(std::size_t pos);

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
    bool in_range(std::size_t bit_index) const;

    /**
     * @brief Reallocate the container if needed to hold up to @p len bits
     */
    void reallocate(std::size_t len);

    /**
     * @brief   Bits are stored here
     */
    std::vector<unsigned char> bytes_;

    /**
     * @brief How many bits are stored by the bitset
     */
    std::size_t bit_size_;
};
}    // namespace corgi::binary