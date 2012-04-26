#pragma once

#include <memory>

class SceneNode;

//! This is an interface for a renderable object which can be attached to
//! scene nodes
class Renderable : public std::enable_shared_from_this<Renderable>
{
public:
	//! Type of renderable
	enum RenderableType {
	    RT_CAMERA, //!< A camera
	    RT_BACKGROUND, //!< A sky box or other background object
	    RT_LIGHT, //!< A light (currently only one is supported)
	    RT_NORMAL //!< An ordinary object
	};

	Renderable() : visible(true) { }

	//! Used by the SceneManager to properly render cameras and lights
	virtual RenderableType getType() { return RT_NORMAL; }

	virtual void render() = 0;

	bool isVisible() const {return visible; }

	//! Sets if this renderable will be drawn by the SceneManager
	void setVisible(bool v) { visible = v; }

	const std::weak_ptr<SceneNode>& getOwner() const { return owner; }

	//! Called by the owning scene node when this renderable object is attached
	//! or removed from it
	void setOwner(const std::weak_ptr<SceneNode>& newOwner)
	{ owner = newOwner; }

protected:
	std::weak_ptr<SceneNode> owner;
	bool visible;
};
