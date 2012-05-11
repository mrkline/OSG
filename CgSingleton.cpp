#include "StdAfx.hpp"
#include "CgSingleton.hpp"

CgSingleton::CgSingleton()
	:vp(context, CG_GL_VERTEX), fp(context, CG_GL_FRAGMENT)
{
	printf("Cg vertex profile: %s\n", vp.getName());
	printf("Cg fragment profile: %s\n", fp.getName());
}