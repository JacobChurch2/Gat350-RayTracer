#pragma once
#include <glm/glm.hpp>

struct ray_t
{
	ray_t() = default;
	ray_t(const glm::vec3& origin, const glm::vec3& direction) :
		origin(origin),
		direction(direction)
	{}

	glm::vec3 GetPoint(float distance) const { return origin + (direction * distance); }
	glm::vec3 operator *(float distance) const { return GetPoint(distance); }

	glm::vec3 origin{ 0 };
	glm::vec3 direction{ 0 };
};