#pragma once
#include "stdafx.h"

#include "GameTimer.h"
#include "GL/renderer_gl.h"
#include "Logger.h"
class Game
{
public:
	Game(void);
	~Game(void);
	void Update(void);
	void MouseMove(int x, int y);
	void UpdateMovement(float forward, float right);
	void ProcessInput(void);
	void SetRenderer(Renderer *renderer);

	// Created and assigned in main window file
	Logger *logger;
	Renderer *renderer;
private:
	GameTimer *m_timer;
	double dt;

	Camera *camera;
	// Input
	Vec2 mouseOffset;
	Vec2 charMovement;
};

