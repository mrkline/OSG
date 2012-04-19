#include "StdAfx.hpp"
#include "Arrow.hpp"

#include "MkMath.hpp"
#include "Material.hpp"
#include "Vector3.hpp"

void Arrow::render()
{
	setActiveMaterial(mat);
	// If we don't have a material, we need the default one to determine
	// if we are to use wireframe or solid rendering
	GLUquadric* q = gluNewQuadric();
	if (getActiveMaterial()->wireframe)
		gluQuadricDrawStyle(q, GLU_LINE);
	else
		gluQuadricDrawStyle(q, GLU_FILL);
	glPushMatrix();
	// Draw the cylinder part of the arrow
	glTranslatef(0.0f, 0.0f, -0.5f);
	gluCylinder(q, 0.25f, 0.25f, 0.5f, 10, 1);
	// Normals for the cap need to be flipped
	gluQuadricOrientation(q, GLU_INSIDE);
	// Cap the back of the arrow cylinder
	gluDisk(q, 0.0f, 0.25f, 10, 1);
	glPopMatrix();
	// Cap the bottom of the cone
	gluDisk(q, 0.0f, 0.5f, 10, 1);
	// Normals for the cap need to be flipped
	gluQuadricOrientation(q, GLU_OUTSIDE);
	// Draw the cone part of the arrow
	gluCylinder(q, 0.5f, 0.0f, 0.5, 10, 1);
	gluDeleteQuadric(q);
}
