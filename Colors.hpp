#pragma once

#include <string>

class Colors
{
	public:
		static const std::string USER_BACKGROUND;
		static const std::string CWD_BACKGROUND;
		static const std::string PROMPT_BACKGROUND;
		static const std::string WHITE;

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
