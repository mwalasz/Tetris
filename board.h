#ifndef BOARD_H
#define BOARD_H

#pragma region Included elements

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include "definitions.h"
#include "brick.h"
#include "sound.h"

#pragma endregion

//Board - klasa reprezentujaca pole powierzchni gry

class Board
{
private:
	bool net_[GAME_WIDTH][GAME_HEIGHT]; //siatka tablicy
	int numberOfFilledLines_;
	Sound sound_;

	TTF_Font * fontStyle = nullptr; //wskaznik dla czcionki
	//wskazniki na tekstury dla dwoch napisow
	SDL_Texture * lineNumberTexture = nullptr; 
	SDL_Texture * levelTexture = nullptr;
	//prostokaty(obszary) na tekstury dla dwoch napisow
	SDL_Rect lineNumberRectangle;
	SDL_Rect levelRectangle;

public:
	Board();
	~Board();

	void DrawBoard(SDL_Renderer * pRenderer); //rysuje tablice
	bool IsCollision(Brick & brick) const; //sprawdza czy wystapila kolizja
	void MergeBricks(Brick & brick); //laczy klocki
	void DeleteFilledLine(); //usuwanie wypelnionych linii

	//setter i getter dla liczby linii
	int GetNumberOfFilledLines_() const;
	void SetNumberOfFilledLines_(int number);

	std::string GetNameOfLevel(); //zwraca nazwe obecnego poziomu trudnosci

	//settery i gettery dla czcionki
	SDL_Rect GetLevelRectangle();
	SDL_Rect GetLinelRectangle();
	void SetLevelRectangle(int x, int y);
	void SetLineNumberRectangle(int x, int y);
	
	//tworzenie powierzchni na ktorej zostanie wyswietlony tekst (obecny poziom i liczba wypelnionych linii)
	void CreateSurfaceToPutTextOn(SDL_Renderer * renderer, int toDisplay, std::string level);
	//przeksztalcenie powierzchni na teksture
	SDL_Texture* SurfaceToTexture(SDL_Surface* surf, SDL_Renderer * renderer);
};

#endif