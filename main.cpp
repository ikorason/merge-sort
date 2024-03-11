#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <chrono>

// timing test resuults summary
// sorting duplicates elements is the fastest, after its random order, reverse sorted order
// the slowest is the `sorted order`

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
    // std::cout << "merge "; print(begin, middle, false); std::cout << "↔ "; print(middle, end);

    Iter left = begin;
    Iter right = middle;

    // loop through until either the left or right range is exhausted
    while (left != middle and right != end) {
        if (compare(*right, *left)) {
            tmp.push_back(std::move(*right++));
            // tmp.emplace_back(*right++);
        } else {
            tmp.push_back(std::move(*left++));
            // tmp.emplace_back(*right++);
        }
    }

    tmp.insert(tmp.end(), left, middle);
    tmp.insert(tmp.end(), right, end);

    std::move(tmp.begin(), tmp.end(), begin);

    // std::cout << " ⇒    "; print(begin, end);
}

template<typename Iter, typename Comparator>
void mergeSort(Iter begin, Iter end, Comparator compare) {
    // std::cout << "sort  "; print(begin, end);
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

template<typename Comparator>
void testSortedResult(Comparator compare) {
    std::list<int> l = {2, 5, 1, 7, 9, 2, 4, 3, 8, 11};
    std::cout << "Before sort: ";
    print(l.begin(), l.end());
    mergeSort(l.begin(), l.end(), compare);
    std::cout << "After sort: ";
    print(l.begin(), l.end());
}

// timing test
void testSorted() {
    std::list<int> l;
    std::cout << "Experiment 1: Sorted Order\n";
    for (int i = 1; i <= 10000; ++i) {
        l.push_back(i);
    }
    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(l.begin(), l.end(), std::less<int>());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";
}

void testReverseSorted() {
    std::list<int> l;
    std::cout << "Experiment 2: Reverse Sorted Order\n";
    for (int i = 10000; i >= 1; --i) {
        l.push_back(i);
    }
    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(l.begin(), l.end(), std::less<int>());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";
}

void testRandom() {
    std::list<int> l;
    std::cout << "Experiment 3: Random Order\n";
    for (int i = 0; i < 10000; ++i) {
        l.push_back(rand() % 10000);
    }
    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(l.begin(), l.end(), std::less<int>());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";
}

void testAllDuplicates() {
    std::list<int> l;
    std::cout << "Experiment 4: All Duplicate Elements\n";
    for (int i = 0; i < 10000; ++i) {
        l.push_back(42);
    }
    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(l.begin(), l.end(), std::less<int>());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";
}

int main() {
    // test result
    std::cout << "Test Result: " << std::endl;

    std::cout << "Ascending Order:\n";
    testSortedResult(std::less<int>());

    std::cout << "Descending Order:\n";
    testSortedResult(std::greater<int>());

    std::cout << std::endl;

    // timing
    std::cout << "TIMING TESTS: " << std::endl;
    testSorted();
    testReverseSorted();
    testRandom();
    testAllDuplicates();

    return 0;
}