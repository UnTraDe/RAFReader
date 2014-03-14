#pragma once

#include <fstream>
#include <hash_map>
#include <boost\algorithm\string.hpp>
#include <string>
#include "Utilities.h"


class Config
{
public:
	Config(std::string filePath);
	void MakeConfig();
	void LoadConfig();

	std::string GetValueString(std::string value) { return mConfig[value]; }

private:
	std::hash_map<std::string, std::string> mConfig;
	std::string mFilePath;
};