#pragma once

#include <list>
#include <string>
#include <memory>

#include "NamedClass.hpp"
#include "Transform.hpp"

class Renderable;

/*!
\brief Represents an entity in the game world.

A tree of SceneNodes is managed by the scene manager.
*/
class SceneNode : public NamedClass
{
public:

	/*!
	\brief Constructor.
	\param parent The parent of the object, or null if it has none
	\param startingTransform The object's starting local transform
	\param id An ID that can be used to identify the object
	\param name A name that can be used to identify the object
	*/
	SceneNode(SceneNode* parent = nullptr,
	          const Transform& startingTransform = Transform(),
	          int id = -1, const std::string& name = std::string());

	//! Deconstructor. Deletes all children
	virtual ~SceneNode();

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

	/*!
	\brief Adds a renderable object to this scene node

	Adding a renderable object transfers its ownership to this scene node.
	It will be deleteed on this node's destruction.
	*/
	void addRenderable(Renderable* toAdd);

	/*!
	\brief Removes a renderable object from this scene node

	Removing the object transfers ownership back to the client's code.
	The client code is responsible for deleting the object after this is called.
	*/
	void removeRenderable(Renderable* toRemove);

	//! Gets the list of renderable objects attached to this scene node
	const std::list<Renderable*>& getRenderables() const { return renderables; }

	// Functions to manipulate the object tree

	//! Tests if the object has children or not
	bool hasChildren() const { return !children.empty(); }

	/*!
	\brief Tests if this object has a given child
	\param child The object to search for in this object's children
	\returns true if this object has the specified child
	*/
	bool hasChild(SceneNode* child) const;

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
	bool hasAncestor(SceneNode* ancestor) const;

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
	bool hasDescendant(SceneNode* descendant) const;

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
	void setParent(SceneNode* newParent);

	//! Gets the object's parent
	SceneNode* getParent() const { return parent; }

	//! Gets a list of the node's children
	std::list<SceneNode*>& getChildren() { return children; }

	//! Gets a list of the node's children
	const std::list<SceneNode*>& getChildren() const { return children; }

	//! Removes this object from its parent
	void removeFromParent();

	/*!
	\brief Add a child object
	\param child Child object to add

	This method removes the child from its current parent, sets this component
	as its parent, and adds the new child to this component's list of children.
	Adding a child transfers ownership of the child to this scene node.
	All children will be deleted on this object's destruction.
	*/
	void addChild(SceneNode* child);

	/*!
	\brief Remove a child object
	\param child Child object to remove

	Removing the child transfers ownership back to the client's code.
	The client code is responsible for deleting the child after this is called.
	*/
	void removeChild(SceneNode* child);

	//! Delete all children
	void deleteAllChildren();

protected:
	Transform trans; //!< The transform for the scene node
	Transform absTrans; //!< The cumulative absolute transform

	//! Node's parent, or null if it has none
	SceneNode* parent;
	//! Linked list of children of this node
	std::list<SceneNode*> children;
	//! Linked list of renderable objects attached to this node
	std::list<Renderable*> renderables;
};
