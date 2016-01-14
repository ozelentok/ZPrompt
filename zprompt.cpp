#include <string>
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
static const string BACKGROUND_COLOR_TEMPLATE("%{[48;5;m%}");
static const string FOREGROUND_COLOR_TEMPLATE("%{[38;5;m%}");
static const string COLORS_STOP("%{[0m%}");
static const char* const HOME_ENVIRONMENT_VARIABLE_NAME = "HOME";
static const size_t COLOR_INSERTION_INDEX = 9;
static const size_t DEFAULT_PROMPT_SIZE = 150;

namespace colors
{
	static const string CWD_FOREGROUND("255");
	static const string CWD_BACKGROUND("25");
	static const string PROMPT_BACKGROUND("22");
}

string start_color(const string& color_starter_template, const string& color)
{
	string color_starter(color_starter_template);
	color_starter.insert(COLOR_INSERTION_INDEX, color);
	return color_starter;
}

string start_foreground_color(const string& color)
{
	return start_color(FOREGROUND_COLOR_TEMPLATE, color);
}

string start_background_color(const string& color)
{
	return start_color(BACKGROUND_COLOR_TEMPLATE, color);
}

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
	prompt += start_foreground_color(colors::CWD_FOREGROUND);
	prompt += start_background_color(colors::CWD_BACKGROUND);
	prompt += cwd;
	prompt += COLORS_STOP;
	prompt += start_foreground_color(colors::CWD_BACKGROUND);
	prompt += ARROW_SEPERATOR;
	prompt += COLORS_STOP;
}

void append_prompt_line(string& prompt)
{
	prompt += start_background_color(colors::PROMPT_BACKGROUND);
	prompt += PROMPT_START;
	prompt += COLORS_STOP;
	prompt += start_foreground_color(colors::PROMPT_BACKGROUND);
	prompt += ARROW_SEPERATOR;
	prompt += COLORS_STOP;
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
