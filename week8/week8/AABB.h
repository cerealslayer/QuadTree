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
#include "W_BufferManager.h"
#include "W_VertexDeclaration.h"
#include "W_ProgramManager.h"
#include <cmath>
#include "BoundingSphere.h"
#include <algorithm> 

struct VertexNoColor
{
	GLfloat x, y, z;
};

class AABB
{
	public:
		AABB(float Xmin, float Xmax, float Zmin, float Zmax);
		
		
		bool intersect(BoundingSphere* sphere);
		
		
		float getXmin()
		{
			return mXMin;
		}
		float getXmax()
		{
			return mXMax;
		}
		float getZmin()
		{
			return mZMin;
		}
		float getZmax()
		{
			return mZMax;
		}
		void Render(const glm::mat4& mView, const glm::mat4& mProj);
		
	private:

		float mXMin;
		float mXMax;

		float mZMin;
		float mZMax;

		static const VertexNoColor LineVertices[];

		static wolf::VertexBuffer* g_pVB;
		static wolf::VertexDeclaration* g_pDecl;
		static wolf::Program* g_pProgram;

		float scaleX;
		float scaleZ;
		glm::vec3 center;


	

		
};

