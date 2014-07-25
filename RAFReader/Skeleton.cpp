#include "Skeleton.h"

Skeleton::Skeleton(std::vector<Bone> bones, std::vector<short> boneIDs)
{
	m_bones = bones;
	m_boneIDs = boneIDs;
}

Skeleton::~Skeleton()
{

}