#pragma once

#include <memory>

class Model;

//! A class for parsing .obj files
class OBJFile
{
public:
	OBJFile(const char* filename);
	const std::shared_ptr<Model>& getModel() { return model; }

private:
	std::shared_ptr<Model> model;
};

