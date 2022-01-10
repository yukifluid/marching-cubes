#include "implicit_function.hpp"

ImplicitFunction::ImplicitFunction()
{

}

glm::vec3 ImplicitFunction::getNormal(const glm::vec3& p) const
{
    const double eps = 1e-4;
    double nx = (this->f(p + glm::vec3(eps, 0, 0)) - this->f(p - glm::vec3(eps, 0, 0))) / eps;
    double ny = (this->f(p + glm::vec3(0, eps, 0)) - this->f(p - glm::vec3(0, eps, 0))) / eps;
    double nz = (this->f(p + glm::vec3(0, 0, eps)) - this->f(p - glm::vec3(0, 0, eps))) / eps;
    glm::vec3 n = glm::normalize(glm::vec3(nx, ny, nz)); 
    return n;
}

SphereField::SphereField(double r)
: r(r)
{

}

double SphereField::f(const glm::dvec3& p) const
{
    double val = glm::length(p) - r;
    return val;
}

ColorField::ColorField(const glm::dvec3& min_cord, const glm::dvec3& max_cord, int n_particles, const std::vector<glm::dvec3>& pos, const std::vector<double>& vol, double rho_0, double h)
: nns(min_cord, max_cord, h, n_particles), pos(pos), vol(vol), rho_0(rho_0), h(h)
{
    this->rho = std::vector<double>(n_particles);

    nns.Set(pos);

    // 密度計算
    for(int i = 0; i < n_particles; i++)
    {
        this->rho[i] = 0;
        std::vector<int> neighbors = nns.Search(pos[i]);
        for(int j : neighbors)
        {
            double r = glm::length(this->pos[i] - this->pos[j]);
            this->rho[i] += this->rho_0 * this->vol[j] * Poly6(r, h);
        }
    }
}

double ColorField::f(const glm::dvec3& p) const
{
    std::vector<int> neighbors = nns.Search(p);

    double val = 0;
    for(int i : neighbors)
    {
        double r = glm::length(p - this->pos[i]);
        val += this->rho_0 * this->vol[i] / this->rho[i] * Poly6(r, h);
    }
    return -val;
}
