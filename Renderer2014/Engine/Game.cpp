#include "Game.h"


Game::Game(void)
{
	m_timer = new GameTimer();
	m_timer->Start();

}

//----------------------------------------------------------------------------

Game::~Game(void)
{
	if (m_timer)
	{
		m_timer->Stop();
		delete m_timer;
	}
}

//----------------------------------------------------------------------------

void Game::SetRenderer(Renderer *renderer)
{
	this->renderer = renderer;
	this->camera = renderer->GetCamera();
}

//----------------------------------------------------------------------------

void Game::Update(void)
{
	m_timer->Tick();
	dt = m_timer->GetDt();

	// ------- Update all objects
	ProcessInput();
	renderer->Update(dt);

	// ------- Draw
	renderer->RenderScene();
}

//----------------------------------------------------------------------------

void Game::ProcessInput(void)
{
	
	// TODO : Implement FirstPersonController. "Controller"

	const float camRotateSpeed = dt * 0.1f;
	
	Vec2 diff = -camRotateSpeed * (mouseOffset);
	//diff = Vec2(0.1f, 0.1f);
	
	camera->Rotate( diff.y, diff.x, 0);
	camera->TranslateLocal(charMovement.x *0.1f, 0, -charMovement.y *0.1f);

	charMovement = Vec2(0, 0);
	mouseOffset = Vec2(0, 0);
}

//----------------------------------------------------------------------------

void Game::MouseMove(int x, int y)
{
	/*
	char buffer[100];
	sprintf(buffer, "UPDATING: %d %d OLD: %f %f\n", x, y, mouseOffset.x, mouseOffset.y);
	logger->Write(buffer);
	*/
	this->mouseOffset += Vec2((float)(x - 100.0f), (float) (y- 100.0f));
}

//----------------------------------------------------------------------------

void Game::UpdateMovement(float forward, float right)
{
	charMovement += Vec2(forward, right);
}