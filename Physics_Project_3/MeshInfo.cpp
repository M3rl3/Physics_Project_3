#include "MeshInfo.h"

MeshInfo::MeshInfo() {

	this->position = glm::vec3(0.f);
	this->rotation = glm::vec3(0.f);
	this->colour = glm::vec4(0.f, 0.f, 0.f, 1.f);
	this->RGBAColour = glm::vec4(0.f, 0.f, 0.f, 1.f);
	this->scale = 1.f;
	this->isWireframe = false;
	this->isVisible = true;
	this->useRGBAColour = false;
	this->drawBBox = false;
}

MeshInfo::~MeshInfo() {

}

// Make a copy of the vertices from the model file
void MeshInfo::CopyVertices(sModelDrawInfo model) {
	unsigned int numVertices = model.numberOfVertices;
	std::vector <glm::vec3> vertices(numVertices);

	for (int i = 0; i < numVertices; i++) {
		vertices[i].x = model.pVertices[i].x;
		vertices[i].y = model.pVertices[i].y;
		vertices[i].z = model.pVertices[i].z;
	}
	this->vertices = vertices;
}

void MeshInfo::CopyIndices(sModelDrawInfo model) {
	unsigned int numIndices = model.numberOfIndices;
	std::vector <unsigned int> indices(numIndices);

	for (int i = 0; i < numIndices; i++) {
		indices[i] = model.pIndices[i];
	}

	unsigned int numTriangles = model.numberOfTriangles;
	std::vector <glm::vec3> tempIndices(numTriangles);

	unsigned int index = 0;
	for (int i = 0; i < numTriangles; i++) {
		tempIndices[i].x = indices[index + 0];
		tempIndices[i].y = indices[index + 1];
		tempIndices[i].z = indices[index + 2];
		index += 3;
	}
	
	this->indices = tempIndices;
}