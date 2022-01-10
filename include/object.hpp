#pragma once

#include "geometry.hpp"
#include "material.hpp"

class Object
{
public:
    Object(const Geometry& geometry, const Material& material);

    const Geometry& getGeometry() const; 
    const Material& getMaterial() const;

private:
    const Geometry& geometry;
    const Material& material;
};