#include "fluid.hpp"

#define PI 3.141592653589
using json = nlohmann::json;

Fluid::Fluid(std::string config_path, std::string csv_path, int ts)
: config(config_path)
{
    this->pos = std::vector<glm::dvec3>(config.fn);
    this->vol = std::vector<double>(config.fn);

    // 粒子ファイル読み込み
    std::ifstream ifs = std::ifstream(csv_path);
    std::string line;

    getline(ifs, line);
    int n = 0;
    while(getline(ifs, line))
    {
        std::vector<std::string> row = split(line, ',');
        int timestep  = std::stoi(row[0]);
        int label     = std::stoi(row[1]);
        glm::dvec3 p  = glm::vec3(std::stod(row[6]), std::stod(row[7]), std::stod(row[8]));
        double volume = std::stod(row[2]);
        if(timestep != ts) continue;
        if(label == 0) continue;
        this->pos.at(n) = p;
        this->vol.at(n++) = volume;
    }
}

std::vector<std::string> Fluid::split(const std::string& str, char delimiter) const
{
    std::istringstream stream(str);
    std::string field;
    std::vector<std::string> result;
    while(getline(stream, field, delimiter)) 
    {
        result.push_back(field);
    }
    return result;
}