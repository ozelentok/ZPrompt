#include "SystemInfo.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <limits.h>

std::string SystemInfo::get_hostname()
{
	char hostname[HOST_NAME_MAX];
	int hostname_result = gethostname(hostname, HOST_NAME_MAX);
	if (hostname_result) {
		return std::string("NO_HOSTNAME");
	}
	return std::string(hostname);
}

std::string SystemInfo::get_username()
{
	const passwd* user_info = getpwuid(getuid());
	if (user_info == nullptr) {
		return std::string("NO_USERNAME");
	}
	return std::string(user_info->pw_name);
}

std::string SystemInfo::get_cwd()
{
	const char* cwd = getenv("PWD");
	if (cwd == nullptr) {
		return "NO_CWD";
	}
	return std::string(cwd);
}

bool SystemInfo::is_root()
{
	return getuid() == 0;
}
