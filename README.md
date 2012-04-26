## OSG

OSG - Orbital Strike Group

or,

OSG - OpenGL Scene Graph engine

Take your pick. OSG is a simple scene graph-based engine that arose out of
a project in a Computer Graphics class at the University of Wisconsin-Madison.
At present time, it is currently just a poor substitude for the SceneManager
from [Irrlicht](http://irrlicht.sourceforge.net/), with some minor tweaks.
Future plans are to turn it into a deferred shading engine for the next CG
project.

### Dependencies

Cg shader code, for obvious reasons, depends on the
[NVIDIA Cg libraries](http://developer.nvidia.com/cg-toolkit).

The Texture class uses SILLY, a part of the CEGUI library, as an image loader.
This allows textures to be loaded from PNG, JPEG, and TGA files.

GLEW is used to access Framebuffer functionality.

### License

(The zlib License)

Copyright (c) 2012 Matt Kline

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.
