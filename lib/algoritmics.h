//
// Created by Елизавета Кравченкова on 27.04.2023.
//

#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <iterator>

namespace liza {
    //находит первый элемент не удовлетворяющий p
    template<class InputIt, class UnaryPredicate>
    InputIt f_of_no(InputIt first, InputIt last, UnaryPredicate p) requires std::input_iterator<InputIt> {
        while (first != last) {
            if (!p(*first)) {
                return first;
            }
            ++first;
        }
        return first;
    }

//находит первый элемент, удовлетворяющий p
    template<class InputIt, class UnaryPredicate>
    InputIt f_of_yes(InputIt first, InputIt last, UnaryPredicate p) requires std::input_iterator<InputIt> {
        while (first != last) {
            if (p(*first)) {
                return first;
            }
            ++first;
        }
        return first;
    }

    // возвращает true, если все элементы диапазона удовлетворяют некоторому предикату. Иначе false
    template<class InputIt, class UnaryPredicate>
    bool all_of(InputIt first, InputIt last, UnaryPredicate p) requires std::input_iterator<InputIt> {
        return f_of_no(first, last, p) == last;
    }

    // возвращает true, если хотя бы один из элементов диапазона удовлетворяет некоторому предикату. Иначе false
    template<class InputIt, class UnaryPredicate>
    bool any_of(InputIt first, InputIt last, UnaryPredicate p) requires std::input_iterator<InputIt> {
        return f_of_yes(first, last, p) != last;
    }

    //возвращает true, если все элементы диапазона не удовлетворяют некоторому предикату. Иначе false
    template<class InputIt, class UnaryPredicate>
    bool none_of(InputIt first, InputIt last, UnaryPredicate p) requires std::input_iterator<InputIt> {
        return f_of_yes(first, last, p) == last;
    }

    //возвращает true, если ровно один элемент диапазона удовлетворяет некоторому предикату. Иначе false
    template<class InputIt, class UnaryPredicate>
    bool one_of(InputIt first, InputIt last, UnaryPredicate p) requires std::input_iterator<InputIt> {
        bool find = false;
        while (first != last) {
            if (p(*first)) {
                if (find) {
                    return false;
                }
                find = true;
            }
            ++first;
        }
        return find;
    }

    //возвращает true, если все элементы диапазона находятся в отсортированном порядке относительно некоторого критерия
    template<class InputIt, class Compare>
    bool is_sorted(InputIt first, InputIt last, Compare comp) requires std::input_iterator<InputIt> {
        if (first == last) {
            return true;
        }
        InputIt next = first;
        ++next;
        while (next != last) {
            if (!comp(*first,
                      *next)) {  //в данном случае при равенстве будет false. Можно поменть, поменят местами элементы в вызове компаратора и убрать отрицание
                return false;
            }
            ++first;
            ++next;
        }
        return true;
    }

    template<class InputIt>
    bool is_sorted(InputIt first, InputIt last) requires std::input_iterator<InputIt> {
        return liza::is_sorted(first, last, std::less<>());
    }

    // возвращает true, если в диапазоне есть элемент, делящий все элементы на удовлетворяющие и не удовлетворяющие - некоторому предикату. Иначе false.
    template<class InputIt, class UnaryPredicate>
    bool is_partitioned(InputIt first, InputIt last, UnaryPredicate p) requires std::input_iterator<InputIt> {
        bool state = p(*first);
        if (!state) {
            return false;
        }
        ++first;
        uint64_t kount = 0;
        while (first != last) {
            if (p(*first) != state) {
                state = p(*first);
                if (kount == 1) {
                    return false;
                }
                kount++;
            }
            ++first;
        }
        return true;
    };

    //находит первый элемент, не равный заданному
    template<class InputIt, class Zadannyy>
    InputIt find_not(InputIt first, InputIt last, const Zadannyy& val) requires std::input_iterator<InputIt> {
        auto comp = [&val](typename InputIt::value_type elem) { return (elem == val); };
        return f_of_no(first, last, comp);
    }

