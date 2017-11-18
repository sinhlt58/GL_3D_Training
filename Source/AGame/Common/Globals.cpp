#include "stdafx.h"
#include "Globals.h"

// define window size
int Globals::screenHeight = 720;
int Globals::screenWidth = 960;
float Globals::s_DeltaTime = 0;
glm::vec3 Globals::s_LightColor = glm::vec3(1.0, 1.0, 1.0);
glm::vec3 Globals::s_LightPosition = glm::vec3(1.2f, 1.0f, 2.0f);
glm::vec3 Globals::s_LightViewPos = glm::vec3(-0.2, -0.3, 5.0);
std::vector<glm::vec3> Globals::s_PointLightPos = {
										glm::vec3(0.7f,  0.2f,  2.0f),
										glm::vec3(2.3f, -3.3f, -4.0f),
										glm::vec3(-4.0f,  2.0f, -12.0f),
										glm::vec3(0.0f,  0.0f, -3.0f) };