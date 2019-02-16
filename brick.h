#ifndef BRICK_H
#define BRICK_H

#pragma region Included elements

#include <SDL2/SDL.h>
#include "definitions.h"

#pragma endregion

//Brick - klasa reprezentujaca figure (klocek) ktorym manewrujemy w trakcie gry

class Brick
 {
 public: //dostepne figury
	 enum Type { I = 0, J, L, O, S, T, Z };

 private:
	 Type typeOfBrick_; //typ figury
	 int rotation_; // obrot figury
	 //koordynaty figury:
	 int x_;
	 int y_;

public:
	Brick(Type);
	~Brick();

	bool IsBrickHere(int x, int y) const; //sprawdza czy klocek znajduje sie w danym miejscu
	void DrawBrick(SDL_Renderer * pRenderer); //rysuje figure
	void MoveBrick(int dx, int dy); //przemieszcza figure o dany wektor
	void RotateBrick(); //obraca figure
	Type RandomizeTypeOfBrick(); //losuje typ figury, ktory spadnie

	//gettery dla koordynatow
	int GetXCoordinate() const;
	int GetYCoordinate() const;
};

#endif