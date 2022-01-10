#pragma once

#include <glm/glm.hpp>

#include <iostream>
#include <vector>
#include <algorithm>

class NearestNeighborSearch
{
public:
    NearestNeighborSearch(const glm::vec3& min_cord, const glm::vec3& max_cord, float gap, int n_particles);

    void Set(const std::vector<glm::dvec3> &pos);
    std::vector<int> Search(const glm::vec3 &pos) const;
    std::vector<std::vector<int>> Search(const std::vector<glm::vec3> &pos) const;

private:
    int n_particles;
    glm::vec3 min_cord;
    glm::vec3 max_cord;
    const float gap;
    int n_grids;
    glm::ivec3 grid_size;
    std::vector<std::pair<int, int>> hash_particle;
    std::vector<std::pair<int, int>> cell_range;

    bool IsInnerGrid(const glm::vec3& p) const;
    int getHash(const glm::vec3& p) const;
};