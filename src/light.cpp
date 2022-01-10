#include "light.hpp"

Light::Light()
{

}

Light::Light(const glm::vec3 &color)
: color(color)
{

}

glm::vec3 Light::getColor() const { return this->color; }

DirectionalLight::DirectionalLight()
{

}

DirectionalLight::DirectionalLight(const glm::vec3 &color, const glm::vec3 &direction)
: Light(color), direction(direction)
{

}

glm::vec3 DirectionalLight::getDirection() const { return this->direction; }