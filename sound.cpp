#include "sound.h"

Sound::Sound()
{
	//inicjalizacja biblioteki i kanalu dzwiekowego
	if (SDL_Init(SDL_INIT_AUDIO) ||
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048))
	{
		throw std::runtime_error(Mix_GetError());
	}

	//zaladowanie muzyki
	music_ = Mix_LoadMUS("Sounds/soundtrack.ogg");
	//zaladowanie dzwieku obrotu
	shortSoundsSpace_ = Mix_LoadWAV("Sounds/space.ogg");
	//zaladowanie dzwieku obrotu
	shortSoundsLine_ = Mix_LoadWAV("Sounds/line.ogg");
	//zaladowanie dzwieku konca gry
	shortSoundsDefeat_ = Mix_LoadWAV("Sounds/defeat.ogg");
	//zaladowanie dzwieku ulozenia klocka
	shortSoundsPlacedBrick_ = Mix_LoadWAV("Sounds/down.ogg");

	//sprawdzenie czy poprawnie otwarto zasoby dzwiekowe
	if (!(music_ || shortSoundsSpace_ || shortSoundsSpace_ 
		|| shortSoundsDefeat_ || shortSoundsPlacedBrick_))
	{
		throw std::runtime_error(Mix_GetError());
	}
}


Sound::~Sound()
{
	Mix_FreeMusic(music_);
	music_ = nullptr;

	Mix_FreeChunk(shortSoundsSpace_);
	shortSoundsSpace_ = nullptr;
	Mix_FreeChunk(shortSoundsSpace_);
	shortSoundsSpace_ = nullptr;
	Mix_FreeChunk(shortSoundsPlacedBrick_);
	shortSoundsPlacedBrick_ = nullptr;

	Mix_Quit();
}

void Sound::playMusic()
{
	Mix_PlayMusic(music_, -1);
}

void Sound::playComunicates(int type)
{
	if (type == SPACE)
	{//obrot figury po spacji
		Mix_PlayChannel(-1, shortSoundsSpace_, 0);
	}
	else if (type == LINE)
	{//usuniecie linii
		Mix_PlayChannel(-1, shortSoundsLine_, 0);
	}
	else if(type == DEFEAT)
	{//przegrana
		Mix_PlayChannel(-1, shortSoundsDefeat_, 0);
	}
	else if (type == BRICK_PLACED)
	{//ulozony klocek na dole
		Mix_PlayChannel(-1, shortSoundsPlacedBrick_, 0);
	}
}