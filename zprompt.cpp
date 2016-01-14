#include "Colors.hpp"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include <algorithm>

using std::string;
using std::stringstream;

static const string UNIX_SEPERATOR("/");
static const string ARROW_SEPERATOR("⮀");
static const string THIN_ARROW_SEPERATOR(" ⮁ ");
static const string CWD_HOME(" ~");
static const string PROMPT_START("\n $ ");
static const char* const HOME_ENVIRONMENT_VARIABLE_NAME = "HOME";
static const size_t DEFAULT_PROMPT_SIZE = 150;

void replace_seperators(string& cwd)
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

void replace_home_path(string& cwd)
{
	const char* const raw_home = getenv(HOME_ENVIRONMENT_VARIABLE_NAME);
	if (raw_home == nullptr) {
		return;
	}
	string home(raw_home);
	size_t index = cwd.find(home, index);
	if (index == 0) {
		cwd.replace(index, home.length(), CWD_HOME);
	}
}

void append_current_working_directory(string& prompt)
{
	const char* raw_cwd = getenv("PWD");
	if (raw_cwd == nullptr) {
		return;
	}
	string cwd = raw_cwd;
	replace_home_path(cwd);
	replace_seperators(cwd);
	prompt += Colors::start_foreground_color(Colors::CWD_FOREGROUND);
	prompt += Colors::start_background_color(Colors::CWD_BACKGROUND);
	prompt += cwd;
	prompt += Colors::stop_colors();
	prompt += Colors::start_foreground_color(Colors::CWD_BACKGROUND);
	prompt += ARROW_SEPERATOR;
	prompt += Colors::stop_colors();
}

void append_prompt_line(string& prompt)
{
	prompt += Colors::start_background_color(Colors::PROMPT_BACKGROUND);
	prompt += PROMPT_START;
	prompt += Colors::stop_colors();
	prompt += Colors::start_foreground_color(Colors::PROMPT_BACKGROUND);
	prompt += ARROW_SEPERATOR;
	prompt += Colors::stop_colors();
}

int main()
{
	string prompt;
	prompt.reserve(DEFAULT_PROMPT_SIZE);
	append_current_working_directory(prompt);
	append_prompt_line(prompt);
	std::cout << prompt;
	return 0;
}
