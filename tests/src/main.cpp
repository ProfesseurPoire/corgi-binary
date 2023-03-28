#include "corgi/binary/binary.h"
#include "corgi/binary/dynamic_bitset.h"
#include "corgi/test/test.h"

using namespace corgi;

int main()
{
    test::add_test("dynamic_bitset", "max_size",
                   []() -> void
                   { std::cout << corgi::binary::dynamic_bitset::max_size(); });

    test::add_test("dynamic_bitset", "allocate_more_than_max",
                   []() -> void
                   {
                       check_any_throw(corgi::binary::dynamic_bitset(
                           corgi::binary::dynamic_bitset::max_size() + 1));
                   });

    test::add_test("dynamic_bitset", "allocate_max",
                   []() -> void
                   {
                       auto val = corgi::binary::dynamic_bitset::max_size();
                       check_no_throw(corgi::binary::dynamic_bitset(val));
                   });

    test::add_test("dynamic_bitset", "constructor",
                   []() -> void
                   {
                       check_no_throw(corgi::binary::dynamic_bitset(10);)
                           corgi::binary::dynamic_bitset bs(10);

                       assert_that(bs.size(), corgi::test::equals(10));

                       assert_that(bs.test(0), corgi::test::equals(false));
                   });

    test::add_test(
        "corgi-binary", "constructor-negative-count",
        []()
        { check_throw(binary::dynamic_bitset(-1), std::invalid_argument); });

    test::add_test("dynamic_bitset", "construction_with_default",
                   []() -> void
                   {
                       binary::dynamic_bitset bs(10, 1);
                       assert_that(bs.size(), corgi::test::equals(10));
                       assert_that(bs.test(1), corgi::test::equals(true));
                   });

    test::add_test("dynamic_bitset", "push_back",
                   []() -> void
                   {
                       binary::dynamic_bitset bs;
                       bs.push_back(false);
                       check_equals(bs.size(), 1LL);
                       check_equals(bs.byte_size(), 1LL);
                       check_equals(bs.test(0), false);

                       bs.push_back(false);
                       bs.push_back(false);
                       bs.push_back(false);
                       bs.push_back(false);
                       bs.push_back(false);
                       bs.push_back(false);
                       bs.push_back(true);
                       bs.push_back(false);
                       check_equals(bs.size(), 9LL);
                       check_equals(bs.byte_size(), 2LL);
                       check_equals(bs.test(7LL), true);
                   });

    test::add_test("corgi-binary", "any",
                   []() -> void
                   {
                       binary::dynamic_bitset bs(10);
                       check_equals(bs.any(), false);
                       bs.set(0, true);
                       check_equals(bs.any(), true);
                   });

    test::add_test("corgi-binary", "none",
                   []() -> void
                   {
                       binary::dynamic_bitset bs(10);
                       check_equals(bs.none(), true);
                       bs.set(0, true);
                       check_equals(bs.none(), false);
                   });

    test::add_test("corgi-binary", "all",
                   []() -> void
                   {
                       binary::dynamic_bitset bs(10, 1);
                       check_equals(bs.all(), true);
                       bs.set(0, false);
                       check_equals(bs.all(), false);
                   });

    test::add_test("corgi-binary", "empty",
                   []() -> void
                   {
                       binary::dynamic_bitset bs;
                       check_equals(bs.empty(), true);

                       check_equals(bs.none(), true);
                       check_equals(bs.any(), false);
                       check_equals(bs.all(), true);
                   });

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