#include "Game.h"

bool Game::Init() {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		return false;
	}

	window = SDL_CreateWindow("PONG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1270, 800, 0);
	if (!window) {
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		return false;
	}

	// Initialization of paddles
	leftPaddle = new Paddle(0);
	rightPaddle = new Paddle(1);

	// Initialize ball
	ball = new Ball;

	return true;
}

void Game::GameLoop() {
	while (isRunning) {
		HandleEvents();
		Update();
		Draw();
	}
}

void Game::HandleEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			isRunning = false;
		}
	}

	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	if (keystates[SDL_SCANCODE_ESCAPE]) {
		isRunning = false;
	}

	// Restart
	if (keystates[SDL_SCANCODE_R]) {
		ball->Reset();
	}

	// Left Paddle movement
	leftPaddle->SetDir(0);
	if (keystates[SDL_SCANCODE_E]) {
		leftPaddle->SetDir(-1);
	}
	if (keystates[SDL_SCANCODE_D]) {
		leftPaddle->SetDir(1);
	}

	// Right Paddle movement
	rightPaddle->SetDir(0);
	if (keystates[SDL_SCANCODE_UP]) {
		rightPaddle->SetDir(-1);
	}
	if (keystates[SDL_SCANCODE_DOWN]) {
		rightPaddle->SetDir(1);
	}
}

void Game::Update() {
	leftPaddle->Update();
	rightPaddle->Update();

	ball->Update(leftPaddle, rightPaddle);
}

void Game::Draw() {
	SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
	SDL_RenderClear(renderer);

	// Draw paddles
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, leftPaddle->GetRect());
	SDL_RenderFillRect(renderer, rightPaddle->GetRect());

	// Draw ball
	SDL_SetRenderDrawColor(renderer, 40, 40, 255, 255);
	SDL_RenderFillRect(renderer, ball->GetRect());

	SDL_RenderPresent(renderer);
}

void Game::Shutdown() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}