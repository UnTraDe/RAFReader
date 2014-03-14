#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "Objects.h"
#include "Model.h"

using namespace std;

Model ModelFromFiles(char *sknPath, char *sklPath);

Model parseSKN(char *memory);
Model parseSKNFromFile(char *path);
std::vector<Bone> parseSKL(char *memory);
std::vector<Bone> parseSKLFromFile(char *path);
void parseANM(char *memory);
void parseANMFromFile(char *memory);