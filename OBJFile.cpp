#include "StdAfx.hpp"
#include "OBJFile.hpp"

#include <iostream>
#include <sstream>
#include <vector>

#include "Model.hpp"
#include "Vector3.hpp"

// for now, assumes a pretty valid obj file and only one object definition
// in the file. obviously this could use refining.

// TODO: texture coords, material library, material to use, face definition
// add face struct or class?

using namespace std;

OBJFile::OBJFile(const char* filename)
{
	if(filename != nullptr)
	{
		ifstream objfile;
		objfile.open(filename);
		if(objfile.fail())
		{
			model = nullptr;
		}
		else
		{
			vector<int> faces;
			model = make_shared<Model>();
			string key, temp;
			float tmpx, tmpy, tmpz, tmpu, tmpv, tmpw;
			while(!objfile.eof() && objfile >> key)
			{
				if(key == "#" || key == "s" || key == "g")
				{
					// ignoring comments and smooth shading and groups
					continue;
				}
				else if(key == "mtllib")
				{
					// material library file
				}
				else if(key == "o")
				{
					// object name
					objfile >> temp;
					model->setName(temp);
				}
				else if(key == "v")
				{
					// vertex
					objfile >> tmpx >> tmpy >> tmpz;
					model->addVertex(Vector3(tmpx, tmpy, tmpz));
				}
				else if(key == "vn")
				{
					// normals
					objfile >> tmpx >> tmpy >> tmpz;
					model->addNormal(Vector3(tmpx, tmpy, tmpz));
				}
				else if(key == "vt")
				{
					// texture coord
					string buff;
					getline(objfile, buff);
					stringstream line(buff);
					line >> tmpu >> tmpv;
					if(line.good())
					{
						line >> tmpw; // 3ds max exports 3d texture coords
					}
					model->addTextureCoord(Vector2(tmpu, tmpv));
				}
				else if(key == "usemtl")
				{
					// material to use
				}
				else if(key == "f")
				{
					// face definition
					string buff;
					getline(objfile, buff);
					// 3ds max pads the end of each face with a space
					if(buff.at(buff.size() - 1) == ' ')
						buff.erase(buff.size() - 1);
					stringstream line(buff);
					string verts[4];
					string v, vt, vn;
					int numverts = 3;

					line >> verts[0] >> verts[1]>> verts[2];
					// cruft - only accepting triangle meshes now
					if(line.good())
					{
						line >> verts[3];
						numverts = 4;
					}
					for(int i = 0; i < numverts; i++)
					{
						stringstream token(verts[i]);
						getline(token, v, '/');
						getline(token, vt, '/');
						token >> vn;
						faces.push_back(atoi(v.c_str())); 
						faces.push_back(atoi(vn.c_str()));
						faces.push_back(atoi(vt.c_str()));
					}
				}
				else
				{
					// unknown or unhandled keyword
					continue;
				}
			}
			// note multiple increment...
			for(auto i = faces.begin(); i != faces.end(); i+=3)
			{
				model->addTriangle(*i, *(i+1), *(i+2));
			}
			objfile.close();
		}
	}
}
