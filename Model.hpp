#pragma once

#include <string>
#include <vector>

#include "Material.hpp"
#include "Renderable.hpp"
#include "Vector3.hpp"

//! An object created from an OBJ file (likely exported from Blender) that 
//	knows how to draw itself.
class Model: public Renderable
{
private:
	// 3 floats per vertex, 3 floats per normal, 2 floats per texture coord
	static const int vertsize = 8;
	std::string objName;
	std::vector<Vector3> vertices;
	std::vector<Vector3> normals;
	std::vector<Vector2> texcoords;
	std::vector<float> tvert;
	std::vector<float> tnorm;
	std::vector<float> ttext;
	std::shared_ptr<Material> objMaterial;
	GLuint vertVboId;
	GLuint normVboId;
	GLuint texcoordVboId;
	bool createdVBOs;
	int numcoords;

public:
	Model();
	void render();
	void setName(std::string name){objName = name;};
	std::string getName(){return this->objName;};
	void addVertex(Vector3 vertex){vertices.push_back(vertex);};
	void addTextureCoord(Vector2 texcoord){texcoords.push_back(texcoord);};
	void addNormal(Vector3 normal){normals.push_back(normal);};
	void addTriangle(int vertidx, int normidx, int texidx);
	void setMaterial(std::shared_ptr<Material> material){objMaterial = material;};
	~Model(void);


};

