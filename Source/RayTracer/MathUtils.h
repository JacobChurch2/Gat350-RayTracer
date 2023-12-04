#pragma once
#include <glm/glm.hpp>

template <typename T>
inline T lerp(const T& a, const T& b, float t) {
	//Linear interpolation
	//<return (1 - t) * a + t * b> Also known as "lerp"
	//lerp(a,b,t) = ((1 - t) * a) + (t * b);
	return (1.0f - t) * a + t * b;
}

inline glm::vec3 cross(const glm::vec3& v1, const glm::vec3& v2)
{
	return glm::vec3
	(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	);
}

inline float dot(const glm::vec3& v1, const glm::vec3& v2)
{
	return glm::acos(dot(v1, v2));
}

inline glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n)
{
	return v - 2.0f * dot(n, v) * n;
}