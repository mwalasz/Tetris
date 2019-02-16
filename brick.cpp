#pragma region Included elements

#include <string>
#include <chrono>
#include <random>
#include "definitions.h"
#include "brick.h"

#pragma endregion

#pragma region Constructors and decontructors

Brick::Brick(Type typeOfFigure) : typeOfBrick_(typeOfFigure), rotation_(0), x_(3), y_(0) {}

Brick::~Brick() {}

#pragma endregion

#pragma region Getters and setters

int Brick::GetXCoordinate() const
{
	return x_;
}

int Brick::GetYCoordinate() const
{
	return y_;
}

#pragma endregion

Brick::Type Brick::RandomizeTypeOfBrick()
{
	std::default_random_engine engine; //utworzenie silnika
	engine.seed(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> outputType(0, TYPES - 1);

	return (Type)outputType(engine); //rzutowanie wyniku losowania na dostepne typy figur
}

bool Brick::IsBrickHere(int x, int y) const
{
	//dostepne typy figur, 7 typow * 4 obroty
	//obrot figury jest realizowany przez przemieszczanie sie po tej tablicy,
	//po kolejnych obrotach
	static const char * Figures[TYPES][4] = {
		{
		  " *  "
		  " *  "
		  " *  "
		  " *  ",
		  "    "
		  "****"
		  "    "
		  "    ",
		  "  * "
		  "  * "
		  "  * "
		  "  * ",
		  "    "
		  "    "
		  "****"
		  "    ",
		},
		{
		  "  * "
		  "  * "
		  " ** "
		  "    ",
		  "    "
		  "*   "
		  "*** "
		  "    ",
		  " ** "
		  " *  "
		  " *  "
		  "    ",
		  "    "
		  "    "
		  "*** "
		  "  * ",
		},
		{
		  " *  "
		  " *  "
		  " ** "
		  "    ",
		  "    "
		  "*** "
		  "*   "
		  "    ",
		  " ** "
		  "  * "
		  "  * "
		  "    ",
		  "  * "
		  "*** "
		  "    "
		  "    ",
		},
		{
		  "    "
		  " ** "
		  " ** "
		  "    ",
		  "    "
		  " ** "
		  " ** "
		  "    ",
		  "    "
		  " ** "
		  " ** "
		  "    ",
		  "    "
		  " ** "
		  " ** "
		  "    ",
		},
		{
		  "  * "
		  " ** "
		  " *  "
		  "    ",
		  "    "
		  "**  "
		  " ** "
		  "    ",
		  " *  "
		  "**  "
		  "*   "
		  "    ",
		  "    "
		  "**  "
		  " ** "
		  "    ",
		},
		{
		  " *  "
		  " ** "
		  " *  "
		  "    ",
		  "    "
		  "*** "
		  " *  "
		  "    ",
		  " *  "
		  "**  "
		  " *  "
		  "    ",
		  " *  "
		  "*** "
		  "    "
		  "    ",
		},
		{
		  " *  "
		  " ** "
		  "  * "
		  "    ",
		  "    "
		  " ** "
		  "**  "
		  "    ",
		  " *  "
		  " ** "
		  "  * "
		  "    ",
		  "    "
		  " ** "
		  "**  "
		  "    ",
		},
	};

	return Figures[typeOfBrick_][rotation_][x + y * 4] != ' ';
}

void Brick::DrawBrick(SDL_Renderer * pRenderer)
{
	switch (typeOfBrick_) //wybranie koloru figury na podstawie jej typu
	{
		case I:
			SDL_SetRenderDrawColor(pRenderer, 0xf2, 0x26, 0x13, 0x01);
			break;
		case J:
			SDL_SetRenderDrawColor(pRenderer, 0xf0, 0xff, 0x00, 0x01);
			break;
		case L:
			SDL_SetRenderDrawColor(pRenderer, 0xa5, 0x37, 0xfd, 0x01);
			break;
		case O:
			SDL_SetRenderDrawColor(pRenderer, 0x4d, 0x05, 0xe6, 0x01);
			break;
		case S:
			SDL_SetRenderDrawColor(pRenderer, 0x81, 0xcf, 0xe0, 0x01);
			break;
		case T:
			SDL_SetRenderDrawColor(pRenderer, 0x00, 0xe6, 0x40, 0x01);
			break;
		case Z:
			SDL_SetRenderDrawColor(pRenderer, 0xf9, 0x69, 0x0e, 0x01);
			break;
	}

	for (int i = 0; i < BRICK_DIMENSION; i++)
	{
		for (int j = 0; j < BRICK_DIMENSION; j++)
		{
			if (IsBrickHere(i,j))
			{
				SDL_Rect rectangle{ (i + x_) * DIMENSION_OF_RECTANGLE + 1, (j + y_) * DIMENSION_OF_RECTANGLE + 1,
					DIMENSION_OF_RECTANGLE - 1, DIMENSION_OF_RECTANGLE - 1}; //rysowanie prostokata o danych koordynatach 
								//i wczesniej zadeklarowanych wymiarow pojedynczego kwadratu
				SDL_RenderFillRect(pRenderer, &rectangle);
			}
		}
	}
}

void Brick::MoveBrick(int dx, int dy)
{//przesuwanie koordynatow o wektor
	x_ += dx; 
	y_ += dy;
}

void Brick::RotateBrick()
{
	rotation_ += 3;
	rotation_ %= NUM_OF_ROTATIONS;
}