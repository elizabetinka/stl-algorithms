//
// Created by Елизавета Кравченкова on 27.04.2023.
//
#include <lib/algoritmics.h>
#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <list>


TEST(AlgoritmicsTestSuite, All_Of_Test) {
    std::initializer_list<int> li{50, 40, 10, 20, 20};

    auto is_even = [](int elem) { return !(elem % 2); };
    ASSERT_TRUE(liza::all_of(li.begin(), li.end(), is_even));
    li = {0, 1, 50, 2, 2, 5};
    ASSERT_FALSE(liza::all_of(li.begin(), li.end(), is_even));
}

TEST(AlgoritmicsTestSuite, Any_Of_Test) {
    std::initializer_list<int> li{1, 5, 3, 9, 20};

    auto is_even = [](int elem) { return !(elem % 2); };
    ASSERT_TRUE(liza::any_of(li.begin(), li.end(), is_even));

    li = {5, 1, 5, 111, 3, 5};
    ASSERT_FALSE(liza::any_of(li.begin(), li.end(), is_even));
}

TEST(AlgoritmicsTestSuite, None_Of_Test) {
    std::initializer_list<int> li{1, 5, 3, 9, 111};

    auto is_even = [](int elem) { return !(elem % 2); };
    ASSERT_TRUE(liza::none_of(li.begin(), li.end(), is_even));

    li = {5, 1, 5, 111, 2, 5};
    ASSERT_FALSE(liza::none_of(li.begin(), li.end(), is_even));
}

TEST(AlgoritmicsTestSuite, One_Of_Test) {
    std::initializer_list<int> li{2, 5, 3, 9, 111};

    auto is_even = [](int elem) { return !(elem % 2); };
    ASSERT_TRUE(liza::one_of(li.begin(), li.end(), is_even));

    li = {5, 1, 5, 111, 1, 5};
    ASSERT_FALSE(liza::one_of(li.begin(), li.end(), is_even));
    li = {5, 1, 2, 111, 2, 5};
    ASSERT_FALSE(liza::one_of(li.begin(), li.end(), is_even));
}

bool ignore_case(char a, char b) {
    return (tolower(a) < tolower(b));
}

bool more(int a, int b) {
    return a < b;
}

TEST(AlgoritmicsTestSuite, Is_Sorted_Test) {
    std::vector<char> v2 = {'A', 'b', 'C', 'd', 'E'};
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 8};
    std::list l = {1, 2, 3, 4, 5};

    ASSERT_TRUE(liza::is_sorted(v.begin(), v.end()));
    ASSERT_TRUE(liza::is_sorted(l.begin(), l.end()));
    ASSERT_TRUE(liza::is_sorted(v2.begin(), v2.end(), ignore_case));


    v.assign({2, 2, 2, 2, 2, 2, 2});
    ASSERT_FALSE(liza::is_sorted(v.begin(), v.end()));
    ASSERT_TRUE(liza::is_sorted(v.begin(), v.end(), std::less_equal<>()));
}

TEST(AlgoritmicsTestSuite, Is_Partitioned_Test) {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 8};
    auto is_even = [](int elem) { return !(elem % 2); };
    ASSERT_FALSE(liza::is_partitioned(v.begin(), v.end(), is_even));
    v.assign({2, 2, 2, 5, 5, 5, 5, 5});
    ASSERT_TRUE(liza::is_partitioned(v.begin(), v.end(), is_even));
    v.assign({5, 5, 5, 5, 5, 2, 2});
    ASSERT_FALSE(liza::is_partitioned(v.begin(), v.end(), is_even));
}

TEST(AlgoritmicsTestSuite, Find_Not_Test) {
    std::vector<int> v = {1, 1, 1, 3, 5, 2, 4};
    ASSERT_TRUE(*liza::find_not(v.begin(), v.end(), 1) == 3);
}

TEST(AlgoritmicsTestSuite, Find_Backward_Test) {
    std::vector<int> v = {1, 1, 1, 3, 5, 2, 4};
    ASSERT_FALSE(liza::find_backward(v.begin(), v.end(), 1) == v.begin());
    ASSERT_TRUE(liza::find_backward(v.begin(), v.end(), 1) == (v.begin() + 2));
}
template<class T>
bool ravno(T a, T b) {
    return (a==b);
}
TEST(AlgoritmicsTestSuite, Is_Palindrom_Test) {
    std::vector<int> v = {1, 1, 1, 3, 5, 2, 4};

    ASSERT_FALSE(liza::is_palindrome(v.begin(), v.end(),ravno<int>));
    v.assign({1, 2, 3, 2, 3, 2, 1});
    ASSERT_TRUE(liza::is_palindrome(v.begin(), v.end(),ravno<int>));
    v.assign({1, 2, 3, 3, 2, 1});
    ASSERT_TRUE(liza::is_palindrome(v.begin(), v.end(),ravno<int>));
}

TEST(AlgoritmicsTestSuite, XRange_Test) {
    auto x = liza::xrange(1.5, 5.5);
    std::vector<double> v{x.begin(), x.end()}; // 1.5 2.5 3.5 4.5
    std::vector<double> ans = {1.5, 2.5, 3.5, 4.5};
    ASSERT_TRUE(ans == v);

    std::vector<int> ans_int = {1, 3, 5};
    uint64_t j = 0;
    // 1 3 5
    for (auto i: liza::xrange(1, 6, 2)) {
        ASSERT_TRUE(ans_int[j] == i);
        ++j;
    }

    ans_int.assign({0, 1, 2, 3});
    auto y = liza::xrange(4);
    std::vector<int> v2{y.begin(), y.end()}; // 0 1 2 3
    ASSERT_TRUE(ans_int == v2);

    j=0;
    std::vector<std::string> ans_str = {"ab","abab","ababab","abababab"};
    for (auto i: liza::xrange<std::string>("ab", "ababababab", "ab")) {
        ASSERT_TRUE(ans_str[j] == i);
        ++j;
    }
}


TEST(AlgoritmicsTestSuite, Zip_Test) {
    std::list l = {1, 2, 3, 4, 5};
    std::vector v = {'a', 'b', 'c', 'd'};
    std::vector<std::pair<int, char>> ans = {{1, 'a'},
                                             {2, 'b'},
                                             {3, 'c'},
                                             {4, 'd'},
    };

    uint64_t i = 0;
    for (auto value: liza::zip(l, v)) {
        ASSERT_TRUE(value.first == ans[i].first && value.second == ans[i].second);
        ++i;
    }
}
