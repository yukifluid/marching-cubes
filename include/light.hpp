#pragma once

#include <glm/glm.hpp>

class Light
{
public:
    Light();
    Light(const glm::vec3 &color);

    glm::vec3 getColor() const;

protected:
    glm::vec3 color;
};

class DirectionalLight : public Light
{
public:
    DirectionalLight();
    DirectionalLight(const glm::vec3 &color, const glm::vec3 &direction);

    glm::vec3 getDirection() const;

private:
    glm::vec3 direction;
};