#ifndef DRAW_H
#define DRAW_H

#pragma region Included elements

#include <SDL2/SDL.h>
#include <iostream>
#include "board.h"
#include "results.h"
#include "sound.h"

#pragma endregion

//Draw - klasa umozliwiajaca graficzne rysowanie obiektow oraz 
//		 realizacje jednej klatki gry, ktora jest zapetlona

class Draw : protected Results
{
private:
	//wskazniki dla biblioteki graficznej
	SDL_Window * pWindow_ = nullptr;
	SDL_Renderer * pRenderer_ = nullptr;
	SDL_Surface * pScreenSurface_ = nullptr;
	SDL_Surface * pEndImage_ = nullptr;
	Board board_;
	Brick brick_;
	Sound sound_;
	uint32_t moveTime_;

public:
	Draw();
	~Draw();

	bool OneFrameAction(); //rysuje i uaktualnia ekran co klatke
	bool CheckCollision(Brick & brick); //kompleksowe sprawdzanie kolizji
	int SetDifficultyLevelOfGame(); //zmiana poziou trudnosci gry -> czasu opadania figury

	uint32_t GetMoveTime(); //getter dla moveTime_

	int HandleOfKeyActions(); //obsluga klawiszy klawiatury
	void MoveBrickByKeys(int x, int y); //przesuwanie klocka za pomoca klawiatury
	void ActionAfterEndOfTheGame(); //zrealizowanie akcji do wyjscia z gry za pomoca ESC
};

#endif