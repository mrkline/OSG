#include "StdAfx.hpp"
#include "Tree.hpp"

#include "Material.hpp"
#include "Transform.hpp"

using namespace std;

static shared_ptr<Material> trunkMat;
static shared_ptr<Material> branchesMat;

Tree::Tree()
{
	if (trunkMat) {
		// Initialize the materials
		trunkMat = make_shared<Material>();
		trunkMat->lighting = true;
		trunkMat->diffuse[0] = 0.542f;
		trunkMat->diffuse[1] = 0.271f;
		trunkMat->diffuse[2] = 0.075f;


		branchesMat = make_shared<Material>();
		branchesMat->lighting = true;
		branchesMat->diffuse[0] = 0.0f;
		branchesMat->diffuse[1] = 0.9f;
		branchesMat->diffuse[2] = 0.0f;
	}
}

void Tree::render()
{
	Transform rot;
	rot.rotateDegrees(Vector3(-90.0f, 0.0, 0.0f));
	glMultMatrixf(rot.getArray());
	setActiveMaterial(trunkMat);
	GLUquadric* q = gluNewQuadric();
	gluCylinder(q, 0.15f, 0.15f, 0.25f, 25, 1);
	setActiveMaterial(branchesMat);
	// Normals for the cap need to be flipped
	gluQuadricOrientation(q, GLU_INSIDE);
	glTranslatef(0.0f, 0.0f, 0.25f);
	gluDisk(q, 0.0f, 0.5f, 25, 1);
	gluQuadricOrientation(q, GLU_OUTSIDE);
	gluCylinder(q, 0.5f, 0.0f, 0.25f, 25, 1);
	glTranslatef(0.0f, 0.0f, 0.2f);
	gluQuadricOrientation(q, GLU_INSIDE);
	gluDisk(q, 0.0f, 0.4f, 25, 1);
	gluQuadricOrientation(q, GLU_OUTSIDE);
	gluCylinder(q, 0.4f, 0.0f, 0.25f, 25, 1);
	glTranslatef(0.0f, 0.0f, 0.2f);
	gluQuadricOrientation(q, GLU_INSIDE);
	gluDisk(q, 0.0f, 0.25f, 25, 1);
	gluQuadricOrientation(q, GLU_OUTSIDE);
	gluCylinder(q, 0.25f, 0.0f, 0.25f, 25, 1);
	gluDeleteQuadric(q);
}
