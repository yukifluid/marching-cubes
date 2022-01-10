#include "scene.hpp"

Scene::Scene()
{
    this->n_objects = 0;
}

Scene::~Scene()
{

}

void Scene::setCamera(const Camera &camera)
{
    this->camera = camera;
}

void Scene::setLight(const DirectionalLight &light)
{
    this->light = light;
}

void Scene::AppendObject(const Object &obj, glm::mat4 model, const Shader &shader)
{
    this->objects.push_back(obj);
    this->models.push_back(model);
    this->shaders.push_back(shader);
    this->n_objects++;
}

void Scene::Draw() const
{
    for(int i = 0; i < this->n_objects; i++)
    {
        this->shaders[i].Use();

        this->shaders[i].SetVec3("light_color", this->light.getColor());
        this->shaders[i].SetVec3("light_dir", this->light.getDirection());

        glm::mat4 projection = this->camera.getProjectionMatrix();
        glm::mat4 view = this->camera.getViewMatrix();

        this->shaders[i].SetVec3("object_color", this->objects[i].getMaterial().getColor());

        this->shaders[i].SetMat4("projection", projection);
        this->shaders[i].SetMat4("view", view);
        this->shaders[i].SetMat4("model", this->models[i]);
        this->shaders[i].SetMat4("normal_matrix", glm::transpose(glm::inverse(models[i])));

        this->objects[i].getGeometry().Draw();
    }
}

void Scene::Reset()
{
    this->objects.clear();
    this->models.clear();
    this->shaders.clear();
    this->n_objects = 0;
}