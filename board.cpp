#pragma region Included elements

#include <iostream>
#include "definitions.h"
#include "board.h"
#include "brick.h"

#pragma endregion

#pragma region Constructors and deconstructors

Board::Board() : net_{ {false} }, numberOfFilledLines_(0)
{
	//inicjlizacja biblioteki 
	if (TTF_Init())
	{
		throw std::runtime_error("Cannot initialize library!");
	}

	//zaladowanie czcionki
	fontStyle = TTF_OpenFont("Fonts/sanson.otf", 25);

	//sprawdzenie czy udalo sie zaladowac czcionke
	if (fontStyle == nullptr)
	{
		throw std::runtime_error("Cannot open font!");
	}
}

Board::~Board()
{
	TTF_CloseFont(fontStyle);
	TTF_Quit();
}

#pragma endregion

#pragma region Getters and setters
int Board::GetNumberOfFilledLines_() const
{
	return numberOfFilledLines_;
}

void Board::SetNumberOfFilledLines_(int number)
{
	numberOfFilledLines_ = number;
}

std::string Board::GetNameOfLevel()
{
	if (numberOfFilledLines_ >= 0 && numberOfFilledLines_ < MOVES_TO_CHANGE_LVL)
		return BEGINNER_S;
	else if (numberOfFilledLines_ >= MOVES_TO_CHANGE_LVL && numberOfFilledLines_ < MOVES_TO_CHANGE_LVL * 2)
		return EASY_S;
	else if (numberOfFilledLines_ >= MOVES_TO_CHANGE_LVL * 2 && numberOfFilledLines_ < MOVES_TO_CHANGE_LVL * 3)
		return INTERMEDIATE_S;
	else if (numberOfFilledLines_ >= MOVES_TO_CHANGE_LVL * 3 && numberOfFilledLines_ < MOVES_TO_CHANGE_LVL * 4)
		return HARD_S;
	else if (numberOfFilledLines_ >= MOVES_TO_CHANGE_LVL * 4 && numberOfFilledLines_ < INT_MAX)
		return PROFESSIONAL_S;
}

SDL_Rect Board::GetLevelRectangle()
{
	return levelRectangle;
}

SDL_Rect Board::GetLinelRectangle()
{
	return lineNumberRectangle;
}

void Board::SetLevelRectangle(int x, int y)
{
	levelRectangle.x = x;
	levelRectangle.y = y;
}

void Board::SetLineNumberRectangle(int x, int y)
{
	lineNumberRectangle.x = x;
	lineNumberRectangle.y = y;
}

#pragma endregion

void Board::DrawBoard(SDL_Renderer * pRenderer)
{
	for (int x = 0; x < GAME_WIDTH; x++)
	{
		for (int y = 0; y < GAME_HEIGHT; y++)
		{
			if (net_[x][y])
			{
				SDL_RenderDrawPoint(pRenderer, x, y); //renderuje punkt tablicy = true czyli pelny
			}
			else
			{
				SDL_SetRenderDrawColor(pRenderer, 0x6c, 0x7a, 0x89, 0x01); //ustawienie koloru
				SDL_Rect boardRectangle{ x * DIMENSION_OF_RECTANGLE + 1, y * DIMENSION_OF_RECTANGLE + 1,
					DIMENSION_OF_RECTANGLE - 1,DIMENSION_OF_RECTANGLE - 1 }; //utworzenie prostokata ktory bedzie rysowany
				SDL_RenderFillRect(pRenderer, &boardRectangle); //wypelnienie prostokata
			}

			//rysowanie obwodki ramki
			SDL_SetRenderDrawColor(pRenderer, 0x00, 0x00, 0x00, 0x00); //ustawienie koloru
			SDL_Rect frameSectionRectangle{ 0, SCREEN_HEIGHT - SCORE_SECTION_HEIGHT + 1, SCREEN_WIDTH, SCORE_SECTION_HEIGHT };
			SDL_RenderFillRect(pRenderer, &frameSectionRectangle); //wypelnienie prostokata

			//rysowanie ramki sekcji z wynikami
			SDL_SetRenderDrawColor(pRenderer, 0x2e, 0x31, 0x31, 0x01); //ustawienie koloru
			SDL_Rect borderOfScoreSection{ 1, SCREEN_HEIGHT - SCORE_SECTION_HEIGHT + 1,
				SCREEN_WIDTH - 1, SCORE_SECTION_HEIGHT - 2 }; //utworzenie prostokata ktory bedzie rysowany
			SDL_RenderFillRect(pRenderer, &borderOfScoreSection); //wypelnienie prostokata

			//rysowanie sekcji z wynikami
			SDL_SetRenderDrawColor(pRenderer, 0x6c, 0x7a, 0x89, 0x01); //ustawienie koloru
			SDL_Rect scoreSectionRectangle{ SIZE_OF_SCORE_BORDER, SCREEN_HEIGHT - SCORE_SECTION_HEIGHT + SIZE_OF_SCORE_BORDER + 1,
				SCREEN_WIDTH - SIZE_OF_SCORE_BORDER * 2, SCORE_SECTION_HEIGHT - SIZE_OF_SCORE_BORDER * 2 }; //utworzenie prostokata ktory bedzie rysowany
			SDL_RenderFillRect(pRenderer, &scoreSectionRectangle); //wypelnienie prostokata

			//rysowanie tekstow
			SDL_RenderCopy(pRenderer, lineNumberTexture, nullptr, &lineNumberRectangle); //renderowanie tekstu liczby linii
			SDL_RenderCopy(pRenderer, levelTexture, nullptr, &levelRectangle); //renderowanie tekstu poziomu gry
		}
	}
}

