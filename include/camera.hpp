#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <iostream>

class Camera
{
public:
    Camera();
    Camera(const glm::vec3 &position, const glm::vec3 &world_up = glm::vec3(0.0f, 1.0f, 0.0f), const glm::vec3 &target = glm::vec3(0.0f, 0.0f, 0.0f), float fov = 45.0f, float aspect_ratio = 800.0/600.0, float clippng_near = 0.1f, float clipping_far = 50.0f);

    glm::vec3 getPosition() const;
    glm::vec3 getUp() const;
    glm::vec3 getRight() const;
    glm::vec3 getTarget() const;
    glm::vec3 getWorldUp() const;
    float getFov() const;

    void Update(const glm::vec3 &position, const glm::vec3 &world_up, const glm::vec3 &target, float fov=45.0f);
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

private:
    glm::vec3 position;
    glm::vec3 up;       
    glm::vec3 right;    
    glm::vec3 target;   
    glm::vec3 world_up; 
    float field_of_view;
    float aspect_ratio;
    float clipping_near;
    float clipping_far;
};