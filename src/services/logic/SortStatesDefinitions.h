#pragma once
#include <map>
#include <string>


enum class SortState
{
	NoContext,
	Compare,
	Sorted,
	BubbleSort,
	BubbleSortCompare,
	BubbleSortLastElementSorted,
	BubbleSortLastElementsSorted,
	BubbleSortSwap,
	InsertionSort,
	InsertionSortCompare,
	InsertionSortFirstElementSorted,
	InsertionSortSelectElement,
	InsertionSortPrevLower,
	InsertionSortSwap,
	MergeSort,
	MergeSortMarkParts,
	MergeSortSelectLowestValue,
	MergeSortTemporarilyCopy,
	MergeSortCopyBack,
	QuickSort,
	QuickSortAllElementsLowerThanPivot,
	QuickSortMarkLowerThanPivot,
	QuickSortMarkHigherThanPivot,
	QuickSortMarkPivotAsSorted,
	QuickSortMarkLastElementSorted,
	QuickSortSelectPivotBegin,
	QuickSortSelectPivot,
	QuickSortSelectNextElement,
	QuickSortSwapPivot,
	QuickSortSwapPivotWithTemporaryPivot,
	QuickSortSwapWithTemporaryPivot,
	RadixSort,
	RadixSortCopyValues,
	RadixSortCopyValuesBack,
	RadixSortDecrementCount,
	RadixSortIncrementCount,
	RadixSortMoveToTemporaryArray,
	RadixSortSelectBucket,
	RadixSortSelectBuckets,
	RadixSortSelectNextElement,
	RadixSortSelectOutgoing,
	RadixSortSumCount,
	SelectionSort,
	SelectionSortCompare,
	SelectionSortNoNeedSwap,
	SelectionSortMarkAsSorted,
	SelectionSortMarkLastAsSorted,
	SelectionSortSelectFirstElement,
	SelectionSortSelectFirstUnsortedElement,
	SelectionSortSelectNewLowestElement,
	SelectionSortSwapLowestWithUnsorted,
};

namespace
{
std::map<SortState, std::string> sortStateToTextMap =
{
	{SortState::Sorted, "Array is sorted!"},

	{SortState::BubbleSort, "Bubble Sort"},
	{SortState::BubbleSortCompare, "Check if %s > %s"},
	{SortState::BubbleSortLastElementSorted, "Mark %s as sorted"},
	{SortState::BubbleSortLastElementsSorted, "Mark %s and %s as sorted\n\tArray is sorted!"},
	{SortState::BubbleSortSwap, "Swapped %s with %s"},

	{SortState::InsertionSort, "Insertion Sort"},
	{SortState::InsertionSortCompare, "Compare with prev value\n\tswap if %s > %s"},
	{SortState::InsertionSortFirstElementSorted, "Mark first element\n\tas sorted"},
	{SortState::InsertionSortSelectElement, "Select first unsorted\n\telement: %s"},
	{SortState::InsertionSortPrevLower, "Elements are in order\nMark both as sorted"},
	{SortState::InsertionSortSwap, "Swapped %s with %s"},

	{SortState::MergeSort, "Merge Sort"},
	{SortState::MergeSortMarkParts, "Recursively select\nparts to be merged"},
	{SortState::MergeSortSelectLowestValue, "Select the lowest value"},
	{SortState::MergeSortTemporarilyCopy, " Copy %s to the\ntemporary array"},
	{SortState::MergeSortCopyBack, "Copy sorted elements back\nto the original array"},

	{SortState::QuickSort, "Quicksort"},
	{SortState::QuickSortAllElementsLowerThanPivot, "All values lower than pivot\n   Mark pivot as sorted"},
	{SortState::QuickSortMarkLowerThanPivot, "   Mark %s as\nlower than pivot"},
	{SortState::QuickSortMarkHigherThanPivot, "   Mark %s as\nhigher than pivot"},
	{SortState::QuickSortMarkPivotAsSorted, "Mark pivot as sorted"},
	{SortState::QuickSortMarkLastElementSorted, "Mark last element in\nthe subarray as sorted"},
	{SortState::QuickSortSelectPivotBegin, "Select last partition\n   element as pivot"},
	{SortState::QuickSortSelectPivot, "Select pivot"},
	{SortState::QuickSortSelectNextElement, "Select next element: %s"},
	{SortState::QuickSortSwapPivot, "Swap %s with pivot"},
	{SortState::QuickSortSwapPivotWithTemporaryPivot, "Swap pivot with\ntemporary pivot"},
	{SortState::QuickSortSwapWithTemporaryPivot, " Swap %s with\ntemporary pivot"},

	{SortState::RadixSort, "Radix sort"},
	{SortState::RadixSortCopyValues, "Copy all values to temp\narray in sorted order"},
	{SortState::RadixSortCopyValuesBack, "Copy sorted values back\nto the original array"},
	{SortState::RadixSortDecrementCount, "Decrement bucket count\nto get sorted position"},
	{SortState::RadixSortIncrementCount, "Increment bucket count"},
	{SortState::RadixSortMoveToTemporaryArray, "Copy %s to the temp array"},
	{SortState::RadixSortSelectBucket, "Select bucket with index %s"},
	{SortState::RadixSortSelectBuckets, "Select adjacent buckets\n  and add their values"},
	{SortState::RadixSortSelectNextElement, "\tSelect element: %s\nCurrent position value: %s"},
	{SortState::RadixSortSelectOutgoing, "Select outgoing array\nposition with index: %s"},
	{SortState::RadixSortSumCount, "\tSum equals to: %s\nSet sum in second bucket"},

	{SortState::SelectionSort, "Selection sort"},
	{SortState::SelectionSortCompare, "Compare with lowest value\n\tCheck if %s < %s"},
	{SortState::SelectionSortNoNeedSwap, "  Swapping is unnecessary\nMarked value is the lowest"},
	{SortState::SelectionSortMarkAsSorted, "Mark %s as sorted"},
	{SortState::SelectionSortMarkLastAsSorted, "Mark last element as sorted\n\t  Array is sorted!"},
	{SortState::SelectionSortSelectFirstElement, "Mark first element\n as lowest value"},
	{SortState::SelectionSortSelectFirstUnsortedElement, "Select first unsorted element"},
	{SortState::SelectionSortSelectNewLowestElement, "Mark %s as new\n lowest value"},
	{SortState::SelectionSortSwapLowestWithUnsorted, "Swap lowest value with\n first unsorted value"},
};

constexpr auto VALUE_PLACEHOLDER = "%s";
}