bool Board::IsCollision(Brick & brick) const
{
	for (int i = 0; i < BRICK_DIMENSION; i++)
	{
		for (int j = 0; j < BRICK_DIMENSION; j++)
		{
			if (brick.IsBrickHere(i, j)) //jesli znaleziono klocek
			{
				//wyznaczenie koordynatow dla kazdej iteracji petli
				int xCoord = brick.GetXCoordinate() + i;
				int yCoord = brick.GetYCoordinate() + j;

				//sprawdzenie czy klocek koliduje 
				if (xCoord < 0 || xCoord >= GAME_WIDTH || yCoord < 0 || yCoord >= GAME_HEIGHT)
					return true;
				else if (net_[xCoord][yCoord])
					return true;
			}
		}
	}
	return false;
}

void Board::MergeBricks(Brick & brick)
{
	for (int i = 0; i < BRICK_DIMENSION; i++)
	{
		for (int j = 0; j < BRICK_DIMENSION; j++)
		{
			if (brick.IsBrickHere(i, j)) //jesli dany klocek znajduje sie w tym miejscu
			{ //poszerzane jest pole tablicy, przez dodanie wartosci true:
				int xCoord = brick.GetXCoordinate() + i;
				int yCoord = brick.GetYCoordinate() + j;

				net_[xCoord][yCoord] = true;
			}
		}
	}

	DeleteFilledLine(); //sprawdzenie czy moze trzeba usunac linie
}

void Board::DeleteFilledLine()
{
	for (int row = 0; row <= (GAME_HEIGHT - 1); row++) //sprawdzanie do przedostatniej linii, bo jesli jest w ostatniej to 
	{ //zostanie wykryta kolizja row gra sie zakonczy
		bool filledLine = true;

		for (int j = 0; j < GAME_WIDTH; j++) //sprawdzanie wiersza
		{
			if (!net_[j][row]) //jesli jakis kwadrat jest pusty, to linia nie moze byc wypelniona
				filledLine = false;
		}

		if (filledLine) //jesli wykryto pelna linie
		{
			sound_.playComunicates(LINE); //odtworzenie dzwieku usuniecia linii
			numberOfFilledLines_++; //zwiekszenie ilosci wypelnionych linii

			for (int k = row - 1; k >= 0; k--)
			{
				for (int x = 0; x < GAME_WIDTH; x++) //usuniecie linii
				{
					net_[x][k + 1] = net_[x][k];
				}
			}
		}
	}
}

void Board::CreateSurfaceToPutTextOn(SDL_Renderer * renderer, int number, std::string level)
{
	//-------------------------------------------------------------------------------------
	//dla liczby wypelnionych linii:

	SDL_Color lineNumberColor = { 0x6f, 0xe8, 0x32, 0x01 }; //kolor z aktualnym numerem linii
	std::string temp = "Filled  lines :          " + std::to_string(number);
	const char * toDisplay = temp.std::string::c_str(); //wyswietlany ciag znakow

	SDL_Surface * lineNumberSurface = TTF_RenderText_Solid(fontStyle, toDisplay, lineNumberColor);
	lineNumberTexture = SurfaceToTexture(lineNumberSurface, renderer);

	//dopasowanie tekstury do danego obszaru (prostokat lineNumberRectangle)
	SDL_QueryTexture(lineNumberTexture, NULL, NULL, &lineNumberRectangle.w, &lineNumberRectangle.h);
	lineNumberRectangle.x = X_TEXT;
	lineNumberRectangle.y = Y_TEXT;

//-------------------------------------------------------------------------------------
	//dla poziomu:

	SDL_Color levelColor = lineNumberColor; //taki sam kolor, jak dla tekstu linijke wyzej
	SDL_Color highestLevelColor = { 0xf2, 0x26, 0x13, 0x01 }; //kolor dla najwyzszego poziomu
	std::string spaces = {}; //ilosc spacji dodawana do koncowego stringa

	if (level == PROFESSIONAL_S) //dla najwyzszego poziomu kolor zmieni sie na czerwony
		levelColor = highestLevelColor;

	//ustawianie odstepow tekstu w zaleznosci od aktualnego poziomu trudnosci
	if (level == EASY_S || level == HARD_S)
		spaces = "     ";
	else if (level == BEGINNER_S)
		spaces = "  ";
	else spaces = "";

	temp = "Level :            " + spaces + level;
	toDisplay = temp.std::string::c_str(); //konwersja stringa na const char *

	SDL_Surface * levelSurface = TTF_RenderText_Solid(fontStyle, toDisplay, levelColor);
	levelTexture = SurfaceToTexture(levelSurface, renderer);

	SDL_QueryTexture(levelTexture, NULL, NULL, &levelRectangle.w, &levelRectangle.h);
	levelRectangle.x = X_TEXT;
	levelRectangle.y = Y_TEXT + 40;
}

SDL_Texture * Board::SurfaceToTexture(SDL_Surface * surf, SDL_Renderer * renderer)
{
	SDL_Texture* text;

	text = SDL_CreateTextureFromSurface(renderer, surf);

	SDL_FreeSurface(surf); //zwolnienie zasobow dla renderowanej powierzchni

	return text;
}