#pragma once
#include <vector>

namespace corgi::binary
{
/**
 * @brief   Get the value of the bit located at @p pos from the object
 *          pointed by @p src of @p size bytes
 *
 *          @param pos : position of the bit we're looking for
 *          @param src : Object we're reading bits from
 *          @param size : total size of @p src
 *
 *          @return     Returns 0 or 1 depending on the bit value. Returns -1 if
 *                      something went wrong
 */
int bit(int pos, unsigned char* src, int size);

/**
 * @brief   Converts @p count bits located at @pos into long long from
 *          the object pointed by @p src of @p size bytes
 *
 *          @param pos : position of the bits we're looking for
 *          @param count : How many bits we're reading.
 *          @param src : Object we're reading bits from
 *          @param size : total size of @p src in bytes.
 *
 *          @return     Returns the converted value, as long as count <=64
 */
long long bits_to_llong(std::size_t    pos,
                        std::size_t    count,
                        unsigned char* src,
                        std::size_t    size);

int bits_to_int(std::size_t    pos,
                std::size_t    count,
                unsigned char* src,
                std::size_t    size);

unsigned long long bits_to_ullong(std::size_t    pos,
                                  std::size_t    len,
                                  unsigned char* src,
                                  std::size_t    size);

}    // namespace corgi::binary