#version 330 core

in vec3 frag_pos;
in vec3 normal;

out vec4 FragColor;

uniform vec3 light_color;
uniform vec3 light_dir;
uniform vec3 object_color;

void main()
{
   FragColor = vec4(object_color, 1.0);
}