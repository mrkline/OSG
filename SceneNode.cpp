#include "SceneNode.hpp"

#include <algorithm>
#include <stack>
#include <queue>

#include "Exceptions.hpp"
#include "Renderable.hpp"

using namespace std;
using namespace Exceptions;

SceneNode::SceneNode(SceneNode* parent, const Transform& startingTransform,
                     int id, const string& name)
	: NamedClass(id, name), trans(startingTransform), parent(parent)
{
	if (parent != nullptr)
		parent->children.push_back(this);
}

SceneNode::~SceneNode()
{
	// Kill all children.
	deleteAllChildren();
}

void SceneNode::update()
{
	updateAbsoluteTransform();
	for (auto it = children.begin(); it != children.end(); ++it)
		(*it)->update();
}

void SceneNode::updateAbsoluteTransform()
{
	if (parent == nullptr)
		absTrans = trans;
	else
		absTrans = trans * parent->absTrans;
}


void SceneNode::addRenderable(Renderable* toAdd)
{
	if (toAdd == nullptr) {
		throw ArgumentNullException(
		    "You cannot add a null renderable object to a scene node.",
		    __FUNCTION__);
	}
	if (find(renderables.begin(), renderables.end(), toAdd)
	        != renderables.end()) {
		throw ArgumentException(
		    "You cannot add the same renderable object to a scene node twice.",
		    __FUNCTION__);
	}
	toAdd->setOwner(this);
	renderables.push_back(toAdd);
}

void SceneNode::removeRenderable(Renderable* toRemove)
{
	if (toRemove == nullptr) {
		throw ArgumentNullException(
		    "You cannot remove a null renderable object from a scene node.",
		    __FUNCTION__);
	}
	auto it = find(renderables.begin(), renderables.end(), toRemove);
	if (it == renderables.end()) {
		throw ArgumentException(
		    "The renderable object to be removed is not in this scene node.",
		    __FUNCTION__);
	}
	toRemove->setOwner(nullptr);
	renderables.erase(it);
}

bool SceneNode::hasChild(SceneNode* child) const
{
	return find(children.begin(), children.end(), child) != children.end();
}

bool SceneNode::hasChild(const string& childName) const
{
	for (auto it = children.begin(); it != children.end(); ++it) {
		if ((*it)->name == childName)
			return true;
	}
	return false;
}

bool SceneNode::hasChild(int childId) const
{
	for (auto it = children.begin(); it != children.end(); ++it) {
		if ((*it)->id == childId)
			return true;
	}
	return false;
}

bool SceneNode::hasAncestor(SceneNode* ancestor) const
{
	for (SceneNode* curr = parent; curr != nullptr; curr = curr->parent) {
		if (curr == ancestor)
			return true;
	}
	return false;
}

bool SceneNode::hasAncestor(const string& ancestorName) const
{
	for (SceneNode* curr = parent; curr != nullptr; curr = curr->parent) {
		if (curr->name == ancestorName)
			return true;
	}
	return false;
}

bool SceneNode::hasAncestor(int ancestorId) const
{
	for (SceneNode* curr = parent; curr != nullptr; curr = curr->parent) {
		if (curr->id == ancestorId)
			return true;
	}
	return false;
}

bool SceneNode::hasDescendant(SceneNode* descendant) const
{
	// Run a BFS
	queue<SceneNode*> q;

	for (auto it = children.begin(); it != children.end(); ++it)
		q.push(*it);

	while (!q.empty()) {
		SceneNode* curr = q.front();
		q.pop();

		if (curr == descendant) {
			return true;
		}
		else {
			const list<SceneNode*>& currChildren = curr->children;
			for (auto it = currChildren.begin(); it != currChildren.end(); ++it)
				q.push(*it);
		}
	}

	return false;
}

bool SceneNode::hasDescendant(const string& descendantName) const
{
	// Run a BFS
	queue<SceneNode*> q;

	for (auto it = children.begin(); it != children.end(); ++it)
		q.push(*it);

	while (!q.empty()) {
		SceneNode* curr = q.front();
		q.pop();

		if (curr->name == descendantName) {
			return true;
		}
		else {
			const list<SceneNode*>& currChildren = curr->children;
			for (auto it = currChildren.begin(); it != currChildren.end(); ++it)
				q.push(*it);
		}
	}

	return false;
}

bool SceneNode::hasDescendant(int descendantId) const
{
	// Run a BFS
	queue<SceneNode*> q;

	for (auto it = children.begin(); it != children.end(); ++it)
		q.push(*it);

	while (!q.empty()) {
		SceneNode* curr = q.front();
		q.pop();

		if (curr->id == descendantId) {
			return true;
		}
		else {
			const list<SceneNode*>& children = curr->children;
			for (auto it = children.begin(); it != children.end(); ++it)
				q.push(*it);
		}
	}

	return false;
}

void SceneNode::setParent(SceneNode* newParent)
{
	if (newParent == this)
		throw ArgumentException(
		    "A scene node cannot set itself as its parent.",
		    __FUNCTION__);

	removeFromParent();
	if (newParent != nullptr)
		newParent->addChild(this);
}

void SceneNode::removeFromParent()
{
	if (parent != nullptr)
		parent->removeChild(this);
}

void SceneNode::addChild(SceneNode* child)
{
	if (child == nullptr)
		throw ArgumentNullException("A scene node cannot add a null child.",
		                            __FUNCTION__);

	if (child == this)
		throw ArgumentException("A scene node cannot add itself as a child.",
		                        __FUNCTION__);

	// We're trying to add a duplicate child
	if (find(children.begin(), children.end(), child) != children.end()) {
		throw ArgumentException(
		    "A scene node cannot have duplicate children.",
		    __FUNCTION__);
	}

	child->removeFromParent();
	children.push_back(child);
	child->parent = this;
}

void SceneNode::removeChild(SceneNode* child)
{
	if (child == nullptr)
		throw ArgumentNullException("A scene node cannot remove a null child.",
		                            __FUNCTION__);

	auto it = find(children.begin(), children.end(), child);
	if (it != children.end()) {
		child->parent = nullptr;
		children.erase(it);
		return;
	}

	throw ArgumentException(
	    "A scene node could not find the child that was to be removed.",
	    __FUNCTION__);
}

void SceneNode::deleteAllChildren()
{
	for (auto it = children.begin(); it != children.end(); ++it)
		delete *it;

	children.clear();
}
