#version 330 core

uniform mat4 MVP;

layout(location = 0) in vec3 position;
layout(location = 1) in int boneIndex;
layout(location = 2) in vec4 weight;
layout(location = 3) in vec3 normal;
layout(location = 4) in vec2 UVCords;

out vec2 UV;

void main()
{
    gl_Position =  MVP * vec4(position, 1.0f);
    UV = UVCords;
}