#pragma once

#include <list>
#include <memory>
#include <string>

#include "NamedClass.hpp"
#include "Transform.hpp"

class Renderable;

/*!
\brief Represents an entity in the game world.

A tree of SceneNodes is managed by the scene manager.
*/
class SceneNode : public NamedClass, public std::enable_shared_from_this<SceneNode>
{
public:

	/*!
	\brief Constructor.
	\param startingTransform The object's starting local transform
	\param id An ID that can be used to identify the object
	\param name A name that can be used to identify the object
	*/
	SceneNode(const Transform& startingTransform = Transform(),
	          int id = -1, const std::string& name = std::string());

	//! Updates the absolute transform of the object
	void update();

	//! Sets the object's transform to a new one
	void setTransform(const Transform& newTransform) { trans = newTransform; }

	//! Gets the object's transform
	Transform& getTransform() { return trans; }

	//! Gets the object's transform
	const Transform& getTransform() const { return trans; }

	/*!
	\brief Called by Update to update the absolute transform
	\see Update

	Only updates based on parent, does not recursively travel up the hierarchy.
	Because of this update should be called on object tree from root down
	*/
	void updateAbsoluteTransform();

	//! Gets the absolute transform
	const Transform& getAbsoluteTransform() const { return absTrans; }

	//! Adds a renderable object to this scene node
	void addRenderable(const std::shared_ptr<Renderable>& toAdd);

	//! Removes a renderable object from this scene node
	void removeRenderable(const std::shared_ptr<Renderable>& toRemove);

	//! Gets the list of renderable objects attached to this scene node
	const std::list<std::shared_ptr<Renderable>>& getRenderables() const { return renderables; }

	// Functions to manipulate the object tree

	//! Tests if the object has children or not
	bool hasChildren() const { return !children.empty(); }

	/*!
	\brief Tests if this object has a given child
	\param child The object to search for in this object's children
	\returns true if this object has the specified child
	*/
	bool hasChild(const std::shared_ptr<SceneNode>& child) const;

	/*!
	\brief Tests if this object has a given child
	\param childName The name of the object to search for in
	                 this object's children
	\returns true if this object has a child with the given name
	*/
	bool hasChild(const std::string& childName) const;

	/*!
	\brief Tests if this object has a given child
	\param childId The ID of the object to search for in this object's children
	\returns true if this object has a child with the given ID
	*/
	bool hasChild(int childId) const;

	/*!
	\brief Tests if this object has a given ancestor
	\param ancestor The object to search for in this object's ancestry
	\returns true if this object has the specified ancestor
	*/
	bool hasAncestor(const std::shared_ptr<SceneNode>& ancestor) const;

	/*!
	\brief Tests if this object has a given ancestor
	\param ancestorName The name of the object to search for in
	                    this object's ancestry
	\returns true if this object has an ancestor with the given name
	*/
	bool hasAncestor(const std::string& ancestorName) const;

	/*!
	\brief Tests if this object has a given ancestor
	\param ancestorId The ID of the object to search for
	                  in this object's ancestry
	\returns true if this object has an ancestor with the given ID
	*/
	bool hasAncestor(int ancestorId) const;


	/*!
	\brief Tests if this object has a given descendant
	\param descendant The object to search for in this object's descendance
	\returns true if this object has the given descendant

	Performs a BFS for the descendant
	*/
	bool hasDescendant(const std::shared_ptr<SceneNode>& descendant) const;

	/*!
	\brief Tests if this object has a given descendant
	\param descendantName The name of the object to search for in
	                      this object's descendance
	\returns true if this object has an descendant with the given name
	*/
	bool hasDescendant(const std::string& descendantName) const;

	/*!
	\brief Tests if this object has a given descendant
	\param descendantId The ID of the object to search for in this object's descendance
	\returns true if this object has an descendant with the given ID
	*/
	bool hasDescendant(int descendantId) const;

	/*!
	\brief Sets the object's parent
	\param newParent A pointer to the new parent, or null if no parent is desired

	This method will remove the component from its current parent (if it exists) and
	set it to the new one.
	*/
	void setParent(const std::weak_ptr<SceneNode>& newParent);

	//! Gets the object's parent
	const std::weak_ptr<SceneNode>& getParent() const { return parent; }

	//! Gets a list of the node's children
	std::list<std::shared_ptr<SceneNode>>& getChildren() { return children; }

	//! Gets a list of the node's children
	const std::list<std::shared_ptr<SceneNode>>& getChildren() const
	{ return children; }

	//! Removes this object from its parent
	void removeFromParent();

	/*!
	\brief Add a child object
	\param child Child object to add

	This method removes the child from its current parent, sets this component
	as its parent, and adds the new child to this component's list of children.
	*/
	void addChild(const std::shared_ptr<SceneNode>& child);

	/*!
	\brief Remove a child object
	\param child Child object to remove
	*/
	void removeChild(const std::shared_ptr<SceneNode>& child);

protected:
	Transform trans; //!< The transform for the scene node
	Transform absTrans; //!< The cumulative absolute transform

	//! Node's parent, or null if it has none
	std::weak_ptr<SceneNode> parent;
	//! Linked list of children of this node
	std::list<std::shared_ptr<SceneNode>> children;
	//! Linked list of renderable objects attached to this node
	std::list<std::shared_ptr<Renderable>> renderables;
};
