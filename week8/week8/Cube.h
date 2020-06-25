//-----------------------------------------------------------------------------
// File:			examples.h
// Original Author:	Gordon Wood
//
// Prototypes for all the example functions
//-----------------------------------------------------------------------------

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
#include "Node.h"

struct Vertex
{
	GLfloat x, y, z;
	GLubyte r, g, b, a;
};
class Cube :public Node
{
	public:

		Cube(const std::string& name);
		void Render(const glm::mat4& mView, const glm::mat4& mProj);
		
	private:
		static const Vertex cubeVertices[];

		static wolf::VertexBuffer* g_pVB;
		static wolf::VertexDeclaration* g_pDecl;
		static wolf::Program* g_pProgram;




		

};






