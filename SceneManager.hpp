#pragma once

#include <list>

class Camera;
class SceneNode;

class SceneManager
{
public:
	std::list<SceneNode*>& getSceneNodes() { return sceneNodes; }

	const std::list<SceneNode*>& getSceneNodes() const { return sceneNodes; }

	void renderScene() const;

	void setActiveCamera(Camera* cam) { activeCamera = cam; }

private:
	static void renderSceneNode(SceneNode* node, bool shadowPass);

	std::list<SceneNode*> sceneNodes;
	Camera* activeCamera;
};
