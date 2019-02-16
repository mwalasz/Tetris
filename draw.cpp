#pragma region Included elements

#include <stdexcept>
#include "definitions.h"
#include "draw.h"

#pragma endregion

#pragma region Constructors and decontructors

Draw::Draw() : brick_(brick_.RandomizeTypeOfBrick()), moveTime_(SDL_GetTicks())
{
	if (SDL_Init(SDL_INIT_VIDEO)) //w przypadku gdy nie udalo sie zainicjalizowac biblioteki 
	{//wyrzucany jest wyjatek
		std::string information = "Cannot initialize Libraries!";
		throw information;
	}
	else //w przeciwnym wypadku tworzone jest okno
	{
		SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_OPENGL, &pWindow_, &pRenderer_); //inicjalizacja okna
		SDL_SetWindowPosition(pWindow_, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED); //ustawienie pozycji okna

		pScreenSurface_ = SDL_GetWindowSurface(pWindow_); //utworzenie powierzchni do umieszczenia obrazu

		pEndImage_ = SDL_LoadBMP("Images/goodbye.bmp"); //zaladowanie obrazu
		if (pEndImage_ == nullptr)
		{
			std::string information = "Cannot find image!";
			throw information;
		}
	}
}

Draw::~Draw()
{
	SDL_FreeSurface(pEndImage_);
	pEndImage_ = nullptr;

	SDL_DestroyRenderer(pRenderer_);
	SDL_DestroyWindow(pWindow_);
	SDL_Quit();
}

#pragma endregion

uint32_t Draw::GetMoveTime()
{
	return moveTime_;
}

bool Draw::OneFrameAction()
{
	try //wykrywanie wyjatku pochodzacego z funkcji HandleOfKeyActions() 
	{
		int infoFromKeyBoard = HandleOfKeyActions(); //obsluga klawiatury

		if (infoFromKeyBoard == PRESSED_ESC) //w przypadku wykrycia ESC, nastepuje koniec gry i stosowny komunikat
		{
			ActionAfterEndOfTheGame();
			return false;
		}
		else if (infoFromKeyBoard == ALL_GOOD) // w przeciwnym wypadku (!ESC) funkcja sie normalnie wykonuje
		{
			int currentNumberOfFilledLines = board_.GetNumberOfFilledLines_();
			std::string currentLevel = board_.GetNameOfLevel();

			board_.CreateSurfaceToPutTextOn(pRenderer_, currentNumberOfFilledLines, currentLevel); //utworzenie tekstur dla tekstu

			SDL_SetRenderDrawColor(pRenderer_, 0x00, 0x00, 0x00, 0x00); //ustawienie koloru siatki

			SDL_RenderClear(pRenderer_); //usuniecie tla

			board_.DrawBoard(pRenderer_); //narysowanie siatki powierzchni gry

			brick_.DrawBrick(pRenderer_); //narysowanie danego klocka

			if (SDL_GetTicks() > moveTime_)
			{
				moveTime_ += SetDifficultyLevelOfGame(); //czas miedzy klatkami

				Brick tempBrick = brick_; //utworzenie kopii, ktora bedziemy operowac

				tempBrick.MoveBrick(0, 1);

				if (CheckCollision(tempBrick)) //jesli wykryto jakakolwiek kolizje, niemozliwa jest dalsza gra
				{
					ActionAfterEndOfTheGame();
					return false;
				}
			}
			SDL_RenderPresent(pRenderer_); //uaktualnienie tla

			return true;
		}
		else return false;

	}
	catch (std::runtime_error)
	{
		std::string information = "Error during executing program!";
		return false;
	}
}

