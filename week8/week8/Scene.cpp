
#include "Scene.h"
#include "Cube.h"
Scene* Scene::mScene = NULL;
/*
private constructor
*/
Scene::Scene()
{
}
/*
get the singleton Instance if there is no instance of Scene, create it
*/
Scene* Scene::Instance()
{
	if (mScene)
	{
		return mScene;
	}

	mScene = new Scene();
	return mScene;
}
/*
create our quad tree, add cube nodes to it at random positions
*/
void Scene::Init()
{
	AABB* root = new AABB(-30.0f, 30.0f, -30.0f, 30.0f);
	tree = new QuadTree(root);
	
	for (int i = 0; i < 20; i++)
	{
		int posx = rand() % 41 - 20;
		int posZ = rand() % 41 - 20;
		float scaleX = rand() % 5 + 1;
		float scaleY = rand() % 5 + 1;
		float scaleZ = rand() % 5 + 1;
		glm::vec3 scale = glm::vec3(scaleX, scaleY, scaleZ);
		Node* node = new Cube("cube");
		node->setTranslate(glm::vec3(posx, 0.0f, posZ));
		node->setScale(scale);
		mScene->addNode(node);
		tree->insert(node);
	}
	
}
/*
add a node so the scene could know how many nodes it has, not used
*/
void Scene::addNode(Node* node)
{
	mTopNodes.push_back(node);
}

/*
set a camera for the scene
*/
void Scene::setCamera(Camera* camera) 
{
	mCamera = camera;
	
}
/*
get the camera set in this scene
*/
Camera* Scene::getCamera()
{
	return mCamera;
}

/*
Render the scene
*/
void Scene::Update(float deltaT)
{
	//update the camera position and frustum
	if (mCamera)
	{
		mCamera->update(0.0f);
		mCamera->frustum();
	}
	
	//get all the AABBs that are located in the leafs of the quad tree
	std::list<AABB*> leafAABB = tree->frustemCheck();
	for each (AABB* aa in leafAABB)
	{
		//check if the leaf AABB is inside the camera frustum
		std::string result = mCamera->AABBCheck(aa);
		if (result == "inside")
		{
			//get all the nodes that are inside this AABB
			std::list<Node*> leafNodes = tree->range(aa);
			for each (Node * node in leafNodes)
			{
				node->Render(mCamera->getViewMatrix(), mCamera->getProjectionMatrix());
			}
		}
		else
		{
			//std::cout << "cull";
		}
	}
	// draw the quad tree
	if (glfwGetKey('T') == GLFW_PRESS && !mClicked)
	{
		mClicked = true;
		if (mDrawTree == false)
		{
			mDrawTree = true;
		}
		else
		{
			mDrawTree = false;
		}
		
	}
	if (glfwGetKey('C') != GLFW_PRESS)
	{
		mClicked = false;
	}
	if (mDrawTree)
	{
		tree->draw(mCamera->getViewMatrix(), mCamera->getProjectionMatrix());
	}
	
}