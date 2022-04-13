#pragma once
#include <map>
#include <string>

enum class SortType
{
	BubbleSort,
	InsertionSort,
	MergeSort,
	QuickSort,
	RadixSort,
	SelectionSort
};

namespace
{
constexpr auto BUBBLE_SORT = "Bubble Sort";
constexpr auto INSERTION_SORT = "Insertion sort";
constexpr auto MERGE_SORT = "Merge sort";
constexpr auto QUICK_SORT = "Quicksort";
constexpr auto RADIX_SORT = "Radix sort";
constexpr auto SELECTION_SORT = "Selection sort";

constexpr auto MIN_ELEMENTS_LEARNING_MODE = 5;
constexpr auto MAX_ELEMENTS_LEARNING_MODE = 20;
constexpr auto DEFAULT_ARRAY_SIZE_VISUALIZATION_MODE = 150;

std::map<std::string, SortType> nameToSortTypeMap = {
	{BUBBLE_SORT, SortType::BubbleSort},
	{INSERTION_SORT, SortType::InsertionSort},
	{MERGE_SORT, SortType::MergeSort},
	{QUICK_SORT, SortType::QuickSort},
	{RADIX_SORT, SortType::RadixSort},
	{SELECTION_SORT, SortType::SelectionSort}
};
}
