#version 330 core

in vec2 UV;
in float lightIntensity;
out vec3 color;

uniform sampler2D textSampler;

void main()
{
	vec3 textureColor = texture(textSampler, UV).rgb;
	color = textureColor * lightIntensity;
}
