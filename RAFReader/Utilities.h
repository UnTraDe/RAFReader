#pragma once

#include <string>
#include <vector>
#include <sstream>

class StringUtils
{
public:
	static std::vector<std::string> Split(std::string s, char delimiter);
	static std::vector<std::string> Split(char *s, char delimiter);
};
