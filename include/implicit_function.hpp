#pragma once

#include <glm/glm.hpp>

#include <vector>

#include "nearest_neighbor_search.hpp"
#include "kernel.hpp"

class ImplicitFunction
{
public:
    ImplicitFunction();
    virtual double f(const glm::dvec3& p) const=0;
    glm::vec3 getNormal(const glm::vec3& p) const;
};

class SphereField : public ImplicitFunction
{
public:
    SphereField(double r);
    double f(const glm::dvec3& p) const;

private:
    double r;
};

class ColorField : public ImplicitFunction
{
public:
    ColorField(const glm::dvec3& min_cord, const glm::dvec3& max_cord, int n_particles, const std::vector<glm::dvec3>& pos, const std::vector<double>& vol, double rho_0, double h);
    double f(const glm::dvec3& p) const;

private:
    const std::vector<glm::dvec3>& pos;
    const std::vector<double>& vol;
    double rho_0;
    double h;
    std::vector<double> rho;
    NearestNeighborSearch nns;
};