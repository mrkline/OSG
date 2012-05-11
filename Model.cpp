#include "StdAfx.hpp"
#include "Model.hpp"

#include "Transform.hpp"

/* 
collection of vertices, normals, faces
handle to a material (which has a handle to a texture)
*/

Model::Model()
{
	createdVBOs = false;
	this->objMaterial = getDefaultMaterial();
}

void Model::addTriangle(int vertidx, int normidx, int texidx){
	// get the vectors pointed to by the indicies passed in
	Vector3 v = vertices[vertidx-1];
	Vector3 n = normals[normidx-1];
	Vector2	t = texcoords[texidx-1];
	// and push the pieces onto the appropriate vectors
	tvert.push_back(v.X);
	tvert.push_back(v.Y);
	tvert.push_back(v.Z);
	tnorm.push_back(n.X);
	tnorm.push_back(n.Y);
	tnorm.push_back(n.Z);
	ttext.push_back(t.X);
	ttext.push_back(t.Y);
}

void Model::render()
{	
	setActiveMaterial(objMaterial);
	
	if(!createdVBOs)
	{
		// initialize the VBOs:
		// create the buffer
		glGenBuffers(1, &vertVboId);
		glGenBuffers(1, &normVboId);
		glGenBuffers(1, &texcoordVboId);
		// bind GL to it
		glBindBuffer(GL_ARRAY_BUFFER, vertVboId);
		// actually copy the data over
		glBufferData(GL_ARRAY_BUFFER, tvert.size() * sizeof(GLfloat), &tvert[0], 
			GL_STATIC_DRAW);
		// repeat for normals and texture coordinates:
		glBindBuffer(GL_ARRAY_BUFFER, normVboId);
		glBufferData(GL_ARRAY_BUFFER, tnorm.size() * sizeof(GLfloat), &tnorm[0], 
			GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, texcoordVboId);
		glBufferData(GL_ARRAY_BUFFER, ttext.size() * sizeof(GLfloat),
			&ttext[0], GL_STATIC_DRAW);
		// clear the binding (ugh, this was hard fought)
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		createdVBOs = true;
	}
			
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// rebind to the buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertVboId);	
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	// rinse and repeat for the normal  and texture coord data
	glBindBuffer(GL_ARRAY_BUFFER, normVboId);	
	glNormalPointer(GL_FLOAT, 0, NULL);
	
	glBindBuffer(GL_ARRAY_BUFFER, texcoordVboId);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);


	// draw the polygon
	glDrawArrays(GL_TRIANGLES, 0, tvert.size() / 3);
	
	//clean up
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

Model::~Model(void)
{
	// give back the vram
	glDeleteBuffers(1, &vertVboId);
	glDeleteBuffers(1, &normVboId);
	glDeleteBuffers(1, &texcoordVboId);
}

