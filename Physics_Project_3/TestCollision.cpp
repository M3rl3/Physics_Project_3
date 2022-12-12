#include "TestCollision.h"

#include <glm/glm.hpp>

int TestAABBPlane(AABB b, Plane p)
{
    // These two lines not necessary with a (Center, extents) AABB representation
    Point c = (b.max + b.min) * 0.5f; // Compute AABB center
    Point e = b.max - c; // Compute positive extents
    // Compute the projection interval radius of b onto L(t) = b.c + t * p.n
    float r = e[0] * abs(p.n[0]) + e[1] * abs(p.n[1]) + e[2] * abs(p.n[2]);
    // Compute distance of box center from plane
    float s = glm::dot(p.n, c) - p.d;
    // Intersection occurs when distance s falls within [-r, +r] interval
    return abs(s) <= r;
}

int TestTriangleAABB(Point v0, Point v1, Point v2, AABB b)
{
	float p0, p1, p2, r;
	// compute box center and extents (if not already given in that format)
	Point c = (b.min + b.max) * 0.5f;
	float e0 = (b.max.x - b.min.x) * 0.5f;
	float e1 = (b.max.y - b.min.y) * 0.5f;
	float e2 = (b.max.z - b.min.z) * 0.5f;
	// Translate triangle as conceptually moving AABB to origin
	v0 = v0 - c;
	v1 = v1 - c;
	v2 = v2 - c;
	// Compute edge vectors for triangle
	glm::vec3 f0 = v1 - v0, f1 = v2 - v1, f2 = v0 - v2;
	// Test axes a00..a22 (category 3)
	// Test axis a00
	p0 = v0.z * v1.y - v0.y * v1.z;
	p2 = v2.z * (v1.y - v0.y) - v2.y * (v1.z - v0.z);
	r = e1 * abs(f0.z) + e2 * abs(f0.y);
	if (Max(-Max(p0, p2), Min(p0, p2)) > r)
		return 0; // axis is a separating axis
	// Repeat similar tests for remaining axes a01..a22,bnm
	
		// Test the three axes corresponding to the face normals of AABB b (category 1).
		// Exit if ...
		// ... [-e0, e0] and [min(v0.x, v1.x, v2.x), max(v0.x, v1.x, v2.x)] do not overlap
		if (Max(v0.x, v1.x, v2.x) < -e0 || Min(v0.x, v1.x, v2.x) > e0) return 0;
	// ... [-e1, e1] and [min(v0.y, v1.y, v2.y), max(v0.y, v1.y, v2.y)] do not overlap
	if (Max(v0.y, v1.y, v2.y) < -e1 || Min(v0.y, v1.y, v2.y) > e1) return 0;
	// ... [-e2, e2] and [min(v0.z, v1.z, v2.z), max(v0.z, v1.z, v2.z)] do not overlap
	if (Max(v0.z, v1.z, v2.z) < -e2 || Min(v0.z, v1.z, v2.z) > e2) return 0;
	// Test separating axis corresponding to triangle face normal (category 2)
	Plane p;
	p.n = glm::cross(f0, f1);
	p.d = glm::dot(p.n, v0);
	return TestAABBPlane(b, p);
}

bool SeperatingAxisTheoremTest(glm::vec3 axis, glm::vec3 boxExtents,
                               glm::vec3 v0, glm::vec3 v1, glm::vec3 v2) {

    glm::vec3 u0 = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 u1 = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 u2 = glm::vec3(0.0f, 0.0f, 1.0f);

    float p0 = glm::dot(v0, axis);
    float p1 = glm::dot(v1, axis);
    float p2 = glm::dot(v2, axis);

    float r = boxExtents.x * abs(glm::dot(u0, axis)) +
              boxExtents.y * abs(glm::dot(u1, axis)) +
              boxExtents.z * abs(glm::dot(u2, axis));

    // Min & Max functions that take 3 arguments
    if (Max(-Max(p0, p1, p2), Min(p0, p1, p2)) > r) {
        // This means BOTH of the points of the projected triangle
        // are outside the projected half-length of the AABB
        // Therefore the axis is seperating and we can exit
        return false;
    }
    return true;
}


