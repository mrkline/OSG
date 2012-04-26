#include "StdAfx.hpp"
#include "SceneManager.hpp"

#include <deque>

#include "SceneNode.hpp"
#include "Material.hpp"
#include "Camera.hpp"

using namespace std;

void SceneManager::renderScene() const
{
	// There's no point in drawing a scene if we don't have an active camera
	if (!activeCamera)
		return;

	// List of renderables to render
	list<Renderable*> lights;
	list<Renderable*> bg;
	list<Renderable*> normals;

	// Update the transforms of all scene nodes via bfs and add their
	// renderables to the various queues
	deque<SceneNode*> q;
	for (auto it = sceneNodes.begin(); it != sceneNodes.end(); ++it)
		q.push_back(it->get());

	while (!q.empty()) {
		auto curr = q.front();
		q.pop_front();

		curr->updateAbsoluteTransform();
		const auto& renderables = curr->getRenderables();
		for (auto it = renderables.begin(); it != renderables.end(); ++it) {
			switch ((*it)->getType()) {
			case Renderable::RT_LIGHT:
				lights.push_back(it->get());
				break;

			case Renderable::RT_BACKGROUND:
				bg.push_back(it->get());
				break;

			case Renderable::RT_NORMAL:
				normals.push_back(it->get());
				break;
			}
		}

		// Enqueue all the node's children
		const auto& currChildren = curr->getChildren();
		for (auto it = currChildren.begin(); it != currChildren.end(); ++it)
			q.push_back(it->get());
	}

	// Draw our camera first
	activeCamera->render();

	// Draw all lights next
	for (auto it = lights.begin(); it != lights.end(); ++it)
		if ((*it)->isVisible()) (*it)->render();

	// Draw all background objects
	for (auto it = bg.begin(); it != bg.end(); ++it) {
		if ((*it)->isVisible()) {
			glPushMatrix();
			glMultMatrixf((*it)->getOwner().lock()->
						  getAbsoluteTransform().getArray());
			(*it)->render();
			glPopMatrix();
		}
	}

	// Clear the depth buffer, allowing normal objects to always be drawn
	// over the background ones
	glClear(GL_DEPTH_BUFFER_BIT);

	// Draw all normal objects
	for (auto it = normals.begin(); it != normals.end(); ++it) {
		if ((*it)->isVisible()) {
			glPushMatrix();
			glMultMatrixf((*it)->getOwner().lock()->
						  getAbsoluteTransform().getArray());
			(*it)->render();
			glPopMatrix();
		}
	}
}
