#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Utilities.h"

#define UNCOMPRESS_BUFFER_LENGTH 2000000

struct PathEntry
{
	int offest;
	int length;
};

struct FileEntry
{
	int pathHash;
	int dataOffset;
	int dataSize;
	int pathListIndex;
};

class RAFReader
{
public:
	RAFReader() {};
	~RAFReader() {};

	static RAFReader *getInstance();

	void extractRAF(std::ifstream &file_table, std::ifstream &file_data);
	void extractAllRAF(const char *path);

private:
	static RAFReader *instance;

};