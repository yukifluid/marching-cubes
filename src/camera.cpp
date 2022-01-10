#include "camera.hpp"

Camera::Camera()
{

}

Camera::Camera(const glm::vec3 &position, const glm::vec3 &world_up, const glm::vec3 &target, float field_of_view, float aspect_ratio, float clipping_near, float clipping_far)
    : position(position), world_up(world_up), target(target), field_of_view(field_of_view), aspect_ratio(aspect_ratio), clipping_near(clipping_near), clipping_far(clipping_far)
{
    glm::vec3 front = glm::normalize(this->target - this->position);
    this->right = glm::normalize(glm::cross(front, this->world_up));
    this->up    = glm::normalize(glm::cross(this->right, front));    
}

glm::vec3 Camera::getPosition() const { return this->position; }
glm::vec3 Camera::getUp() const { return this->up; }
glm::vec3 Camera::getRight() const { return this->right; }
glm::vec3 Camera::getTarget() const { return this->target; }
glm::vec3 Camera::getWorldUp() const { return this->world_up; }
float Camera::getFov() const { return this->field_of_view; }

void Camera::Update(const glm::vec3 &position, const glm::vec3 &world_up, const glm::vec3 &target, float fov)
{
    this->position = position;
    this->world_up = world_up;
    this->target = target;
    this->field_of_view = fov;

    glm::vec3 front = glm::normalize(this->target - this->position);
    this->right = glm::normalize(glm::cross(front, this->world_up));
    this->up    = glm::normalize(glm::cross(this->right, front));    
}

glm::mat4 Camera::getViewMatrix() const { return glm::lookAt(this->position, this->target, this->up); }
glm::mat4 Camera::getProjectionMatrix() const { return glm::perspective(glm::radians(this->field_of_view), this->aspect_ratio, this->clipping_near, this->clipping_far); }