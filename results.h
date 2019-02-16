#ifndef RESULTS_H
#define RESULTS_H

#pragma region Included elements

#include <SDL2/SDL.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include "definitions.h"
#include "board.h"

#pragma endregion

//Results - klasa wyniki uzyskane w trakcie gry

class Results : protected Board
{
private:
	std::string userName_; //imie gracza
	double gameDuration_; //czas trwania gry
	int level_; //poziom
	int linesFilled_; //ilosc wypelnionych linii
	time_t endTime_; //czas zakonczenia gry

public:
	Results();
	~Results();

	int GetLinesFilled() const;
	void SetLinesResult(int number); //setter ustawiajacy liczbe wypelnionych linii na koneic gry
	
	void SetLevel(int number); //setter ustawiajacy poziom trudnosci na koniec gry
	std::string GetNameOfGameLevel(); //funkcja przypisujaca stringa z nazwa do poziomu trudnosci

	std::chrono::time_point<std::chrono::system_clock> GetTimeForDuration(); //czas rozpoczecia lub zakonczenia gry
	std::string GetEndTimeOfGame(); //pobiera czas (date) zakonczenia gry

	void SetGameDuration(double time); //setter dla czasu trwania gry
	double GetGameDuration(); //getter dla czasu trwania gry, zaokragla do czesci setnych

	std::string GameDurationForDisplay(); //zmienia czas trwania gry na stringa i umozliwie lepsze wyswietlanie

	void SaveResultsToFile(const std::string & fileName); //funkcja zapisujaca wyniki do pliku
};

#endif