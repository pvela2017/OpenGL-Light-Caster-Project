#version 440 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 TexCoords;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

uniform mat4 rot;
uniform mat4 trans_ida;
uniform mat4 trans_vuelta;
uniform bool flag_rot;

void main()
{
	if (flag_rot)
	{
		gl_Position = projection * view * model  * trans_vuelta * rot * trans_ida* vec4(position, 1.0f);
    		vs_out.FragPos = vec3(model * vec4(position, 1.0));
    		vs_out.Normal = transpose(inverse(mat3(model))) * normal;
    		vs_out.TexCoords = texCoords;
    		vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
	}
	else
	{
		gl_Position = projection * view * model * vec4(position, 1.0f);
		vs_out.FragPos = vec3(model * vec4(position, 1.0));
   		vs_out.Normal = transpose(inverse(mat3(model))) * normal;
    		vs_out.TexCoords = texCoords;
    		vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
	}

}