
#pragma once
#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include "W_Common.h"
#include "Camera.h"
#include "QuadTree.h"
#include "AABB.h"
#include <iostream>
#include <list>
class Scene
{
	private:
		static Scene* mScene;
		bool mClicked = false;
		bool mDrawTree = true;
		Camera* mCamera;
		QuadTree* tree;
		Scene();
		


	public:
		static Scene* Instance();
		void addNode(Node* node);
		void Init();
		void setCamera(Camera* camera);
		Camera* getCamera();

		void Update(float deltaT);

		std::list<Node*> mTopNodes;
};
