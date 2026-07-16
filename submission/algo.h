#pragma once

#include <deque>

template<class T, class Comp>
std::deque<T> Merge(const std::deque<T>& half1, const std::deque<T>& half2, const Comp& comparator) {
    std::deque<T> result;

    auto i = half1.begin();
    auto j = half2.begin();

    while (i < half1.end() && j < half2.end()) {
        if (comparator(*i, *j)) {
            result.push_back(*i);
            ++i;
        } else {
            result.push_back(*j);
            ++j;
        }
    }

    while (i < half1.end()) {
        result.push_back(*i);
        ++i;
    }

    while (j < half2.end()) {
        result.push_back(*j);
        ++j;
    }

    return result;
}

template<class T, class Comp>
std::deque<T> MergeSort(const std::deque<T>& src, const Comp& comparator) {
    if (src.size() <= 1) {
        return src;
    }

    const size_t mid = src.size() / 2;

    std::deque<T> left(src.begin(), src.begin() + mid);
    std::deque<T> right(src.begin() + mid, src.end());

    left = MergeSort(left, comparator);
    right = MergeSort(right, comparator);

    return Merge(left, right, comparator);
}
