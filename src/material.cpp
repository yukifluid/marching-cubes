#include "material.hpp"

Material::Material(const glm::vec3 &color)
: color(color)
{

}

glm::vec3 Material::getColor() const { return this->color; }