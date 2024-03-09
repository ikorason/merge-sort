#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <chrono>

// please use at least 'g++ -std=c++14` flag to run this app
// or else lambda auto won't work

template<typename Iter>
void print(const Iter& begin, const Iter& end, bool new_line = true)
{
    std::for_each(begin, end, [](auto& i) { std::cout << i << " "; });
    if (new_line) {
        std::cout << std::endl;
    }
}

template <typename Iter, typename Comparator>
void merge(Iter begin, Iter middle, Iter end, Comparator compare) {
    // temporary vector to store the merged elements
    std::vector<typename Iter::value_type> tmp;
    // the vector is reserved to avoid reallocations
    // its size is set to the distance between `begin` and `end`
    tmp.reserve(std::distance(begin, end));

    // this line prints the elements in the left and right halves of the current merge operation
    std::cout << "merge "; print(begin, middle, false); std::cout << "↔ "; print(middle, end);

    Iter left = begin;
    Iter right = middle;

    // loop through until either the left or right range is exhausted
    while (left != middle and right != end) {
        if (compare(*right, *left)) {
            tmp.emplace_back(*right++);
        } else {
            tmp.emplace_back(*left++);
        }
    }

    tmp.insert(tmp.end(), left, middle);
    tmp.insert(tmp.end(), right, end);

    std::move(tmp.begin(), tmp.end(), begin);
    std::cout << " ⇒    "; print(begin, end);
}

template<typename Iter, typename Comparator>
void mergeSort(Iter begin, Iter end, Comparator compare) {
    std::cout << "sort  "; print(begin, end);
    // calculate total no. of elements between the two iterators
    int size = std::distance(begin, end);
    if (size <= 1) return;
    // calculate the iterator pointing to the middle of the current range    
    auto middle = std::next(begin, size/2);
    // recursively sort the two halves
    mergeSort(begin, middle, compare);
    mergeSort(middle, end, compare);
    // merge the sorted halves
    merge(begin, middle, end, compare);
}

int main() {
    std::list<int> l = {2, 5, 1, 7, 9, 2, 4, 3, 8, 11};
    mergeSort(l.begin(), l.end(), std::less<int>());
    std::cout << "done  "; print(l.begin(), l.end());
    return 0;
}