#pragma once

#include <string>

class SystemInfo 
{
	public:
		static std::string get_hostname();
		static std::string get_username();
		static std::string get_cwd();
		static bool is_root();

	private:
		SystemInfo() = delete;
};
