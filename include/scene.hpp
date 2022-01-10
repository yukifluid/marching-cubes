#pragma once

#include <vector>

#include <glm/glm.hpp>

#include <memory>

#include "camera.hpp"
#include "light.hpp"
#include "object.hpp"
#include "shader.hpp"

class Scene
{
public:
    Scene();
    ~Scene();
    void Draw() const;
    void setCamera(const Camera &camera);
    void setLight(const DirectionalLight &light);
    void AppendObject(const Object &obj, glm::mat4 model, const Shader &shader);
    void Reset();

private:
    int n_objects;
    std::vector<Object> objects;
    std::vector<glm::mat4> models;
    std::vector<Shader> shaders;
    Camera camera;
    DirectionalLight light;
};
