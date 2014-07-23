#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include "Objects.h"
#include "Model.h"

using namespace std;

class ModelParser
{
public:
	static std::shared_ptr<Model> ParseModel(std::string filePath);
	static std::shared_ptr<Model> ParseModel(const char* memory);
};



