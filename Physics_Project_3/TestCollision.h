#pragma once

#include "Primitives.h"
#include "MeshInfo.h"
#include <glm/glm.hpp>

typedef glm::vec3 Point;

int TestAABBPlane(AABB b, Plane p);
int TestTriangleAABB(Point v0, Point v1, Point v2, AABB b);
bool SeperatingAxisTheoremTest(glm::vec3 axis, glm::vec3 boxExtents,
                               glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);
int Intersect(Point p0, Point p1, Point p2, AABB aabb);
bool CastRay(Ray ray, MeshInfo** gameObject, std::vector<MeshInfo*> listOfGameObjects);