#include "corgi/binary/binary.h"
#include "corgi/binary/dynamic_bitset.h"
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

    test::add_test("dynamic_bitset", "construction",
                   []() -> void
                   {
                       corgi::binary::dynamic_bitset bs(10);
                       assert_that(bs.size(), corgi::test::equals(10));

                       assert_that(bs.test(0), corgi::test::equals(false));
                   });

    test::add_test("dynamic_bitset", "construction_with_default",
                   []() -> void
                   {
                       binary::dynamic_bitset bs(10, 1);
                       assert_that(bs.size(), corgi::test::equals(10));
                       assert_that(bs.test(1), corgi::test::equals(true));
                   });

    test::add_test("dynamic_bitset", "set_bit",

                   []() -> void
                   {
                       binary::dynamic_bitset bs(10);
                       bs.set(4, 1);

                       assert_that(bs.test(4), corgi::test::equals(true));
                       assert_that(bs.to_ullong(), corgi::test::equals(16));
                   });

    test::add_test("dynamic_bitset", "slice",
                   []()
                   {
                       //    binary::dynamic_bitset set(10, 1);
                       //    set.set(0, 0);

                       //    auto subset = set.slice(0, 5);

                       //    check_equals(subset.size(), 5);
                       //    check_equals(subset[0], false);
                       //    check_equals(subset[1], true);
                       //    check_equals(subset[2], true);
                       //    check_equals(subset[3], true);
                       //    check_equals(subset[4], true);
                   });

    return test::run_all();
}