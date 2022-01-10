#version 330 core

in vec3 frag_pos;
in vec3 normal;

out vec4 FragColor;

uniform vec3 light_color;
uniform vec3 light_dir;
uniform vec3 object_color;

void main()
{
  vec3 norm = normalize(normal);

  float ambient_strength = 0.5;
  vec3 ambient = ambient_strength * light_color;

  float diff = max(dot(norm, light_dir), 0.0);
  vec3 diffuse = diff * light_color;

  vec3 result = (ambient + diffuse) * object_color;
  FragColor = vec4(result, 1.0);
}