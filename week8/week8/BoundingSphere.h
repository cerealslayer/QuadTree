#pragma once
#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <stdio.h>
#include <stdlib.h>
#ifndef __APPLE__
#include <GL/glew.h>
#endif
#include <GL/glfw.h>
#include "W_Common.h"
#include <cmath>


class BoundingSphere
{
public:
	BoundingSphere() 
	{}
	void setPosition(const glm::vec3& position)
	{
		mPosition = position;
	}
	void Position(const glm::vec3& position)
	{
		mPosition += position;
	}
	const glm::vec3& getPosition()
	{
		return mPosition;
	}
	void setRadius(float radius)
	{
		mRadius = radius;
	}
	void Radius(float radius)
	{
		mRadius *= radius;
	}
	
	float getRadius()
	{
		return mRadius;
	}

private:
	float mRadius = 1.0f;
	glm::vec3 mPosition = glm::vec3(0.0f,0.0f,0.0f);
};
