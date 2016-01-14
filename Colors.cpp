#include "Colors.hpp"

#ifdef ZSH
static const size_t COLOR_INSERTION_INDEX = 9;
static const std::string BACKGROUND_COLOR_TEMPLATE("%{[48;5;m%}");
static const std::string FOREGROUND_COLOR_TEMPLATE("%{[38;5;m%}");
static const std::string COLORS_STOP("%{[0m%}");

const std::string Colors::CWD_FOREGROUND("255");
const std::string Colors::CWD_BACKGROUND("25");
const std::string Colors::PROMPT_BACKGROUND("22");

#else
static const size_t COLOR_INSERTION_INDEX = 7;
static const std::string BACKGROUND_COLOR_TEMPLATE("\e[48;5;m");
static const std::string FOREGROUND_COLOR_TEMPLATE("\e[38;5;m");
static const std::string COLORS_STOP("\e[0m");

const std::string Colors::CWD_FOREGROUND("255");
const std::string Colors::CWD_BACKGROUND("25");
const std::string Colors::PROMPT_BACKGROUND("22");
#endif

std::string Colors::start_color(
	const std::string& color_starter_template,
	const std::string& color)
{
	std::string color_starter(color_starter_template);
	color_starter.insert(COLOR_INSERTION_INDEX, color);
	return color_starter;
}

std::string Colors::start_foreground_color(const std::string& color)
{
	return start_color(FOREGROUND_COLOR_TEMPLATE, color);
}

std::string Colors::start_background_color(const std::string& color)
{
	return start_color(BACKGROUND_COLOR_TEMPLATE, color);
}

std::string Colors::stop_colors()
{
	return COLORS_STOP;
}
