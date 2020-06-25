#pragma once

#include "Node.h"
#include "BoundingSphere.h"
#include "AABB.h"
#include <list>


class QuadTree
{
	
	public:
		QuadTree(AABB* bound);
		bool insert(Node* node);
		void divide();
		std::list<Node*> range(AABB* range);
		std::list<AABB*> frustemCheck();
		void draw(const glm::mat4& mView, const glm::mat4& mProj);

	private:

		const int capacity = 2;

		AABB* mBound;
		std::list<Node*> mPoints;
		

		
		QuadTree* northWest = NULL;
		QuadTree* northEast = NULL;
		QuadTree* southWest = NULL;
		QuadTree* southEast = NULL;
		
};
