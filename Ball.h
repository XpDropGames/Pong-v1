#pragma once

#include "Paddle.h"

class Ball
{
public:
	Ball();
	void Update(Paddle* lPaddle, Paddle* rPaddle);
	void HandleCollision(Paddle* paddle);
	bool TopCollision(Paddle* paddle);
	bool BottomCollision(Paddle* paddle);

	SDL_Rect* GetRect();

private:
	int dir = 0;
	int size = 20;
	float speed;
	const int INITIAL_SPEED = 5.f;
	const int MAX_SPEED = 10.f;

	Vec2 pos;
	Vec2 vel;
	SDL_Rect rect;
};

