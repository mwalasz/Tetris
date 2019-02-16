#pragma region Included elements

	#define SDL_MAIN_HANDLED
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_ttf.h>
	#include <iostream>
	#include "draw.h"
	#include "definitions.h"
	#include "board.h"
	#include "results.h"
	#include "game.h"
	#include "sound.h"

#pragma endregion

//Krotki opis programu:
/*
Gra polega na ulozeniu jak najwiekszej ilosci pelnych linii ze spadajacych klockow.

Pelna linia znika z ekranu po ulozeniu.

Na dole ekranu wyswietlana jest dotychczasowa liczba wypelnionych linii, 
a takze obecny poziom gry. Poziom jest zwiekszany co okreslona liczbe wypelnionych linii,
liczbe ta mozemy zdefiniowac w pliku "definitons.h" (domyslnie ustawiona na 3).

W grze jest 5 poziomow, z kazdym poziomem zwieksza sie szybkosc opadania figur na dol planszy.
Dostepne sa nastepujace poziomy: poczatkujacy, latwy, sredni, trudny, profesjonalny.

Gra konczy sie, gdy zabraknie miejsca na ekranie lub gdy nacisnie sie ESC.
Po zakonczeniu wyswietli sie obraz GAME OVER.

Wyniki gry zapisywane sa do pliku "gameResults.txt", ktory znajduje sie w folderze Results projektu.
Zbierane sa tam takie dane jak czas zakoczenia gry, dlugosc gry, koncowy poziom trudnosci oraz 
liczba wypelnionych linii.

Sterowanie:
	- strzalki:
		- w dol - przyspieszenie klocka
		- w lewo - przesuniecie klocka w lewo
		- w prawo - przesuniecie klocka w prawo
	- spacja - obrot figury (mozna naciskac w nieskonczonosc)
	- F1 - wlaczenie podkladu muzycznego
	- F2 - wylaczenie podkladu muzycznego
	- ESC - wyjscie z gry

Do poprawnej pracy, program wymaga nastepujacych bibliotek:
	- SDL2 - obsluga efektow graficznych (glowna)
	- SDL_mixer - obsluga efektow dzwiekowych (rozszerzenie glownej)
	- SDL_ttf - obsluga renderowania tekstu (rozszerzenie glownej)
*/

int main(int argc, char ** argv)
{
	Game game;
	game.Tetris();

	return 0;
}