#include "nearest_neighbor_search.hpp"

NearestNeighborSearch::NearestNeighborSearch(const glm::vec3& min_cord, const glm::vec3& max_cord, float gap, int n_particles)
: min_cord(min_cord), max_cord(max_cord), gap(gap), n_particles(n_particles)
{
    this->grid_size = glm::ivec3(glm::ceil((max_cord - min_cord) / gap));
    this->n_grids = this->grid_size.x * this->grid_size.y * this->grid_size.z;
    this->hash_particle = std::vector<std::pair<int, int>>(n_particles);
    this->cell_range = std::vector<std::pair<int, int>>(this->n_grids);
    this->max_cord = this->min_cord + glm::vec3(this->grid_size) * this->gap;
}

void NearestNeighborSearch::Set(const std::vector<glm::dvec3> &pos)
{
    for(int i = 0; i < this->n_particles; i++)
    {
        int hash = this->getHash(pos[i]);
        this->hash_particle[i] = std::make_pair(hash, i);
    }
    std::sort(this->hash_particle.begin(), this->hash_particle.end());

    std::fill(this->cell_range.begin(), this->cell_range.end(), std::make_pair(0xffffffff, 0xffffffff));
    for(int i = 0; i < this->n_particles; i++)
    {
        if(this->hash_particle[i].first < 0) continue;
        if(cell_range[this->hash_particle[i].first].first == 0xffffffff) cell_range[this->hash_particle[i].first].first = i;
        cell_range[this->hash_particle[i].first].second = i+1;
    }
}

std::vector<int> NearestNeighborSearch::Search(const glm::vec3 &pos) const
{
    // 距離がh以下とは限らない
    std::vector<int> neighbors;
    for(int dx = -1; dx <= 1; dx++) for(int dy = -1; dy <= 1; dy++) for(int dz = -1; dz <= 1; dz++)
    {
        glm::vec3 p = pos + glm::vec3(dx, dy, dz) * this->gap;
        if(!this->IsInnerGrid(p)) continue;
        int hash = this->getHash(p);
        for(int i = this->cell_range[hash].first; i < this->cell_range[hash].second; i++)
        {
            int idx = this->hash_particle[i].second;
            neighbors.push_back(idx);
        }
    }
    return neighbors;
}

std::vector<std::vector<int>> NearestNeighborSearch::Search(const std::vector<glm::vec3> &pos) const
{
    std::vector<std::vector<int>> all_neighbors;
    for(glm::vec3 p : pos) all_neighbors.push_back(this->Search(p));
    return all_neighbors;
}

bool NearestNeighborSearch::IsInnerGrid(const glm::vec3& p) const
{
    if(p.x < this->min_cord.x || p.y < this->min_cord.y || p.z < this->min_cord.z || this->max_cord.x <= p.x || this->max_cord.y <= p.y || this->max_cord.z <= p.z) return false;
    return true;
}

int NearestNeighborSearch::getHash(const glm::vec3& p) const
{
    glm::ivec3 idx = glm::floor((p - this->min_cord) / this->gap);
    int hash = idx.x + idx.y * this->grid_size.x + idx.z * this->grid_size.x * this->grid_size.y;
    if(!this->IsInnerGrid(p)) hash = -1;
    return hash;
}