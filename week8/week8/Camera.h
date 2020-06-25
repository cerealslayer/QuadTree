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
#include "BoundingSphere.h"
#include "Plane.h"
#include <list>
#include <cmath>

enum class CameraMode { FirstPerson, Static };

class Camera
{
public:
	
	Camera(const glm::vec3& position,const glm::vec3& direction);
	void setStaticCamera(const glm::vec3& position, const glm::vec3& direction);
	void setMode(const CameraMode& mode);
	void update(float deltaf);
	void setNear(float near);
	void setFar(float far);
	const glm::mat4& getViewMatrix();
	const glm::mat4& getProjectionMatrix();
	void frustum();
	std::string sphereCheck(BoundingSphere* sphere);
	std::string AABBCheck(AABB* aabb);

	


private:
	void firstPerson();
	void staticCam();

	float mFov = 45.0;
	float mWidth = 1280.0f;
	float mLength = 720.0f;

	float mNear = 0.1f;
	float mFar = 100.0f;

	glm::mat4 mView = glm::lookAt(glm::vec3(0.0f, 20.0f, 60.0f), glm::vec3(20.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 mProj = glm::perspective(mFov, mWidth / mLength, mNear, mFar);

	glm::vec3 mPosition = glm::vec3(0.0f, 0.0f, 5.0f);
	glm::vec3 mDirection = glm::vec3(0.0f,0.0f,0.0f);
	glm::vec3 mTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	
	float mHorizontalAngle = 3.14f;
    float mVerticalAngle = 0.0f;


	float mSpeed = 0.5f;
	float mMouseSpeed = 0.0005f;

	

	bool mInitial = true;

	CameraMode mCameraMode = CameraMode::Static;

	float hightNear = 2 * tan(mFov / 2) * mNear;
	float hightFar = 2 * tan(mFov / 2) * mFar;

	float widthNear = hightNear * (mWidth / mLength);
	float widthFar = hightFar * (mWidth / mLength);

	std::list<Plane*> mPlanes;
	
	
};
