#include "Primitives.h"

#include "OpenGL.h"
#include "MeshInfo.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


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