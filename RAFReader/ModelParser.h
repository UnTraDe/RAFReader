#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Objects.h"
#include "Model.h"
#include "Skeleton.h"

using namespace std;

Model ModelFromFiles(char *sknPath, char *sklPath);

Model parseSKN(char *memory);
Model parseSKNFromFile(char *path);
Skeleton parseSKL(char *memory);
Skeleton parseSKLFromFile(char *path);
Animation parseANM(char *memory);
Animation parseANMFromFile(char *memory);