int Draw::HandleOfKeyActions()
{
	SDL_Event keyHandle;
	if (SDL_WaitEventTimeout(&keyHandle, 100))
	{
		switch (keyHandle.type)
		{
		case SDL_KEYDOWN: //gdy przycisk jest wcisniety
		{
			switch (keyHandle.key.keysym.sym) //wczytanie kodu odpowiedniego klawisza
			{
			case SDLK_F1: //wlaczanie muzyki
				sound_.playMusic();
				break;

			case SDLK_F2: //wylaczenie muzyki
				if(Mix_PlayingMusic())
					Mix_HaltMusic();
				break;

			case SDLK_DOWN: //przyspieszenie, 2 w dol
				MoveBrickByKeys(0, 2);
				break;

			case SDLK_RIGHT: //przesuniecie w prawo
				MoveBrickByKeys(1, 0);
				break;

			case SDLK_LEFT: //przesuniecie w lewo
				MoveBrickByKeys(-1, 0);
				break;

			case SDLK_SPACE: //obrot figury
			{
				sound_.playComunicates(SPACE); //odtwarzanie dzwieku

				Brick tempBrick = brick_; //utworzenie tymczasowej figury
				tempBrick.RotateBrick(); //obrot figury
				if (!board_.IsCollision(tempBrick))//sprawdzenie czy zaszla kolizja
					brick_ = tempBrick; //jesli nie zaszla, przypisujemy tymczasowa figure 
						// na ktorej operowalismy do elementu klasy
			}
			break;

			case SDLK_ESCAPE: //wyjscie z gry
			{
				return PRESSED_ESC;
			}
			break;
			}
		}
		break;

		case SDL_QUIT:
			throw std::runtime_error("SDL_QUIT");
		}
		return ALL_GOOD;
	}
	else return ALL_GOOD;
}

void Draw::MoveBrickByKeys(int x, int y)
{
	Brick tempBrick = brick_; //utworzenie tymczasowej figury

	tempBrick.MoveBrick(x, y); //ruszenie figury o koordynaty przekazane do funkcji

	if (!board_.IsCollision(tempBrick)) //sprawdzenie czy zaszla kolizja
		brick_ = tempBrick; //jesli nie zaszla, przypisujemy tymczasowa figure 
			// na ktorej operowalismy do elementu klasy
}

void Draw::ActionAfterEndOfTheGame()
{
	Mix_FadeOutMusic(500); //wygaszenie muzyki w tle

	SDL_BlitSurface(pEndImage_, NULL, pScreenSurface_, NULL); //wysiwetlenie koncowej grafiki
	SDL_UpdateWindowSurface(pWindow_); //uaktualnienie powierzchni okna

	sound_.playComunicates(DEFEAT); //odtworzenie dzwieku przegranej
	SDL_Delay(1500); //opoznienie zeby mozna odwtorzyc dzwiek
}

bool Draw::CheckCollision(Brick & brick)
{
	if (board_.IsCollision(brick)) //jesli wykryto pierwsza kolizje
	{
		board_.MergeBricks(brick_); //laczenie klockow
		brick_ = brick_.RandomizeTypeOfBrick(); //wybranie typu nowego klocka

		if (board_.IsCollision(brick_)) //jesli bedzie ponowna kolizja
		{ //brak mozliwosci kontynuacji gry
			//zapisanie stanu gry
			SetLinesResult(board_.GetNumberOfFilledLines_());
			SetLevel(GetMoveTime());

			return true; //nie mozna dalej kontynuowac gry
		}
		else//mozna kontynuowac gre
		{
			sound_.playComunicates(BRICK_PLACED); //odtworzenie dzwieku ulozonego klocka
			return false;
		}
	}
	else
	{
		brick_ = brick; //przypisanie elementowi klasy, klocka na ktorym wczesniej operowalismy
		return false; //mozna kontynuowac gre
	}
}

int Draw::SetDifficultyLevelOfGame()
{
	int moveTime = 0, lines = 0;
	lines = board_.GetNumberOfFilledLines_(); //pobranie aktualnej liczby wypelnionych linii

	//ustawianie poziomu na podstawie ilosci wypelnionych linii:
	if (lines >= 0 && lines < MOVES_TO_CHANGE_LVL)
	{
		moveTime = BEGINNER;
		SetLevel(BEGINNER);
	}
	else if (lines >= MOVES_TO_CHANGE_LVL && lines < MOVES_TO_CHANGE_LVL * 2)
	{
		moveTime = EASY;
		SetLevel(EASY);
	}
	else if (lines >= MOVES_TO_CHANGE_LVL * 2 && lines < MOVES_TO_CHANGE_LVL * 3)
	{
		moveTime = INTERMEDIATE;
		SetLevel(INTERMEDIATE);
	}
	else if (lines >= MOVES_TO_CHANGE_LVL * 3 && lines < MOVES_TO_CHANGE_LVL * 4)
	{
		moveTime = HARD;
		SetLevel(HARD);
	}
	else if (lines >= MOVES_TO_CHANGE_LVL * 4 && lines < INT_MAX)
	{
		moveTime = PROFESSIONAL;
		SetLevel(PROFESSIONAL);
	}

	return moveTime;
}