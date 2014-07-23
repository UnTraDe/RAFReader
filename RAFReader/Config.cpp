#include "Config.h"

Config::Config(std::string filePath)
{
	mFilePath = filePath;
}

void Config::LoadConfig()
{
	std::ifstream file(mFilePath);

	while (!file.is_open()) {
		MakeConfig();
		file = std::ifstream(mFilePath);
	}
	
	char buffer[100];
	
	do
	{
		memset(buffer, 0, sizeof(buffer));
		file.getline(buffer, sizeof(buffer));
		std::string line(buffer);
		std::vector<std::string> result = StringUtils::Split(line, '=');
		mConfig[result[0]] = result[1];
	} while (!file.eof());

	file.close();
}

void Config::MakeConfig()
{
	char file_buffer[] = "GameDirectory=C:\\Riot Games\\League of Legends";
	std::ofstream file(mFilePath);
	file.write(file_buffer, sizeof(file_buffer));
	file.close();
}