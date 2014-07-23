#include <iostream>
#include "Engine.h"

using namespace std;

Engine engine;

int main(int argc, char const *argv[])
{
	engine.Initialize();
	engine.Run();

    return 0;
}