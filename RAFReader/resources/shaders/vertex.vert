#version 330 core

uniform mat4 MVP;
uniform vec3 lightSource = vec3(0.0f, 300.0f, 400.0f);

layout(location = 0) in vec3 position;
layout(location = 1) in int boneIndex;
layout(location = 2) in vec4 weight;
layout(location = 3) in vec3 normal;
layout(location = 4) in vec2 UVCords;

out vec2 UV;
out float lightIntensity;

void main()
{
    gl_Position =  MVP * vec4(position, 1.0f);
    UV = UVCords;

    vec3 N = normalize((MVP * vec4(normal, 1.0)).xyz);
	vec3 L = normalize(lightSource);
	lightIntensity = clamp(0.5 + dot(N, L) * (1.0-0.5), 0.0, 1.0);
}