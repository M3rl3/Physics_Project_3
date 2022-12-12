#pragma once

#include "MeshInfo.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class AABB {
public:
	AABB(float min[3], float max[3]);
	~AABB();

	glm::vec3 center;
	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 extents;

	float Min[3];
	float Max[3];
};

struct Plane {
	glm::vec3 n;
	glm::vec3 p;
	float d;
};

class Ray {
public:
	Ray(const glm::vec3& p, const glm::vec3& d);
	~Ray();

	glm::vec3 origin;
	glm::vec3 direction;
};

//void draw_bbox(MeshInfo* mesh, unsigned int shaderID, glm::mat4 meshTransform);

float Max(float v1, float v2, float v3);
float Max(float v1, float v2);
float Min(float v1, float v2);
float Min(float v1, float v2, float v3);