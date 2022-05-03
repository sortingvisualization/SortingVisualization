#pragma once
#include <map>
#include <string>

//List of draw types which need to be mapped inside DrawFactory
enum class DrawType
{
	CircleDraw,
	ColumnsDraw,
	LearningDraw,
	LinesDraw,
	PyramidDraw,
};

namespace
{
constexpr auto CIRCLE_DRAW = "Circle";
constexpr auto COLUMNS_DRAW = "Columns";
constexpr auto LINES_DRAW = "Lines";
constexpr auto PYRAMID_DRAW = "Pyramid";

//Mapping the name of the draw type with its enum. The name functions as a key in order to get the translation.
std::map<std::string, DrawType> nameToDrawTypeMap = {
	{CIRCLE_DRAW, DrawType::CircleDraw},
	{COLUMNS_DRAW, DrawType::ColumnsDraw},
	{LINES_DRAW, DrawType::LinesDraw},
	{PYRAMID_DRAW, DrawType::PyramidDraw},
};

constexpr auto SURFACE_HEIGHT_FACTOR = 0.8;
constexpr auto SURFACE_HEIGHT_PADDING_FACTOR = 0.2;
constexpr auto SURFACE_WIDTH_FACTOR = 0.8;
constexpr auto COLUMN_PADDING = 3;
constexpr auto BUTTON_PADDING = 5;
}
