#ifndef SOUND_H
#define SOUND_H

#pragma region Included elements

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "definitions.h"

#pragma endregion

//Sound - klasa umozliwiajaca odtwarzanie dzwiekow

class Sound
{
private:
	Mix_Music * music_ = nullptr; //muzyka w tle
	Mix_Chunk * shortSoundsSpace_ = nullptr; //dzwiek obrotu figury
	Mix_Chunk * shortSoundsLine_ = nullptr; //usuniecie linii
	Mix_Chunk * shortSoundsDefeat_ = nullptr; //koniec gry
	//ulozonenie pojedynczego klocka
	Mix_Chunk * shortSoundsPlacedBrick_ = nullptr; 

public:
	Sound();
	~Sound();

	void playMusic(); //odtwarzanie glownej muzyki
	void playComunicates(int type); //odtwarzanie 
	//krotkich sygnalow w zaleznosci od akcji
};

#endif