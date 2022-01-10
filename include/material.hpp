#pragma once

#include <glm/glm.hpp>

class Material
{
public:
    Material(const glm::vec3 &color);

    glm::vec3 getColor() const;
private:
    glm::vec3 color;
};