#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/color_space.hpp>

using color3_t = glm::vec3;
using color4_t = glm::vec4;
using rgba_t = uint32_t;

inline color4_t RGBAToColor(const rgba_t& rgba) 
{
	float red = glm::clamp(static_cast<float>((rgba >> 24) & 0xFF) / 255.0f, 0.0f, 1.0f);
	float green = glm::clamp(static_cast<float>((rgba >> 16) & 0xFF) / 255.0f, 0.0f, 1.0f);
	float blue = glm::clamp(static_cast<float>((rgba >> 8) & 0xFF) / 255.0f, 0.0f, 1.0f);
	float alpha = glm::clamp(static_cast<float>(rgba & 0xFF) / 255.0f, 0.0f, 1.0f);

	return color4_t(red, green, blue, alpha);
}

inline rgba_t ColorToRGBA(const color4_t& color) 
{
	uint8_t red = static_cast<uint8_t>(glm::clamp(color.r * 255.0f, 0.0f, 255.0f));
	uint8_t green = static_cast<uint8_t>(glm::clamp(color.g * 255.0f, 0.0f, 255.0f));
	uint8_t blue = static_cast<uint8_t>(glm::clamp(color.b * 255.0f, 0.0f, 255.0f));
	uint8_t alpha = static_cast<uint8_t>(glm::clamp(color.a * 255.0f, 0.0f, 255.0f));

	return (static_cast<uint32_t>(red) << 24) | (static_cast<uint32_t>(green) << 16) | (static_cast<uint32_t>(blue) << 8) | static_cast<uint32_t>(alpha);
}
