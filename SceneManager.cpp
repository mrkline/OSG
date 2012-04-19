#include "SceneManager.hpp"

#include <Windows.h>
#include <GL/gl.h>
#include <deque>

#include "SceneNode.hpp"
#include "Material.hpp"
#include "Camera.hpp"

using namespace std;

void SceneManager::renderScene() const
{
	// There's no point in drawing a scene if we don't have an active camera
	if (activeCamera == nullptr)
		return;

	// List of renderables to render
	list<Renderable*> lights;
	list<Renderable*> bg;
	list<Renderable*> normals;

	// Update the transforms of all scene nodes via bfs and add their
	// renderables to the various queues
	deque<SceneNode*> q;
	for (auto it = sceneNodes.begin(); it != sceneNodes.end(); ++it)
		q.push_back(*it);

	while (!q.empty()) {
		SceneNode* curr = q.front();
		q.pop_front();

		curr->updateAbsoluteTransform();
		const list<Renderable*>& renderables = curr->getRenderables();
		for (auto it = renderables.begin(); it != renderables.end(); ++it) {
			switch ((*it)->getType()) {
			case Renderable::RT_LIGHT:
				lights.push_back(*it);
				break;

			case Renderable::RT_BACKGROUND:
				bg.push_back(*it);
				break;

			case Renderable::RT_NORMAL:
				normals.push_back(*it);
				break;
			}
		}

		// Enqueue all the node's children
		const list<SceneNode*>& currChildren = curr->getChildren();
		for (auto it = currChildren.begin(); it != currChildren.end(); ++it)
			q.push_back(*it);
	}

	// Draw our camera first
	activeCamera->render();

	// Draw all lights next
	for (auto it = lights.begin(); it != lights.end(); ++it)
		(*it)->render();

	// Draw all background objects
	for (auto it = bg.begin(); it != bg.end(); ++it) {
		glPushMatrix();
		glMultMatrixf((*it)->getOwner()->getAbsoluteTransform().getArray());
		(*it)->render();
		glPopMatrix();
	}

	// Clear the depth buffer, allowing normal objects to always be drawn
	// over the background ones
	glClear(GL_DEPTH_BUFFER_BIT);

	// Draw all normal objects
	for (auto it = normals.begin(); it != normals.end(); ++it) {
		glPushMatrix();
		glMultMatrixf((*it)->getOwner()->getAbsoluteTransform().getArray());
		(*it)->render();
		glPopMatrix();
	}
}
