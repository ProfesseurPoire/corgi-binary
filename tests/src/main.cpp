#include "corgi/binary/binary.h"
#include "corgi/test/test.h"
int main()
{
    corgi::test::add_test(
        "corgi-binary", "bit",
        []() -> void
        {
            int v = 0b11111111111110111001111101111101;
            assert_that(
                corgi::binary::bit(0, reinterpret_cast<unsigned char*>(&v), 4),
                corgi::test::equals(1));
            assert_that(
                corgi::binary::bit(1, reinterpret_cast<unsigned char*>(&v), 4),
                corgi::test::equals(0));
        });

    corgi::test::add_test(
        "corgi-binary", "bits_llong",
        []() -> void
        {
            int r = 0b00000000000000111011100111110111;
            int v = 0b11111111111110111001111101111101;

            auto result = corgi::binary::bits_to_llong(
                4, 18, reinterpret_cast<unsigned char*>(&v), 4);

            assert_that(result, corgi::test::equals(static_cast<long long>(r)));
        });

    return corgi::test::run_all();
}