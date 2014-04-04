#include <iostream>
#include <string>
#include <fstream>
#include <RAFReader.h>

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc < 2)
	{
		cout << "You must specify at least one parameter" << endl;
		return 1;
	}

	RAFReader* reader = RAFReader::getInstance();

	string argument1(argv[1]);

	if (argument1 == "-a")
	{
		if (argv[2] == NULL)
		{
			cout << "Missing directory path" << endl;
			return 1;
		}

		reader->extractAllRAF(argv[2]);
	}
	else if (argument1 == "-s")
	{
		if (argv[2] == NULL)
		{
			cout << "Missing file path" << endl;
			return 1;
		}

		string filename(argv[2]);
		std::ifstream file_table(argv[2], std::ios::binary);
		std::ifstream file_data(filename.append(".dat"), std::ios::binary);

		cout << "Extracting " << filename << "..." << endl;
		reader->extractRAF(file_table, file_data);
	}
	else
	{
		cout << "Unknown argument specified \"" << argv[1] << "\"" << endl;
	}

	return 0;
}