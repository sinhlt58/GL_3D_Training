#pragma once
#include <glm/vec3.hpp>
#include <vector>

class Globals
{
public:
	static int screenWidth;
	static int screenHeight;
	static float s_DeltaTime;
	static glm::vec3 s_LightColor;
	static glm::vec3 s_LightPosition;
	static glm::vec3 s_LightViewPos;
	static int const s_NumPointLights = 4;
	static std::vector<glm::vec3> s_PointLightPos;
};
