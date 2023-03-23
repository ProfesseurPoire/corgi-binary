#include "corgi/binary/binary.h"
#include "corgi/test/test.h"

using namespace corgi;

int main()
{
    test::add_test(
        "corgi-binary", "bit",
        []() -> void
        {
            int test_data = 0b11111111111110111001111101111101;
            assert_that(
                binary::bit(0, reinterpret_cast<unsigned char*>(&test_data), 4),
                test::equals(1));
            assert_that(
                binary::bit(1, reinterpret_cast<unsigned char*>(&test_data), 4),
                test::equals(0));
        });

    test::add_test(
        "corgi-binary", "bits_llong",
        []() -> void
        {
            int test_data       = 0b11111111111110111001111101111101;
            int expected_result = 0b00000000000000111011100111110111;

            auto result = binary::bits_to_llong(
                4, 18, reinterpret_cast<unsigned char*>(&test_data), 4);

            assert_that(result,
                        test::equals(static_cast<long long>(expected_result)));
        });

    return test::run_all();
}