#include "QuadTree.h"

static std::list<AABB*> mQuad;
/*
set the quad tree with its area bounds
*/
QuadTree::QuadTree(AABB* bound) :mBound(bound)
{

}

/*
insert a node into the tree
*/
bool QuadTree::insert(Node* node)
{
	//if the quad tree area dosent intersect with the node dont insert it
	if (!mBound->intersect(node->getSphere()))
	{
		return false;
	}
	//check to see if this leaf has roo,
	if (mPoints.size() < 2 && northWest == NULL)
	{
		mPoints.push_back(node);
		return true;
	}
	// if there is no room and no children we have to divide the tree to create room
	if (northWest == NULL)
	{
		divide();
	}
	//if there are children insert the node into one of them recursivly
	if (northWest->insert(node)) return true;
	if (northEast->insert(node)) return true;
	if (southWest->insert(node)) return true;
	if (southEast->insert(node)) return true;
	

	return false;
}

/*
given an area, return all the Nodes that exist in its bounds
*/
std::list<Node*> QuadTree::range(AABB* range)
{
	std::list<Node*> pointsInRange;
	std::list<Node*> temp;
	//add all the nodes at this level
	for each (Node* node in mPoints)
	{
		pointsInRange.push_back(node);
	}
	// if there are no children return all the nodes
	if (northWest == NULL)
	{
		return pointsInRange;
	}

	// Otherwise, add the nodes from the children
	temp = northWest->range(range);
	pointsInRange.insert(pointsInRange.end(), temp.begin(), temp.end());
	temp = northEast->range(range);
	pointsInRange.insert(pointsInRange.end(), temp.begin(), temp.end());
	temp = southWest->range(range);
	pointsInRange.insert(pointsInRange.end(), temp.begin(), temp.end());
	temp = southEast->range(range);
	pointsInRange.insert(pointsInRange.end(), temp.begin(), temp.end());
	
	return pointsInRange;
}

/*
create 4 sub Squares as children to this level
*/
void QuadTree::divide()
{
	float xMin = mBound->getXmin();
	float xMax = mBound->getXmax();
	float zMin = mBound->getZmin();
	float zMax = mBound->getZmax();

	//find the center of the AABB at this level
	float xMid = (xMin + xMax) / 2;
	float zMid = (zMin + zMax) / 2;

	//create 4 children that seperate this AABB
	AABB* boundNorthWest = new AABB(xMin, xMid, zMin, zMid);
	northWest = new QuadTree(boundNorthWest);
	
	AABB* boundNorthEast = new AABB(xMid, xMax, zMin, zMid);
	northEast = new QuadTree(boundNorthEast);

	AABB* boundSouthWest = new AABB(xMin, xMid, zMid, zMax);
	southWest = new QuadTree(boundSouthWest);

	AABB* boundSouthEast = new AABB(xMid, xMax, zMid, zMax);
	southEast = new QuadTree(boundSouthEast);

	/*
	insert all the nodes at this level into the appropriate children
	*/
	for each (Node* node in mPoints)
	{
		northWest->insert(node);
		northEast->insert(node);
		southWest->insert(node);
		southEast->insert(node);
	}
	//we want only the leaf nodes to have data
	mPoints.clear();
}

/*
return all AABBs at the leafs
*/
std::list<AABB*> QuadTree::frustemCheck()
{
	std::list<AABB*> AABBInRange;
	std::list<AABB*> temp;
	if (northWest == NULL)
	{
		
		AABBInRange.push_back(mBound);
		
	}
	else
	{
		temp = northWest->frustemCheck();
		AABBInRange.insert(AABBInRange.end(), temp.begin(), temp.end());
		temp = northEast->frustemCheck();
		AABBInRange.insert(AABBInRange.end(), temp.begin(), temp.end());
		temp = southWest->frustemCheck();
		AABBInRange.insert(AABBInRange.end(), temp.begin(), temp.end());
		temp = southEast->frustemCheck();
		AABBInRange.insert(AABBInRange.end(), temp.begin(), temp.end());
		
	}
	return AABBInRange;
}

/*
draw the tree recursivly
*/
void QuadTree::draw(const glm::mat4& mView, const glm::mat4& mProj)
{
	if (northWest == NULL)
	{
		mBound->Render(mView, mProj);
	}
	if (northWest != NULL)
	{
		northWest->draw(mView, mProj);
		northEast->draw(mView, mProj);
		southEast->draw(mView, mProj);
		southWest->draw(mView, mProj);
	}
}

