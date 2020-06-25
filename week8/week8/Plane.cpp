#include "Plane.h"
#include <stdlib.h> 

Plane::Plane(const glm::vec3& normal, const glm::vec3& point) : mNormal(normal), mPoint(point)
{
	glm::normalize(mNormal);
	mDistance = -glm::dot(mNormal, mPoint);
}
/*
distance between this plane and a point
*/
float Plane::distance(const glm::vec3& point)
{
	return (mDistance + glm::dot(mNormal, point));
}
glm::vec3 Plane::getNormal()
{
	return mNormal;
}
float Plane::getDistance()
{
	return mDistance;
}