#pragma once

#include <functional>
#include <memory>

class CgProgram;
struct Material;


//! A shader set is made up of a vertex shader, a fragment shader, and their
//! needed callback
struct ShaderSet
{
	std::shared_ptr<CgProgram> vertexShader;
	std::shared_ptr<CgProgram> fragmentShader;
	std::function<void(const std::shared_ptr<Material>&)> callback;
};
