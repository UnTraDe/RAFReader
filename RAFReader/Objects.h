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
	//char boneName[32];
	int parent;
	float scale;
	float matrix[12];
};

struct AnimationPos
{
	float rotation[4];
	float x;
	float y;
	float z;
};