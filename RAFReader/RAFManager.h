#pragma once

#include <iostream>
#include <zlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>
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

class RAFManager
{
public:
    RAFManager() {};
    ~RAFManager() {};

    static RAFManager *getInstance();

    void extractRAF(std::ifstream &file_table, std::ifstream &file_data);
    void extractAllRAF(const char *path);


private:
    static RAFManager *instance;

};