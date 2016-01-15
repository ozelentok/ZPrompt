#include "Colors.hpp"
#include "SystemInfo.hpp"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <algorithm>

static const std::string UNIX_SEPERATOR("/");
static const std::string ARROW_SEPERATOR("⮀");
static const std::string THIN_ARROW_SEPERATOR(" ⮁ ");
static const std::string CWD_HOME(" ~");
static const char* const HOME_ENVIRONMENT_VARIABLE_NAME = "HOME";
static const size_t DEFAULT_PROMPT_SIZE = 1024;

void replace_seperators(std::string& cwd)
{
	size_t index = 0;
	bool is_root = false;
	is_root = UNIX_SEPERATOR == cwd;
	while (true) {
		index = cwd.find(UNIX_SEPERATOR, index);
		if (index == std::string::npos) {
			break;
		}
		cwd.replace(index, UNIX_SEPERATOR.length(), THIN_ARROW_SEPERATOR);
		index += THIN_ARROW_SEPERATOR.length();
	}
	if (!is_root) {
		cwd.append(" ");
	}
}

void replace_home_path(std::string& cwd)
{
	const char* const raw_home = getenv(HOME_ENVIRONMENT_VARIABLE_NAME);
	if (raw_home == nullptr) {
		return;
	}
	std::string home(raw_home);
	size_t index = cwd.find(home, index);
	if (index == 0) {
		cwd.replace(index, home.length(), CWD_HOME);
	}
}

void append_arrow(std::string& prompt, const std::string& background_color,
	const std::string& next_background, bool is_final)
{
	if (is_final) {
		prompt += Colors::stop_colors();
	} else {
		prompt += Colors::start_background_color(next_background);
	}
	prompt += Colors::start_foreground_color(background_color);
	prompt += ARROW_SEPERATOR;
	prompt += Colors::stop_colors();
}

void append_user_and_hostname(std::string& prompt)
{
	prompt += Colors::start_background_color(Colors::USER_BACKGROUND);
	prompt += " ";
	prompt += SystemInfo::get_username();
	prompt += "@";
	prompt += SystemInfo::get_hostname();
	prompt += " ";
	append_arrow(prompt, Colors::USER_BACKGROUND, Colors::CWD_BACKGROUND, false);
}

void append_current_working_directory(std::string& prompt)
{
	std::string cwd = SystemInfo::get_cwd();
	replace_home_path(cwd);
	replace_seperators(cwd);
	prompt += Colors::start_background_color(Colors::CWD_BACKGROUND);
	prompt += cwd;
	append_arrow(prompt, Colors::CWD_BACKGROUND, Colors::CWD_BACKGROUND, true);
	prompt += "\n";
}

void append_prompt_line(std::string& prompt)
{
	prompt += Colors::start_background_color(Colors::PROMPT_BACKGROUND);
	prompt += SystemInfo::is_root() ? " # " : " $ ";
	prompt += Colors::stop_colors();
	prompt += Colors::start_foreground_color(Colors::PROMPT_BACKGROUND);
	prompt += ARROW_SEPERATOR;
	prompt += Colors::stop_colors();
}

int main()
{
	std::string prompt;
	prompt.reserve(DEFAULT_PROMPT_SIZE);
	append_user_and_hostname(prompt);
	append_current_working_directory(prompt);
	append_prompt_line(prompt);
	std::cout << prompt;
	return 0;
}