    //находит первый элемент, равный заданному, с конца
    template<class InputIt, class Zadannyy>
    InputIt find_backward(InputIt first, InputIt last, const Zadannyy& val) requires std::input_iterator<InputIt> {
        InputIt find = first;
        while (first != last) {
            if (*first == val) {
                find = first;
            }
            ++first;
        }
        return find;
    }

    //находит первый элемент, равный заданному, с конца
    template<class BiderIt, class Zadannyy>
    BiderIt find_backward(BiderIt first, BiderIt last, const Zadannyy& val) requires std::bidirectional_iterator<BiderIt> {
        --last;
        while (last != first) {
            if (*last == val) {
                return last;
            }
            --last;
        }
        return first;
    }


    //возвращает true, если заданная последовательность является палиндромом относительно некоторого условия. Иначе false.
    template<class BiderIt, class Compare>
    bool is_palindrome(BiderIt first, BiderIt last,  Compare comp) requires std::bidirectional_iterator<BiderIt> {
        int64_t n = std::distance(first, last);
        --last;
        for (int64_t i = 0; i < (n / 2); ++i) {
            if (!comp((*first),(*last))) {
                return false;
            }
            ++first;
            --last;

        }
        return true;
    }


    template<class T>
    class XrangeIterator {
    public:
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef size_t size_type;
        typedef std::input_iterator_tag iterator_category;
        typedef XrangeIterator self;

        XrangeIterator(const T& pos, const T& step) : my_position_(pos), step_(step) {}

        bool operator==(const self& lhs) const {
            return my_position_ == lhs.my_position_;
        }

        bool operator!=(const self& lhs) const {
            return my_position_ < lhs.my_position_;
        }

        reference operator->() {
            return my_position_;
        }

        reference operator*() {
            return my_position_;
        }

        //префиксная версия возвращает значение после инкремента
        self& operator++() {
            my_position_ = my_position_ + step_;
            return *this;
        }

        //постфиксная версия возвращает значение до инкремента
        self operator++(int) {
            self oldValue(my_position_, step_);
            ++(*this);
            return oldValue;
        }

    protected:
        T my_position_;
        T step_;
    };

    template<class T>
    class xrange_object {
    public:
        xrange_object(const T& start, const T& end, const T& step) : start_(start), end_(end), step_(step) {}

        XrangeIterator<T> begin() {
            return XrangeIterator<T>(start_, step_);
        }

        XrangeIterator<T> end() {
            return XrangeIterator<T>(end_, step_);
        }

    private:
        T start_;
        T end_;
        T step_;
    };

    template<class T>
    xrange_object<T> xrange(const T& start, const T&  end, const T&  step = 1) {
        return xrange_object<T>(start, end, step);
    }

    template<class T>
    xrange_object<T> xrange(const T& end) {
        return xrange_object<T>(T(), end, 1);
    }


    template<class FirstContainer, class SecondContainer, class FirstContainerT,class SecondContainerT>
    class ZipIterator {
    public:
        typedef ptrdiff_t difference_type;
        typedef typename FirstContainerT::value_type value_type1;
        typedef typename SecondContainerT::value_type value_type2;
        typedef std::pair<value_type1, value_type2> value_type;
        typedef value_type* pointer;
        typedef value_type& reference;
        typedef size_t size_type;
        typedef std::input_iterator_tag iterator_category;
        typedef ZipIterator self;

        ZipIterator(FirstContainer it1, SecondContainer it2) : iter1(it1), iter2(it2) {
            value = std::make_pair(*iter1, *iter2);
        }

        bool operator==(const self& lhs) const {
            return iter1 == lhs.iter1 && iter2 == lhs.iter2;
        }

        bool operator!=(const self& lhs) const {
            return !operator==(lhs);
        }

        auto operator->() {
            return value;
        }

        auto operator*() {
            return value;
        }

        //префиксная версия возвращает значение после инкремента
        self& operator++() {
            ++iter1;
            ++iter2;
            value.first = *iter1;
            value.second = *iter2;
            return *this;
        }

        //постфиксная версия возвращает значение до инкремента
        self operator++(int) {
            self oldValue(iter1, iter2);
            ++(*this);
            return oldValue;
        }

