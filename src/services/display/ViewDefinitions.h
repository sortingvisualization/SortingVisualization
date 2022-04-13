#pragma once

enum class ViewType
{
	AlgorithmSelectionView,
	ModeSelectionView,
	LearningModeView,
	VisualizationModeView
};

namespace
{
constexpr auto MODE_CONTEXT = "ModeContext";
constexpr auto SORT_CONTEXT = "SortContext";

constexpr auto LEARNING_MODE = "Learning";
constexpr auto VISUALIZATION_MODE = "Visualization";

constexpr auto BACK_BUTTON_LABEL = "Back";
constexpr auto RESET_BUTTON_LABEL = "Reset";
constexpr auto SORT_BUTTON_LABEL = "Sort";
constexpr auto STOP_BUTTON_LABEL = "Stop";
constexpr auto PREV_BUTTON_LABEL = "<";
constexpr auto NEXT_BUTTON_LABEL = ">";
constexpr auto FIRST_BUTTON_LABEL = "<<";
constexpr auto LAST_BUTTON_LABEL = ">>";
}
