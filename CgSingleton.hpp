#pragma once

#include <map>
#include <memory>
#include <string>

#include "CgContext.hpp"
#include "CgProfile.hpp"

struct ShaderSet;

//! A simple singleton class to provide global access to our shader context and
//! profiles
class CgSingleton
{
public:
	typedef std::map<std::string, std::shared_ptr<ShaderSet>> ShaderSetMap;

	static CgSingleton& getSingleton()
	{
		// Use a pointer to circumvent RAII - there's no need to tear
		// this down as the program exits - just let the program exit
		static CgSingleton* instance = new CgSingleton;
		return *instance;
	}

	CgContext& getContext() { return context; }

	CgProfile& getVertexProfile() { return vp; }

	CgProfile& getFragmentProfile() { return fp; }

	ShaderSetMap shaderSetMap;

private:
	CgSingleton();

	CgContext context;
	CgProfile vp;
	CgProfile  fp;
};
