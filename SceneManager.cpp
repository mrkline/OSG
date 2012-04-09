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

	// List of lights to render (at the time being we only support one)
	list<Renderable*> lights;
	list<SceneNode*> nodesToRender;

	// Update the transforms of all scene nodes via bfs
	deque<SceneNode*> q;
	for (auto it = sceneNodes.begin(); it != sceneNodes.end(); ++it)
		q.push_back(*it);

	while (!q.empty()) {
		SceneNode* curr = q.front();
		q.pop_front();

		nodesToRender.push_back(curr);
		curr->updateAbsoluteTransform();
		const list<Renderable*>& renderables = curr->getRenderables();
		for (auto it = renderables.begin(); it != renderables.end(); ++it) {
			if ((*it)->getType() == Renderable::RT_LIGHT)
				lights.push_back(*it);
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

	// Draw all scene nodes
	for (auto it = nodesToRender.begin(); it != nodesToRender.end(); ++it)
		renderSceneNode(*it, false);
}

void SceneManager::renderSceneNode(SceneNode* node, bool shadowPass)
{
	// Save the camera's transform for rendering other nodes
	glPushMatrix();

	// Apply this node's transform
	glMultMatrixf(node->getAbsoluteTransform().getArray());

	// Draw all renderables
	const list<Renderable*>& renderables = node->getRenderables();
	for (auto it = renderables.begin(); it != renderables.end(); ++it) {
		// We already rendered the camera and lights
		if ((*it)->getType() == Renderable::RT_NORMAL)
			(*it)->render();
	}

	// Revert to the camera's transform, undoing this node's transform
	glPopMatrix();
}
