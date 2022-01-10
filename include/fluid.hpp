#pragma once

#include <glm/glm.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>

#include "config.hpp"

class Fluid
{
public:
    Fluid(std::string config_path, std::string csv_path, int ts);

    std::vector<glm::dvec3> pos;
    std::vector<double> vol;

    Config config;

private:
    std::vector<std::string> split(const std::string& str, char delimiter) const;

};