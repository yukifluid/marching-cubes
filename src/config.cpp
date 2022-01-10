#include "config.hpp"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#define PI 3.141592653589

Config::Config(const std::string& path)
{
    std::ifstream ifs = std::ifstream(path);

    nlohmann::json config;
    ifs >> config;

    this->dt    = config["delta_time"].get<double>();
    this->rho_0 = config["rest_density"].get<double>();
    this->kp    = config["num_neighbor_particles"].get<int>();
    this->m     = config["particle_mass"].get<double>();
    this->bsize = glm::ivec3(config["boundary_size"][0], config["boundary_size"][1], config["boundary_size"][2]);
    this->fsize = glm::ivec3(config["fluid_size"][0], config["fluid_size"][1], config["fluid_size"][2]);

    this->bn = bsize.x*bsize.y*bsize.z - (bsize.x-2)*(bsize.y-2)*(bsize.z-2);
    this->fn = fsize.x*fsize.y*fsize.z;
    this->pn = bn + fn;

    double fvol = fn*m/rho_0;
    this->h = pow((3.0*kp*fvol)/(4.0*fn*PI), 1.0/3.0);
    this->r = pow(PI/(6.0*kp), 1.0/3.0) * h;

    this->min_cord = -glm::dvec3(bsize) * r;
    this->max_cord =  glm::dvec3(bsize) * r;
}

void Config::check() const
{
    std::cout << "dt: "    << this->dt    << std::endl;
    std::cout << "rho_0: " << this->rho_0 << std::endl;
    std::cout << "kp: "    << this->kp    << std::endl;
    std::cout << "m: "     << this->m     << std::endl;
    std::cout << "bn: "    << this->bn    << std::endl;
    std::cout << "fn: "    << this->fn    << std::endl;
    std::cout << "pn: "    << this->pn    << std::endl;
    std::cout << "h: "     << this->h     << std::endl;
    std::cout << "r: "     << this->r     << std::endl;
    std::cout << "bsize: " << "(" << this->bsize.x << ", " << this->bsize.y << ", " << this->bsize.z << ")" << std::endl;
    std::cout << "fsize: " << "(" << this->fsize.x << ", " << this->fsize.y << ", " << this->fsize.z << ")" << std::endl;
    std::cout << "min_cord: " << "(" << this->min_cord.x << ", " << this->min_cord.y << ", " << this->min_cord.z << ")" << std::endl;
    std::cout << "max_cord: " << "(" << this->max_cord.x << ", " << this->max_cord.y << ", " << this->max_cord.z << ")" << std::endl;
}