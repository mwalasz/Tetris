#ifndef GAME_H
#define GAME_H

#pragma region Included elements

#include <SDL2/SDL.h>
#include <iostream>
#include "definitions.h"
#include "draw.h"

#pragma endregion

//Game - klasa reprezentujaca cala gre


class Game : protected Draw
{
public:
	Game();
	~Game();

	void Tetris(); //cala petla gry
};

#endif