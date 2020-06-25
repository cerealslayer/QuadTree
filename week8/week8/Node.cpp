#include "Node.h"

/*
add a bounding sphere to this node and assign its name
*/
Node::Node(const std::string& name) :mName(name)
{
	mBoundingSphere = new BoundingSphere();
}

const std::string& Node::getName()
{
	return mName;
}

void Node::addChild(Node* child)
{
	mChildern.push_back(child);
}
void Node::setParent(Node* parent)
{
	mParent = parent;
}

bool Node::hasParent()
{
	return(mParent);
}
/*
get the world transform for this node and all its children
*/
const glm::mat4& Node::getWorldTransform()
{
	if (dirty)
	{
		mWorld = glm::translate(mTranslation) * glm::rotate(mAngle, mRotation) * glm::scale(mScale);
	}
	if (hasParent())
	{
		return mWorld * mParent->getWorldTransform();
	}
	return mWorld;
}
const glm::mat4& Node::getTransfrom()
{
	if (dirty)
	{
		mWorld = glm::translate(mTranslation) * glm::rotate(mAngle, mRotation) * glm::scale(mScale);
	}
	mWorld = glm::translate(mTranslation) * glm::rotate(mAngle, mRotation) * glm::scale(mScale);
	return mWorld;
}

/*
increase the scale by a scalar
*/
void Node::scale(const glm::vec3& scale)
{
	mScale *= scale;
	mBoundingSphere->Radius(((mScale.x + mScale.z)/2));
	dirty = true;
}
/*
increase rotation vector by a certain amount
*/
void Node::rotation(const glm::vec3& rotation)
{
	mRotation += rotation;
	dirty = true;
}
/*
move the object a certain amount
*/
void Node::translate(const glm::vec3& translation)
{
	mTranslation += translation;
	mBoundingSphere->Position(translation);
	dirty = true;
}
/*
increase the angle by a certain amount
*/
void Node::angle(float angle)
{
	mAngle += angle;
	dirty = true;
}
/*
set a new scale
*/
void Node::setScale(const glm::vec3& scale)
{
	mScale = scale;
	dirty = true;
}
/*
set a new Rotation vector
*/
void Node::setRotation(const glm::vec3& rotation,float angle)
{
	mRotation = rotation;
	mAngle = angle;
	dirty = true;
}
/*
set a new transform position
*/
void Node::setTranslate(const glm::vec3& translation)
{
	mTranslation = translation;
	mBoundingSphere->setPosition(translation);
	dirty = true;
}
/*
return the current position
*/
const glm::vec3& Node::getTranslation()
{
	return mTranslation;
}

/*
return the bounding sphere
*/
BoundingSphere* Node::getSphere()
{
	return mBoundingSphere;
}
/*
if you reach here, then there is no subclass to be renderd
*/
void Node::Render(const glm::mat4& view, const glm::mat4& projection)
{
	throw std::runtime_error("Render() is unsupported in this context");
}
void Node::update(float deltat)
{
	for each (Node* node in mChildern)
	{
		node->update(deltat);
	}
}
