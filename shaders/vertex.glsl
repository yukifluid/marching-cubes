#version 330 core

layout (location = 0) in vec3 attribute_pos;
layout (location = 1) in vec3 attribute_normal;

out vec3 frag_pos;
out vec3 normal;

uniform mat4 model;
uniform mat4 normal_matrix;
uniform mat4 view;
uniform mat4 projection; 

void main()
{
   gl_Position = projection * view * model * vec4(attribute_pos, 1.0);
   frag_pos = vec3(model * vec4(attribute_pos, 1.0));
   normal = mat3(normal_matrix) * attribute_normal;
}