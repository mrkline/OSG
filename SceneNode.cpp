#include "SceneNode.hpp"

#include <algorithm>
#include <stack>
#include <queue>

#include "Exceptions.hpp"
#include "Renderable.hpp"

using namespace std;
using namespace Exceptions;

SceneNode::SceneNode(const Transform& startingTransform,
                     int id, const string& name)
	: NamedClass(id, name), trans(startingTransform), parent(parent)
{
}

void SceneNode::update()
{
	updateAbsoluteTransform();
	for (auto it = children.begin(); it != children.end(); ++it)
		(*it)->update();
}

void SceneNode::updateAbsoluteTransform()
{
	auto p = parent.lock();
	if (!p)
		absTrans = trans;
	else
		absTrans = p->absTrans * trans;
}


void SceneNode::addRenderable(const shared_ptr<Renderable>& toAdd)
{
	if (find(renderables.begin(), renderables.end(), toAdd)
	        != renderables.end()) {
		throw ArgumentException(
		    "You cannot add the same renderable object to a scene node twice.",
		    __FUNCTION__);
	}
	toAdd->setOwner(shared_from_this());
	renderables.push_back(toAdd);
}

void SceneNode::removeRenderable(const std::shared_ptr<Renderable>& toRemove)
{
	auto it = find(renderables.begin(), renderables.end(), toRemove);
	if (it == renderables.end()) {
		throw ArgumentException(
		    "The renderable object to be removed is not in this scene node.",
		    __FUNCTION__);
	}
	toRemove->setOwner(weak_ptr<SceneNode>());
	renderables.erase(it);
}

bool SceneNode::hasChild(const shared_ptr<SceneNode>& child) const
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

bool SceneNode::hasAncestor(const shared_ptr<SceneNode>& ancestor) const
{
	for (auto curr = parent.lock(); curr; curr = curr->parent.lock()) {
		if (curr == ancestor)
			return true;
	}
	return false;
}

bool SceneNode::hasAncestor(const string& ancestorName) const
{
	for (auto curr = parent.lock(); curr; curr = curr->parent.lock()) {
		if (curr->name == ancestorName)
			return true;
	}
	return false;
}

bool SceneNode::hasAncestor(int ancestorId) const
{
	for (auto curr = parent.lock(); curr; curr = curr->parent.lock()) {
		if (curr->id == ancestorId)
			return true;
	}
	return false;
}

bool SceneNode::hasDescendant(const shared_ptr<SceneNode>& descendant) const
{
	// Run a BFS
	queue<SceneNode*> q;

	for (auto it = children.begin(); it != children.end(); ++it)
		q.push(it->get());

	while (!q.empty()) {
		auto curr = q.front();
		q.pop();

		if (curr == descendant.get()) {
			return true;
		}
		else {
			const auto& currChildren = curr->children;
			for (auto it = currChildren.begin(); it != currChildren.end(); ++it)
				q.push(it->get());
		}
	}

	return false;
}

bool SceneNode::hasDescendant(const string& descendantName) const
{
	// Run a BFS
	queue<SceneNode*> q;

	for (auto it = children.begin(); it != children.end(); ++it)
		q.push(it->get());

	while (!q.empty()) {
		auto curr = q.front();
		q.pop();

		if (curr->name == descendantName) {
			return true;
		}
		else {
			const auto& currChildren = curr->children;
			for (auto it = currChildren.begin(); it != currChildren.end(); ++it)
				q.push(it->get());
		}
	}

	return false;
}

bool SceneNode::hasDescendant(int descendantId) const
{
	// Run a BFS
	queue<SceneNode*> q;

	for (auto it = children.begin(); it != children.end(); ++it)
		q.push(it->get());

	while (!q.empty()) {
		auto curr = q.front();
		q.pop();

		if (curr->id == descendantId) {
			return true;
		}
		else {
			const auto& children = curr->children;
			for (auto it = children.begin(); it != children.end(); ++it)
				q.push(it->get());
		}
	}

	return false;
}

void SceneNode::setParent(const weak_ptr<SceneNode>& newParent)
{
	removeFromParent();
	auto np = newParent.lock();
	if (np)
		np->addChild(shared_from_this());
}

void SceneNode::removeFromParent()
{
	auto p = parent.lock();
	if (p)
		p->removeChild(shared_from_this());
}

void SceneNode::addChild(const shared_ptr<SceneNode>& child)
{
	if (child.get() == this)
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
	child->parent = shared_from_this();
}

void SceneNode::removeChild(const shared_ptr<SceneNode>& child)
{
	auto it = find(children.begin(), children.end(), child);
	if (it != children.end()) {
		child->parent.reset();
		children.erase(it);
		return;
	}

	throw ArgumentException(
	    "A scene node could not find the child that was to be removed.",
	    __FUNCTION__);
}
