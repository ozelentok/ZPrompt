#pragma once

#include <string>

class Colors
{
	public:
		static const std::string CWD_FOREGROUND;
		static const std::string CWD_BACKGROUND;
		static const std::string PROMPT_BACKGROUND;

		static std::string start_foreground_color(const std::string& color);
		static std::string start_background_color(const std::string& color);
		static std::string stop_colors();

	private:
		static std::string start_color(
				const std::string& color_starter_template,
				const std::string& color);

	private:
		Colors() = delete;
};
