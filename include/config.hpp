#pragma once

#include <string>

#include <glm/glm.hpp>

class Config
{
public:
    Config(const std::string& path);

    void check() const;

    double dt;
    double rho_0;
    int kp;
    double m; 
    glm::ivec3 bsize;
    glm::ivec3 fsize;
    int bn;
    int fn;
    int pn;
    double h;
    double r;
    glm::dvec3 min_cord;
    glm::dvec3 max_cord;
};