#pragma once

#include <vector>
#include "Objects.h"

class Skeleton
{
public:
	Skeleton(std::vector<Bone> bones, std::vector<short> boneIDs);
	~Skeleton();

private:
	std::vector<Bone> m_bones;
	std::vector<short> m_boneIDs;
};