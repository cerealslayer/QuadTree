#pragma once
#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <stdio.h>
#include <stdlib.h>
#ifndef __APPLE__
#include <GL/glew.h>
#endif
#include "W_Common.h"
#include <list>
#include <iostream>
#include "BoundingSphere.h"

class Node 
{
public:
	Node(const std::string& name);

	Node* getParent();
	std::list<Node*> getChildern();

	const std::string& getName();
	
	void setParent(Node* parent);
	void addChild(Node* child);

	bool hasParent();

	const glm::mat4& getWorldTransform();

	virtual void Render(const glm::mat4& view,const glm::mat4& projection);

	void scale(const glm::vec3& scale);
	void rotation(const glm::vec3& rotation);
	void translate(const glm::vec3& translate);
	void angle(float angle);

	void setScale(const glm::vec3& scale);
	void setRotation(const glm::vec3& rotation, float angle);
	void setTranslate(const glm::vec3& translate);

	const glm::vec3& getTranslation();
	BoundingSphere* getSphere();

	const glm::mat4& getTransfrom();

	void update(float deltat);
	
		
	



private:
	const std::string& mName;
	
	Node* mParent = NULL;
	std::list<Node*> mChildern;

	glm::vec3 mTranslation;
	glm::vec3 mScale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 mRotation = glm::vec3(1.0f, 1.0f, 1.0f);
	float mAngle = 0;

	bool dirty = false;

	glm::mat4 mWorld = glm::translate(0.0f, 0.0f, 0.0f) * glm::rotate(0.0f, 1.0f, 1.0f, 0.0f);

	BoundingSphere* mBoundingSphere;
	
};
