#pragma once

class SceneNode;

//! This is an interface for a renderable object which can be attached to
//! scene nodes
class Renderable
{
public:
	//! Type of renderable
	enum RenderableType {
	    RT_CAMERA,
	    RT_LIGHT,
	    RT_NORMAL
	};

	Renderable() : owner(nullptr), shadow(true), shadowed(false) { }

	//! Used by the SceneManager to properly render cameras and lights
	virtual RenderableType getType() { return RT_NORMAL; }

	virtual void render() = 0;

	SceneNode* getOwner() { return owner; }

	//! Called by the owning scene node when this renderable object is attached
	//! to it
	void setOwner(SceneNode* newOwner);

protected:
	SceneNode* owner;
};
