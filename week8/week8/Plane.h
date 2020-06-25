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
#include "AABB.h"
#include "BoundingSphere.h"
class Plane
{
	public:
		Plane(const glm::vec3& normal,const glm::vec3& point);
		float distance(const glm::vec3& point);
		glm::vec3 getNormal();
		float getDistance();
	private:

		glm::vec3 mNormal;
		glm::vec3 mPoint;
		float mDistance;

};
