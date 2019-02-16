#include "game.h"

Game::Game() {}
Game::~Game() {}

void Game::Tetris()
{
	try
	{
		std::chrono::time_point<std::chrono::system_clock> start, end;

		start = GetTimeForDuration(); //czas rozpoczecia gry

		while (Draw::OneFrameAction()) {} //obsluga gry

		end = GetTimeForDuration(); //czas zakonczenia gry

		std::chrono::duration<double> elapsedSeconds = end - start; //obliczenie czasu gry

		SetGameDuration(elapsedSeconds.count()); //ustawienie czasu gry
	}
	catch (std::string)
	{
		std::cout << "Error while initializing libraries!";
	}

	Draw::SaveResultsToFile(GAME_RESULTS); //zapisanie rezultatow gry do pliku
}