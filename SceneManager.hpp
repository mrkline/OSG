#pragma once

#include <list>
#include <memory>

class Camera;
class SceneNode;

class SceneManager
{
public:
	std::list<std::shared_ptr<SceneNode>>& getSceneNodes() { return sceneNodes; }

	const std::list<std::shared_ptr<SceneNode>>& getSceneNodes() const { return sceneNodes; }

	void renderScene() const;

	void setActiveCamera(std::shared_ptr<Camera>& cam) { activeCamera = cam; }

private:
	std::list<std::shared_ptr<SceneNode>> sceneNodes;
	std::shared_ptr<Camera> activeCamera;
};
