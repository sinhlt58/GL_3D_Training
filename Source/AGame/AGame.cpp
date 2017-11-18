// NewTrainingFramework.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "GraphicsEngine/Shaders.h"
#include "GraphicsEngine/Vertex.h"
#include "Common/Globals.h"
#include "GraphicsEngine/Texture.h"
#include "Entity/Cube.h"
#include <ctime>
#include "Manager/Camera.h"
#include "Manager/ManagerInput.h"
#include <iostream>
#include "GraphicsEngine/Model.h"
#include "GraphicsEngine/ComponentGraphics.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

std::shared_ptr<Cube> cube = std::make_shared<Cube>();
std::shared_ptr<Cube> lightSource = std::make_shared<Cube>();
std::vector<std::shared_ptr<Cube>> cubes;

inline float GetRandFloat(float min, float max) {
	return min + float(std::rand()) / RAND_MAX*max;
}

int Init(ESContext *esContext)
{
	glEnable(GL_DEPTH_TEST);

	SingletonCamera::CreateInstance();
	SingletonManagerInput::CreateInstance();

	std::srand((unsigned)time(nullptr));

	//todo: remove later and this code should be in factory and resource manager class
	std::shared_ptr<Shaders> shader = std::make_shared<Shaders>();
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	std::shared_ptr<Texture> texture2 = std::make_shared<Texture>();
	std::shared_ptr<Model> model = std::make_shared<Model>();
	std::shared_ptr<Shaders> shader2 = std::make_shared<Shaders>();

	shader->Init("../Data/Shaders/EntityVS.vs", "../Data/Shaders/EntityFS.fs");
	texture->LoadFile("../Data/Textures/container_wood.png");
	texture2->LoadFile("../Data/Textures/container_wood_specular.png");
	model->LoadModel("../Data/Models/cube.obj");
	shader2->Init("../Data/Shaders/LightSourceVS.vs", "../Data/Shaders/LightSourceFS.fs");

	cube->Init();
	lightSource->Init();

	for (int i = 0; i < 10; i++){
		std::shared_ptr<Cube> c = std::make_shared<Cube>();
		c->Init();
		c->GetComponentGraphics()->SetModel(model);
		c->GetComponentGraphics()->SetTexture(texture);
		c->GetComponentGraphics()->SetShader(shader);
		c->GetComponentGraphics()->SetObjectColor(glm::vec3(1.0, 0.5, 0.31));
		c->GetComponentGraphics()->AddTexture(texture2); //specular texture
		
		c->GetComponentGraphics()->SetRotate(glm::vec3(i*20.0f, 0.0f, i*-20.0f));
		c->GetComponentGraphics()->SetPosition(glm::vec3(GetRandFloat(-10, 10), GetRandFloat(-10, 10), GetRandFloat(-10, 10)));
		cubes.push_back(c);
	}
	
	cube->GetComponentGraphics()->SetModel(model);
	cube->GetComponentGraphics()->SetTexture(texture);
	cube->GetComponentGraphics()->SetShader(shader);
	cube->GetComponentGraphics()->SetObjectColor(glm::vec3(1.0, 0.5, 0.31));
	cube->GetComponentGraphics()->AddTexture(texture2);

	//add point lights
	for (int i=0; i<Globals::s_NumPointLights; i++)
	{
		std::shared_ptr<Cube> c = std::make_shared<Cube>();
		c->Init();
		c->GetComponentGraphics()->SetModel(model);
		c->GetComponentGraphics()->SetTexture(texture);
		c->GetComponentGraphics()->SetShader(shader2);

		c->GetComponentGraphics()->SetRotate(glm::vec3(0.0, 0.0, 45));
		c->GetComponentGraphics()->SetPosition(Globals::s_PointLightPos[i]);
		c->GetComponentGraphics()->SetScale(glm::vec3(0.2, 0.2, 0.2));
		cubes.push_back(c);
	}

	return 0;
}

void Draw(ESContext *esContext)
{
	
}

void Update(ESContext *esContext, float deltaTime)
{
	Globals::s_DeltaTime = deltaTime / 100;
	if (InputMgr->IsPressed(KEY_FORWARD))
	{
		CameraMgr->MoveForWard();
	}
	if (InputMgr->IsPressed(KEY_BACKWARD))
	{
		CameraMgr->MoveBackWard();
	}
	if (InputMgr->IsPressed(KEY_LEFT))
	{
		CameraMgr->MoveLeft();
	}
	if (InputMgr->IsPressed(KEY_RIGHT))
	{
		CameraMgr->MoveRight();
	}
	cube->Update(deltaTime);
	for (auto c : cubes) {
		c->Update(deltaTime);
	}
	lightSource->GetComponentGraphics()->SetPosition(Globals::s_LightPosition);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	cube->Render(deltaTime);
	for (auto c : cubes) {
		c->Render(deltaTime);
	}
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Key(ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (bIsPressed)
	{
		switch (key)
		{
			case 'w': case 'W':
				InputMgr->SetKeyPressed(KEY_FORWARD);
				break;
			case 's': case 'S':
				InputMgr->SetKeyPressed(KEY_BACKWARD);
				break;
			case 'a': case 'A':
				InputMgr->SetKeyPressed(KEY_LEFT);
				break;
			case 'd': case 'D':
				InputMgr->SetKeyPressed(KEY_RIGHT);
				break;
		}
	}else
	{
		switch (key)
		{
		case 'w': case 'W':
			InputMgr->SetKeyPressed(KEY_FORWARD, false);
			break;
		case 's': case 'S':
			InputMgr->SetKeyPressed(KEY_BACKWARD, false);
			break;
		case 'a': case 'A':
			InputMgr->SetKeyPressed(KEY_LEFT, false);
			break;
		case 'd': case 'D':
			InputMgr->SetKeyPressed(KEY_RIGHT, false);
			break;
		}
	}
}

void MouseMove(ESContext* ESContext, float x, float y)
{
	if (InputMgr->IsFirstTouch())
	{
		InputMgr->SetLastTouchPos(glm::vec2(x, y));
		InputMgr->SetIsFirstTouch(false);
	}else
	{
		auto p = InputMgr->GetTouchPos();
		InputMgr->SetLastTouchPos(p);
	}
	InputMgr->SetTouchPos(glm::vec2(x, y));
	CameraMgr->UpdateRotationFPS();
}

void MouseDown(ESContext* esContext, float x, float y)
{
	InputMgr->SetTouchPos(glm::vec2(x, y));
	InputMgr->SetLastTouchPos(glm::vec2(x, y));
}

void MouseUp(ESContext* esContext, float x, float y)
{
	InputMgr->SetTouchPos(glm::vec2(x, y));
	InputMgr->SetLastTouchPos(glm::vec2(x, y));
	InputMgr->SetIsFirstTouch(true);
}

void CleanUp()
{
	SingletonCamera::DestroyInstance();
	SingletonManagerInput::DestroyInstance();
}

//////////////////////////////////////////// WINDOWS main function ////////////////////////////////////////////////////
#ifdef _WIN32

#include <conio.h>

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0)
		return 0;

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);
	esRegisterMouseMoveFunc(&esContext, MouseMove);
	esRegisterMouseDownFunc(&esContext, MouseDown);
	esRegisterMouseUpFunc(&esContext, MouseUp);
	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	printf("Press any key...\n");
	_getch();

	return 0;
}

#endif
//////////////////////////////////////////// WINDOWS main function ////////////////////////////////////////////////////