    protected:
        FirstContainer iter1;
        SecondContainer iter2;
        value_type value;
    };

    template<class FirstContainer, class SecondContainer>
    class zip_object {
    public:
        typedef typename FirstContainer::iterator iterator1;
        typedef typename SecondContainer::iterator iterator2;

        zip_object(FirstContainer& l, SecondContainer& r) : C1(&l), C2(&r), size1(l.size()), size2(r.size()) {
        }

        ZipIterator<iterator1, iterator2,FirstContainer,SecondContainer> begin() {
            return ZipIterator<iterator1, iterator2,FirstContainer,SecondContainer>(C1->begin(), C2->begin());
        }

        ZipIterator<iterator1, iterator2,FirstContainer,SecondContainer> end() {
            if (size1 < size2) {
                if constexpr (std::is_same_v<typename std::iterator_traits<iterator1>::iterator_category, std::bidirectional_iterator_tag>) {
                    typename SecondContainer::iterator iterator22 = C2->end();
                    for (uint64_t i = 0; i < (size2 - size1); ++i) {
                        --iterator22;
                    }
                    return ZipIterator<iterator1, iterator2,FirstContainer,SecondContainer>(C1->end(), iterator22);
                } else {
                    return Do(C2->end());
                }
            } else if (size1 > size2) {
                if constexpr (std::is_same_v<typename std::iterator_traits<iterator1>::iterator_category, std::bidirectional_iterator_tag>) {
                    typename FirstContainer::iterator iterator11 = C1->end();
                    for (uint64_t i = 0; i < (size1 - size2); ++i) {
                        --iterator11;
                    }
                    return ZipIterator<iterator1, iterator2,FirstContainer,SecondContainer>(iterator11, C2->end());
                } else {
                    return Do(C1->end());
                }
            }
            return ZipIterator<iterator1, iterator2,FirstContainer,SecondContainer>(C1->end(), C2->end());
        }

    private:
        /*
        template<class T>
        ZipIterator<iterator1, iterator2> Do(const T& iterator) requires std::bidirectional_iterator<T> {
            if (size1 < size2) {
                typename SecondContainer::iterator iterator22 = C2->end();
                for (uint64_t i = 0; i < (size2 - size1); ++i) {
                    --iterator22;
                }
                return ZipIterator<iterator1, iterator2>(C1->end(), iterator22);
            } else {
                typename FirstContainer::iterator iterator11 = C1->end();
                for (uint64_t i = 0; i < (size1 - size2); ++i) {
                    --iterator11;
                }
                return ZipIterator<iterator1, iterator2>(iterator11, C2->end());
            }

        }


        template<class T>
        ZipIterator<iterator1, iterator2> Do(const T& ite) requires std::random_access_iterator<T> {
            if (size1 < size2) {
                ite = ite - (size2 - size1);
                return ZipIterator<FirstContainer, T>(C1->end(), ite);
            } else {
                ite = ite - (size1 - size2);
                return ZipIterator<T, SecondContainer>(ite, C2->end());
            }
        }
*/
        template<class T>
        ZipIterator<iterator1, iterator2,FirstContainer,SecondContainer> Do(const T& iterator) requires std::input_iterator<T> {
            if (size1 < size2) {
                typename SecondContainer::iterator iterator22 = C2->begin();
                for (uint64_t i = 0; i < size1; ++i) {
                    ++iterator22;
                }
                return ZipIterator<iterator1, iterator2,FirstContainer,SecondContainer>(C1->end(), iterator22);
            } else {
                typename FirstContainer::iterator iterator11 = C1->begin();
                for (uint64_t i = 0; i < size2; ++i) {
                    ++iterator11;
                }
                return ZipIterator<iterator1, iterator2,FirstContainer,SecondContainer>(iterator11, C2->end());
            }
        }


        FirstContainer* C1;
        SecondContainer* C2;

        int64_t size1;
        int64_t size2;
    };

    template<class FirstContainer, class SecondContainer>
    zip_object<FirstContainer, SecondContainer> zip(FirstContainer& l, SecondContainer& r) {
        return zip_object<FirstContainer, SecondContainer>(l, r);
    }

}
