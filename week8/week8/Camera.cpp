#include "Camera.h"

using namespace std;

/*
create new camera at a position looking at a direction
*/
Camera::Camera(const glm::vec3& position,const glm::vec3& direction)
{
	this->mPosition = position;
	this->mDirection = direction;
}
/*
change the camera to a static camera and give it its values
*/
void Camera::setStaticCamera(const glm::vec3& position, const glm::vec3& direction)
{
	this->mPosition = position;
	this->mDirection = direction;
	this->mCameraMode = CameraMode::Static;
}
/*
set the mode to the given one, either first person or static
*/
void Camera::setMode(const CameraMode& mode)
{
		this->mCameraMode = mode;	
}

const glm::mat4& Camera::getViewMatrix()
{
	return this->mView;
}

const glm::mat4& Camera::getProjectionMatrix()
{
	return this->mProj;
}


void Camera::setNear(float near)
{
	this->mNear = near;
	this->mProj = glm::perspective(45.0f, mWidth / mLength, mNear, mFar);
}

void Camera::setFar(float far)
{
	this->mFar = far;
	this->mProj = glm::perspective(45.0f, mWidth / mLength, mNear, mFar);
}
/*
call the appropriate method to update
*/
void Camera::update(float deltaT)
{
	
	if (this->mCameraMode == CameraMode::Static)
	{
		staticCam();
	}
	else
	{
		firstPerson();
	}
	

}
/*
calculate the frustum
*/
void Camera::frustum()
{
	
	glm::vec3 Z, X, Y,centerNear,centerFar;
	
	Z = mPosition - mTarget;
	glm::normalize(Z);

	X = glm::vec3(0.0f, 1.0f, 0.0f) * Z;
	glm::normalize(X);

	Y = X * Z;

	centerNear = mPosition - Z * mNear;
	centerFar = mPosition - Z * mFar;


	Plane* near = new Plane(-Z, centerNear);
	Plane* far = new Plane(Z, centerFar);

	glm::vec3 aux, normal;

	aux = (centerNear + Y * hightNear) - mPosition;
	glm::normalize(aux);

	normal = aux * X;

	Plane* top = new Plane(normal, centerNear + Y * hightNear);

	aux = (centerNear - Y * hightNear) - mPosition;
	glm::normalize(aux);
	normal = X * aux;

	Plane* bottom = new Plane(normal, centerNear - Y * hightNear);

	aux = (centerNear - X * widthNear) - mPosition;
	glm::normalize(aux);
	normal = aux * Y;
	Plane* left = new Plane(normal, centerNear - X * widthNear);

	aux = (centerNear + X * widthNear) - mPosition;
	glm::normalize(aux);
	normal = Y * aux;
	Plane* right = new Plane(normal, centerNear + X * widthNear);

	mPlanes.clear();
	
	mPlanes.push_back(top);
	mPlanes.push_back(bottom);
	mPlanes.push_back(left);
	mPlanes.push_back(right);
	mPlanes.push_back(far);
	mPlanes.push_back(near);
	

}
/*
check for frustum and sphere collision (was used for brute force but is not used now)
*/
std::string Camera::sphereCheck(BoundingSphere* sphere)
{
	float distance;
	std::string result = "inside";

	for each (Plane* p in mPlanes)
	{
		distance = p->distance(sphere->getPosition());
		if (distance < -sphere->getRadius())
		{
			result = "outside";
		}
		else if (distance < sphere->getRadius())
		{
			result = "intersect";
		}
	}
	return result;
}
/*
check for frustum AABB collision
*/
std::string Camera::AABBCheck(AABB* aabb)
{

	std::string result = "inside";
	for each (Plane* p in mPlanes)
	{
		glm::vec3 center = (glm::vec3(aabb->getXmax(),0.0f,aabb->getXmin()) + glm::vec3(aabb->getZmax(),0.0f,aabb->getZmin())) * 0.5f; 
		glm::vec3 extents = glm::vec3(aabb->getXmax(), 0.0f, aabb->getXmin()) - center; 

		float radius = extents.x * std::abs(p->getNormal().x) + extents.y * std::abs(p->getNormal().y) + extents.z * std::abs(p->getNormal().z);

		float s = glm::dot(p->getNormal(), center) - p->getDistance();

		if (std::abs(s) <= radius)
		{
			result = "outside";
		}
		
	}
	return result;
}

/*
set the camera to the given position and target
*/
void Camera::staticCam()
{
	this->mView = glm::lookAt(mPosition, mTarget, glm::vec3(0.0f, 1.0f, 0.0f));
}
/*
calculate the first person movement
*/
void Camera::firstPerson()
{
	int xpos, ypos;
	glfwGetMousePos(&xpos, &ypos);
	glfwSetMousePos(mWidth / 2, mLength / 2);
	glfwDisable(GLFW_MOUSE_CURSOR);

	this->mHorizontalAngle += this->mMouseSpeed * float(1280 / 2 - xpos);
	this->mVerticalAngle += this->mMouseSpeed * float(720 / 2 - ypos);

	this->mDirection = glm::vec3(
		cos(this->mVerticalAngle) * sin(this->mHorizontalAngle),
		sin(this->mVerticalAngle),
		cos(this->mVerticalAngle) * cos(this->mHorizontalAngle)
	);

	glm::vec3 right = glm::vec3(
		sin(this->mHorizontalAngle - 3.14f / 2.0f),
		0,
		cos(this->mHorizontalAngle - 3.14f / 2.0f)
	);

	// Move forward
	if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) {
		mPosition += mDirection * mSpeed;
	}
	// Move backward
	if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS) {
		mPosition -= mDirection * mSpeed;
	}
	// Strafe right
	if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
		mPosition += right * mSpeed;
	}
	// Strafe left
	if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
		mPosition -= right * mSpeed;
	}
	mTarget = mPosition + mDirection;
	this->mView = glm::lookAt(mPosition, mTarget, glm::vec3(0.0f, 1.0f, 0.0f));

}
