#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 nor;
	glm::vec4 color;
	glm::vec2 uv;
};