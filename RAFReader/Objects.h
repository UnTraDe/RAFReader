#pragma once

struct Vertex
{
	float position[3];
	char boneIndex[4];
	float weights[4];
	float normals[3];
	float textureCords[2];
};

struct Bone
{
	short id;
	short parent;
	float position[3];
	float quaternion[4];
	char name[32];
};

struct AnimationPos
{
	float rotation[4];
	float x;
	float y;
	float z;
};