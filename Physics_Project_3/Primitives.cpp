#include "Primitives.h"

#include "OpenGL.h"
#include "MeshInfo.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

AABB::AABB(float min[3], float max[3]) {
	memcpy(&(Min[0]), &(min[0]), 3 * sizeof(float));
	memcpy(&(Max[0]), &(max[0]), 3 * sizeof(float));
}

AABB::~AABB() {

}

Ray::Ray(const glm::vec3& p, const glm::vec3& d)
	: origin(p), direction(d) {

	float m =
		sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
	direction.x /= m;
	direction.y /= m;
	direction.z /= m;
}

Ray::~Ray() {

}

float Max(float v1, float v2, float v3) {
	if (v1 > v2 && v1 > v3) {
		return v1;
	}
	else if (v2 > v1 && v2 > v3) {
		return v2;
	}
	else if (v3 > v1 && v3 > v2) {
		return v3;
	}
}

float Max(float v1, float v2) {
	if (v1 > v2) {
		return v1;
	}
	else if (v2 > v1) {
		return v2;
	}
}

float Min(float v1, float v2) {
	if (v1 < v2) {
		return v1;
	}
	else if (v2 < v1) {
		return v2;
	}
}

float Min(float v1, float v2, float v3) {
	if (v1 < v2 && v1 < v3) {
		return v1;
	}
	else if (v2 < v1 && v2 < v3) {
		return v2;
	}
	else if (v3 < v1 && v3 < v2) {
		return v3;
	}
}