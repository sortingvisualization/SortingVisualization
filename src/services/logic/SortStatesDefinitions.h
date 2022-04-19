#pragma once
#include <map>

#include "TranslationConsts.h"


enum class SortState
{
	NoContext,
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
std::map<SortState, Tc> sortStateToTranslationMap =
{
	{SortState::Sorted, Tc::StateSorted},

	{SortState::BubbleSort, Tc::StateBubbleSort},
	{SortState::BubbleSortCompare, Tc::StateBubbleSortCompare},
	{SortState::BubbleSortLastElementSorted, Tc::StateBubbleSortLastElementSorted},
	{SortState::BubbleSortLastElementsSorted, Tc::StateBubbleSortLastElementsSorted},
	{SortState::BubbleSortSwap, Tc::StateBubbleSortSwap},

	{SortState::InsertionSort, Tc::StateInsertionSort},
	{SortState::InsertionSortCompare, Tc::StateInsertionSortCompare},
	{SortState::InsertionSortFirstElementSorted, Tc::StateInsertionSortFirstElementSorted},
	{SortState::InsertionSortSelectElement, Tc::StateInsertionSortSelectElement},
	{SortState::InsertionSortPrevLower, Tc::StateInsertionSortPrevLower},
	{SortState::InsertionSortSwap, Tc::StateInsertionSortSwap},

	{SortState::MergeSort, Tc::StateMergeSort},
	{SortState::MergeSortMarkParts, Tc::StateMergeSortMarkParts},
	{SortState::MergeSortSelectLowestValue, Tc::StateMergeSortSelectLowestValue},
	{SortState::MergeSortTemporarilyCopy, Tc::StateMergeSortTemporarilyCopy},
	{SortState::MergeSortCopyBack, Tc::StateMergeSortCopyBack},

	{SortState::QuickSort, Tc::StateQuickSort},
	{SortState::QuickSortAllElementsLowerThanPivot, Tc::StateQuickSortAllElementsLowerThanPivot},
	{SortState::QuickSortMarkLowerThanPivot, Tc::StateQuickSortMarkLowerThanPivot},
	{SortState::QuickSortMarkHigherThanPivot, Tc::StateQuickSortMarkHigherThanPivot},
	{SortState::QuickSortMarkPivotAsSorted, Tc::StateQuickSortMarkPivotAsSorted},
	{SortState::QuickSortMarkLastElementSorted, Tc::StateQuickSortMarkLastElementSorted},
	{SortState::QuickSortSelectPivotBegin, Tc::StateQuickSortSelectPivotBegin},
	{SortState::QuickSortSelectPivot, Tc::StateQuickSortSelectPivot},
	{SortState::QuickSortSelectNextElement, Tc::StateQuickSortSelectNextElement},
	{SortState::QuickSortSwapPivot, Tc::StateQuickSortSwapPivot},
	{SortState::QuickSortSwapPivotWithTemporaryPivot, Tc::StateQuickSortSwapPivotWithTemporaryPivot},
	{SortState::QuickSortSwapWithTemporaryPivot, Tc::StateQuickSortSwapWithTemporaryPivot},

	{SortState::RadixSort, Tc::StateRadixSort},
	{SortState::RadixSortCopyValues, Tc::StateRadixSortCopyValues},
	{SortState::RadixSortCopyValuesBack, Tc::StateRadixSortCopyValuesBack},
	{SortState::RadixSortDecrementCount, Tc::StateRadixSortDecrementCount},
	{SortState::RadixSortIncrementCount, Tc::StateRadixSortIncrementCount},
	{SortState::RadixSortMoveToTemporaryArray, Tc::StateRadixSortMoveToTemporaryArray},
	{SortState::RadixSortSelectBucket, Tc::StateRadixSortSelectBucket},
	{SortState::RadixSortSelectBuckets, Tc::StateRadixSortSelectBuckets},
	{SortState::RadixSortSelectNextElement, Tc::StateRadixSortSelectNextElement},
	{SortState::RadixSortSelectOutgoing, Tc::StateRadixSortSelectOutgoing},
	{SortState::RadixSortSumCount, Tc::StateRadixSortSumCount},

	{SortState::SelectionSort, Tc::StateSelectionSort},
	{SortState::SelectionSortCompare, Tc::StateSelectionSortCompare},
	{SortState::SelectionSortNoNeedSwap, Tc::StateSelectionSortNoNeedSwap},
	{SortState::SelectionSortMarkAsSorted, Tc::StateSelectionSortMarkAsSorted},
	{SortState::SelectionSortMarkLastAsSorted, Tc::StateSelectionSortMarkLastAsSorted},
	{SortState::SelectionSortSelectFirstElement, Tc::StateSelectionSortSelectFirstElement},
	{SortState::SelectionSortSelectFirstUnsortedElement, Tc::StateSelectionSortSelectFirstUnsortedElement},
	{SortState::SelectionSortSelectNewLowestElement, Tc::StateSelectionSortSelectNewLowestElement},
	{SortState::SelectionSortSwapLowestWithUnsorted, Tc::StateSelectionSortSwapLowestWithUnsorted},
};

constexpr auto VALUE_PLACEHOLDER = "%s";
}

