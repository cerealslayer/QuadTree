#include "AABB.h"

const VertexNoColor AABB::LineVertices[] = {
{ -0.5f ,0.0f,0.5f},
{ 0.5f ,0.0f,0.5f},
{ 0.5f ,0.0f,0.5f},
{ 0.5f ,0.0f,-0.5f},
{ 0.5f ,0.0f,-0.5f},
{ -0.5f ,0.0f,-0.5f},
{ -0.5f ,0.0f,-0.5f},
{ -0.5f ,0.0f,0.5f},
};

wolf::VertexBuffer* AABB::g_pVB = 0;
wolf::VertexDeclaration* AABB::g_pDecl = 0;
wolf::Program* AABB::g_pProgram = 0;


AABB::AABB(float Xmin, float Xmax, float Zmin, float Zmax) : mXMin(Xmin), mXMax(Xmax), mZMin(Zmin), mZMax(Zmax)
{
	//calculate the center and the scale of this AABB
	center = glm::vec3((Xmax + Xmin) / 2, 0.0f, (Zmax + Zmin) / 2);
	scaleX = std::abs(Xmax - Xmin);
	scaleZ = std::abs(Zmax - Zmin);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	g_pProgram = wolf::ProgramManager::CreateProgram("data/week8/cube.vsh", "data/week8/cube.fsh");
	g_pVB = wolf::BufferManager::CreateVertexBuffer(LineVertices, sizeof(VertexNoColor) * 8);

	g_pDecl = new wolf::VertexDeclaration();
	g_pDecl->Begin();
	g_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
	g_pDecl->SetVertexBuffer(g_pVB);
	g_pDecl->End();
}
/*
check for intersection with a sphere
*/
bool AABB::intersect(BoundingSphere* sphere)
{
	//math make my head hurt
	glm::vec3 sphereVec = sphere->getPosition();
	float x = std::max(mXMin, std::min(sphereVec.x, mXMax));
	float z = std::max(mZMin, std::min(sphereVec.z, mZMax));

	float distance = std::sqrt((x - sphereVec.x) * (x - sphereVec.x) +
		(z - sphereVec.z) * (z - sphereVec.z));

	return distance < sphere->getRadius();

}

void AABB::Render(const glm::mat4& mView, const glm::mat4& mProj)
{
	// Use shader program.
	g_pProgram->Bind();

	static float s_fRot = 0;
	glm::mat4 mWorld = glm::translate(center) * glm::scale(scaleX, 1.0f, scaleZ);


	g_pProgram->SetUniform("projection", mProj);
	g_pProgram->SetUniform("view", mView);
	g_pProgram->SetUniform("world", mWorld);



	// Set up source data
	g_pDecl->Bind();

	// Draw!
	glDrawArrays(GL_LINES, 0, 8);
}