int Intersect(Point p0, Point p1, Point p2, AABB aabb) {
    // Get the triangle points as vectors
    glm::vec3 v0 = p0;
    glm::vec3 v1 = p1;
    glm::vec3 v2 = p2;

    // Convert AABB to center-extents form
    Point c = (aabb.min + aabb.max) * 0.5f;
    float e0 = (aabb.max.x - aabb.min.x) * 0.5f;
    float e1 = (aabb.max.y - aabb.min.y) * 0.5f;
    float e2 = (aabb.max.z - aabb.min.z) * 0.5f;
    Point e = glm::vec3(e0, e1, e2);

    // Translate the triangle as conceptually moving the AABB to origin
    // This is the same as we did with the point in triangle test
    v0 -= c;
    v1 -= c;
    v2 -= c;

    // Compute the edge vectors of the triangle  (ABC)
    // That is, get the lines between the points as vectors
    glm::vec3 f0 = v1 - v0; // B - A
    glm::vec3 f1 = v2 - v1; // C - B
    glm::vec3 f2 = v0 - v2; // A - C

    // Compute the face normals of the AABB, because the AABB
    // is at center, and of course axis aligned, we know that 
    // it's normals are the X, Y and Z axis.
    glm::vec3 u0 = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 u1 = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 u2 = glm::vec3(0.0f, 0.0f, 1.0f);

    // There are a total of 13 axis to test!

    // We first test against 9 axis, these axis are given by
    // cross product combinations of the edges of the triangle
    // and the edges of the AABB. You need to get an axis testing
    // each of the 3 sides of the AABB against each of the 3 sides
    // of the triangle. The result is 9 axis of seperation

    // Compute the 9 axis
    glm::vec3 axis_u0_f0 = glm::cross(u0, f0);
    glm::vec3 axis_u0_f1 = glm::cross(u0, f1);
    glm::vec3 axis_u0_f2 = glm::cross(u0, f2);
    
    glm::vec3 axis_u1_f0 = glm::cross(u1, f0);
    glm::vec3 axis_u1_f1 = glm::cross(u1, f1);
    glm::vec3 axis_u1_f2 = glm::cross(u2, f2);
                                
    glm::vec3 axis_u2_f0 = glm::cross(u2, f0);
    glm::vec3 axis_u2_f1 = glm::cross(u2, f1);
    glm::vec3 axis_u2_f2 = glm::cross(u2, f2);

    // Repeat this test for the other 8 seperating axis
    // You may wish to make some kind of a helper function to keep
    // things readable
    // TODO: 8 more SAT tests
    // Project all 3 vertices of the triangle onto the Seperating axis
    if (SeperatingAxisTheoremTest(axis_u0_f0, e, v0, v1, v2) == false) return 0;
    if (SeperatingAxisTheoremTest(axis_u0_f1, e, v0, v1, v2) == false) return 0;
    if (SeperatingAxisTheoremTest(axis_u0_f2, e, v0, v1, v2) == false) return 0;
                                                                              
    if (SeperatingAxisTheoremTest(axis_u1_f0, e, v0, v1, v2) == false) return 0;
    if (SeperatingAxisTheoremTest(axis_u1_f1, e, v0, v1, v2) == false) return 0;
    if (SeperatingAxisTheoremTest(axis_u1_f2, e, v0, v1, v2) == false) return 0;
                                                                              
    if (SeperatingAxisTheoremTest(axis_u2_f0, e, v0, v1, v2) == false) return 0;
    if (SeperatingAxisTheoremTest(axis_u2_f1, e, v0, v1, v2) == false) return 0;
    if (SeperatingAxisTheoremTest(axis_u2_f2, e, v0, v1, v2) == false) return 0;
    

    // Next, we have 3 face normals from the AABB
    // for these tests we are conceptually checking if the bounding box
    // of the triangle intersects the bounding box of the AABB
    // that is to say, the seperating axis for all tests are axis aligned:
    // axis1: (1, 0, 0), axis2: (0, 1, 0), axis3 (0, 0, 1)
    // TODO: 3 SAT tests
    // Do the SAT given the 3 primary axis of the AABB
    // You already have vectors for this: u0, u1 & u2
    if (SeperatingAxisTheoremTest(u0, e, v0, v1, v2) == false) return 0;
    if (SeperatingAxisTheoremTest(u1, e, v0, v1, v2) == false) return 0;
    if (SeperatingAxisTheoremTest(u2, e, v0, v1, v2) == false) return 0;

    // Finally, we have one last axis to test, the face normal of the triangle
    // We can get the normal of the triangle by crossing the first two line segments
    // TODO: 1 SAT test
    glm::vec3 triangleNormal = glm::cross(f0, f1);
    if (SeperatingAxisTheoremTest(triangleNormal, e, v0, v1, v2) == false) return 0;
    // Passed testing for all 13 seperating axis that exist!

    Plane p;
    p.n = glm::cross(f0, f1);
    p.d = glm::dot(p.n, v0);
    return TestAABBPlane(aabb, p);
}

int TestRayAABB(const Ray& ray, AABB b)
{
    for (int i = 0; i < 1000; i++)
    {
        glm::vec3 direction = ray.origin + ray.direction * glm::vec3(i * 0.1);

        if (
            direction.x >= b.min[0] &&
            direction.x <= b.max[0] &&
            direction.y >= b.min[1] &&
            direction.y <= b.max[1] &&
            direction.z >= b.min[2] &&
            direction.z <= b.max[2]
            )
        {
            return 1;
        }
    }

    return 0;
}