#include "object.hpp"

Object::Object(const Geometry& geometry, const Material& material)
: geometry(geometry), material(material)
{

}

const Geometry& Object::getGeometry() const { return this->geometry; }
const Material& Object::getMaterial() const { return this->material; }