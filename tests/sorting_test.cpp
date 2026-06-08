#include <gtest/gtest.h>

#include <vector>

#include "include/legacy/sorting.h"

namespace {
using SortFn = void (*)(std::vector<int>&);

void ExpectSorted(SortFn sort_fn, const std::vector<int>& input, const std::vector<int>& expected) {
	auto values = input;
	sort_fn(values);
	EXPECT_EQ(values, expected);
}
} // namespace

TEST(SortingTest, InsertionHandlesEmptyVector) {
	ExpectSorted(&Sorting::insertion, {}, {});
}

TEST(SortingTest, InsertionHandlesSingleElement) {
	ExpectSorted(&Sorting::insertion, {42}, {42});
}

TEST(SortingTest, InsertionSortsAlreadySortedInput) {
	ExpectSorted(&Sorting::insertion, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5});
}

TEST(SortingTest, InsertionSortsReverseOrderedInput) {
	ExpectSorted(&Sorting::insertion, {5, 4, 3, 2, 1}, {1, 2, 3, 4, 5});
}

TEST(SortingTest, InsertionSortsMixedValues) {
	ExpectSorted(&Sorting::insertion, {3, -1, 7, 3, 0, -5}, {-5, -1, 0, 3, 3, 7});
}

TEST(SortingTest, SelectionHandlesEmptyVector) {
	ExpectSorted(&Sorting::selection, {}, {});
}

TEST(SortingTest, SelectionHandlesSingleElement) {
	ExpectSorted(&Sorting::selection, {42}, {42});
}

TEST(SortingTest, SelectionSortsAlreadySortedInput) {
	ExpectSorted(&Sorting::selection, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5});
}

TEST(SortingTest, SelectionSortsReverseOrderedInput) {
	ExpectSorted(&Sorting::selection, {5, 4, 3, 2, 1}, {1, 2, 3, 4, 5});
}

TEST(SortingTest, SelectionSortsMixedValues) {
	ExpectSorted(&Sorting::selection, {3, -1, 7, 3, 0, -5}, {-5, -1, 0, 3, 3, 7});
}
