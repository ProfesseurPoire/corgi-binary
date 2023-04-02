#include "corgi/binary/binary.h"
#include "corgi/binary/dynamic_bitset.h"
#include "corgi/test/test.h"

using namespace corgi;

int main()
{
    // NOTE : This test probably fails on 32 bits because I suspect this
    // will return the max value of uint and the +1 will just loop back to 0
    // Maybe it'd be nice to run the code on both 32 and 64 bit environment
    test::add_test(
        "dynamic_bitset", "allocate_more_than_max",
        []() -> void
        {
            std::cout << corgi::binary::dynamic_bitset::max_size() << std::endl;
            check_throw(corgi::binary::dynamic_bitset(
                            corgi::binary::dynamic_bitset::max_size() + 1),
                        std::length_error);
        });

    test::add_test(
        "dynamic_bitset", "insert",
        []() -> void
        {
            corgi::binary::dynamic_bitset bs {true, true, false, false};
            bs.insert(2, 3, true);

            check_equals(bs.size(), static_cast<std::size_t>(7));
            check_equals(bs.test(0), true);
            check_equals(bs.test(1), true);
            check_equals(bs.test(2), true);
            check_equals(bs.test(3), true);
            check_equals(bs.test(4), true);
            check_equals(bs.test(5), false);
            check_equals(bs.test(6), false);
        });

    test::add_test("dynamic_bitset", "slice",
                   []() -> void
                   {
                       corgi::binary::dynamic_bitset bs(
                           {true, false, true, false, true, false});

                       auto s = bs.slice(2, 4);

                       check_equals(s.size(), static_cast<std::size_t>(3));
                       check_equals(s.test(0), true);
                       check_equals(s.test(1), false);
                       check_equals(s.test(2), true);

                       check_throw(bs.slice(6, 2), std::out_of_range);
                       check_throw(bs.slice(1, 10), std::out_of_range);
                       check_throw(bs.slice(3, 2), std::invalid_argument);
                   });

    test::add_test("dynamic_bitset", "comparison",
                   []() -> void
                   {
                       corgi::binary::dynamic_bitset bs {true, false, true};
                       corgi::binary::dynamic_bitset bs2 {true, false, true};
                       bs2.push_back("true");
                       bs2.pop_back();

                       check_equals(bs, bs2);
                   });

    test::add_test("dynamic_bitset", "insert_initializer_list",
                   []() -> void
                   {
                       corgi::binary::dynamic_bitset bs;
                       bs.insert(0, {true, false, true, false});
                       check_equals(bs.size(), static_cast<std::size_t>(4));
                       check_equals(bs.test(0), true);
                       check_equals(bs.test(1), false);
                       check_equals(bs.test(2), true);
                       check_equals(bs.test(3), false);

                       bs.insert(1, {true, false});
                       check_equals(bs.size(), static_cast<std::size_t>(6));
                       check_equals(bs.test(0), true);
                       check_equals(bs.test(1), true);
                       check_equals(bs.test(2), false);
                       check_equals(bs.test(3), false);
                       check_equals(bs.test(4), true);
                       check_equals(bs.test(5), false);

                       check_throw(bs.insert(10, {false}), std::out_of_range);
                   });

    test::add_test("dynamic_bitset", "insert_one",
                   []() -> void
                   {
                       corgi::binary::dynamic_bitset bs;
                       bs.insert(0, true);
                       check_equals(bs.size(), static_cast<std::size_t>(1));
                       check_equals(bs.test(0), true);

                       bs.insert(1, 4, false);
                       check_equals(bs.size(), static_cast<std::size_t>(5));
                       check_equals(bs.test(0), true);
                       check_equals(bs.test(1), false);
                       check_equals(bs.test(2), false);
                       check_equals(bs.test(3), false);
                       check_equals(bs.test(4), false);

                       bs.insert(4, 4, true);
                       check_equals(bs.size(), static_cast<std::size_t>(9));
                       check_equals(bs.test(0), true);
                       check_equals(bs.test(1), false);
                       check_equals(bs.test(2), false);
                       check_equals(bs.test(3), false);
                       check_equals(bs.test(4), true);
                       check_equals(bs.test(5), true);
                       check_equals(bs.test(6), true);
                       check_equals(bs.test(7), true);
                       check_equals(bs.test(8), false);

                       check_throw(bs.insert(10, true), std::out_of_range);
                   });

    test::add_test(
        "dynamic_bitset", "constructor",
        []() -> void
        {
            corgi::binary::dynamic_bitset bs({true, false, false, true});
            check_equals(bs.size(), static_cast<std::size_t>(4));
            check_equals(bs.test(0), true);
            check_equals(bs.test(1), false);
            check_equals(bs.test(2), false);
            check_equals(bs.test(3), true);
        });

    test::add_test("dynamic_bitset", "at",
                   []() -> void
                   {
                       corgi::binary::dynamic_bitset bs;
                       try
                       {
                           // bs.at(1);
                       }
                       catch(std::exception& e)
                       {
                           std::cout << e.what() << std::endl;
                       }
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

    test::add_test("dynamic_bitset", "construction_with_default",
                   []() -> void
                   {
                       binary::dynamic_bitset bs(10, 1);
                       assert_that(bs.size(), corgi::test::equals(10));
                       assert_that(bs.test(1), corgi::test::equals(true));
                   });

    test::add_test(
        "dynamic_bitset", "push_back",
        []() -> void
        {
            binary::dynamic_bitset bs;
            bs.push_back(false);
            check_equals(bs.size(), static_cast<std::size_t>(1));
            check_equals(bs.byte_size(), static_cast<std::size_t>(1));
            check_equals(bs.test(0), false);

            bs.push_back(false);
            bs.push_back(false);
            bs.push_back(false);
            bs.push_back(false);
            bs.push_back(false);
            bs.push_back(false);
            bs.push_back(true);
            bs.push_back(false);
            check_equals(bs.size(), static_cast<std::size_t>(9));
            check_equals(bs.byte_size(), static_cast<std::size_t>(2));
            check_equals(bs.test(7), true);
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

    test::add_test(
        "corgi-binary", "clear",
        []() -> void
        {
            binary::dynamic_bitset bs(10, 1);
            bs.clear();
            check_equals(bs.size(), static_cast<std::size_t>(0));
            check_equals(bs.byte_size(), static_cast<std::size_t>(2));
            bs.push_back(false);
            bs.push_back(true);
            check_equals(bs.test(0), false);
            check_equals(bs.test(1), true);
            check_equals(bs.size(), static_cast<std::size_t>(2));
            check_equals(bs.byte_size(), static_cast<std::size_t>(2));
        });

    test::add_test(
        "dynamic_bitset", "erase",
        []() -> void
        {
            binary::dynamic_bitset bs({true, false, true, true, false});
            bs.erase(3);
            check_equals(bs.size(), static_cast<std::size_t>(4));
            check_equals(bs.test(0), true);
            check_equals(bs.test(1), false);
            check_equals(bs.test(2), true);
            check_equals(bs.test(3), false);

            check_throw(bs.erase(5), std::out_of_range);
        });

    test::add_test(
        "dynamic_bitset", "erase_range",
        []() -> void
        {
            binary::dynamic_bitset bs({true, false, true, true, false});
            bs.erase(2, 3);
            check_equals(bs.size(), static_cast<std::size_t>(3));
            check_equals(bs.test(0), true);
            check_equals(bs.test(1), false);
            check_equals(bs.test(2), false);

            check_throw(bs.erase(1, 8), std::out_of_range);
            check_throw(bs.erase(10, 8), std::out_of_range);
            check_throw(bs.erase(2, 1), std::invalid_argument);
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