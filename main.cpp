#include <iostream>
#include <list>
#include <chrono>

template<typename Iter>
using value_type_t = typename std::iterator_traits<Iter>::value_type;

template <typename Iterator, typename Comparator = std::less<value_type_t<Iterator>>>
void merge(const Iterator& first, const Iterator& middle, const Iterator& last, Comparator lessThan = Comparator{}) {
    // sizes
    auto s1 = std::distance(first, middle);
    auto s2 = std::distance(middle, last);

    // create temporary vectors to hold the two sub-arrays
    std::vector<value_type_t<Iterator>> left(s1);
    std::vector<value_type_t<Iterator>> right(s2);

    std::move(first, middle, left.begin());
    std::move(middle, last, right.begin());

    auto it1 = left.begin();
    auto it2 = right.begin();
    auto current = first;

    while (it1 != left.end() && it2 != right.end()) {
        if (lessThan(*it1, *it2)) {
            *current++ = std::move(*it1++);
        } else {
            *current++ = std::move(*it2++);
        }
    }

    std::move(it1, left.end(), current);
    std::move(it2, right.end(), current);
}

template<typename Iterator, typename Comparator = std::less<value_type_t<Iterator>>>
void mergeSort(const Iterator& first, const Iterator& last, Comparator lessThan = Comparator{}) {
    // calculate total no. of elements between the two iterators
    auto const N = std::distance(first, last);
    if (N <= 1) return;
    // calculate the iterator pointing to the middle of the current range    
    auto middle = std::next(first, N/2);
    // recursively sort the two halves
    mergeSort(first, middle, lessThan);
    mergeSort(middle, last, lessThan);
    // merge the sorted halves
    merge(first, middle, last, lessThan);
}

int main() {
    std::list<int> myList = {38, 27, 43, 3, 9, 82, 10};
    
    // std::cout << "Original List: ";
    // for (const auto& element : myList) {
    //     std::cout << element << " ";
    // }
    // std::cout << std::endl;

    mergeSort(myList.begin(), myList.end());

    // std::cout << "Sorted List: ";
    // for (const auto& element : myList) {
    //     std::cout << element << " ";
    // }
    // std::cout << std::endl;

    return 0;
}