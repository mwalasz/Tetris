#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include <string>

/* STALE ZDEFINIOWANE W PROGRAMIE */

//sciezka do pliku z wynikami gry
const std::string GAME_RESULTS = "Results/gameResults.txt";

//ilosc typow figur
constexpr int TYPES = 7;

//wszystkie mozliwe rotacje figur
constexpr int NUM_OF_ROTATIONS = 4;	

//ilosc ruchow po ktorych poziom ulegnie zmianie
constexpr int MOVES_TO_CHANGE_LVL = 3; 

//wymiary generowanego okna gry
constexpr int SCORE_SECTION_HEIGHT = 100; //wysokosc sekcji z wynikami
constexpr int SIZE_OF_SCORE_BORDER = 10;

constexpr int SCREEN_WIDTH = 360;
constexpr int SCREEN_HEIGHT = 720 + SCORE_SECTION_HEIGHT;
//-----------------------------

//wymiary generowanego okna menu
constexpr int MENU_WIDTH = 500;
constexpr int MENU_HEIGHT = 600;
//-----------------------------

//ilosc prostokatow z ktorych sklada sie pole gry
constexpr int GAME_WIDTH = 10;
constexpr int GAME_HEIGHT = 20;
//-----------------------------

//koordynaty tekstu
constexpr int X_TEXT = 65;
constexpr int Y_TEXT = 738;

//wymiary pojedynczego rysowanego prostokata
constexpr int BRICK_DIMENSION = 4; //wysokosc figury
constexpr auto DIMENSION_OF_RECTANGLE = (SCREEN_WIDTH / 10); //rozmiar  rysowanego prostokata
//-----------------------------

//dostepne poziomy trudnosci (INT):
enum Level { BEGINNER = 800, EASY = 550, INTERMEDIATE = 350, HARD = 250, PROFESSIONAL = 120 };
// (STD::STRING):
const std::string BEGINNER_S = "BEGINNER";
const std::string EASY_S = "EASY";
const std::string INTERMEDIATE_S = "INTERMEDIATE";
const std::string HARD_S = "HARD";
const std::string PROFESSIONAL_S = "PROFESSIONAL";
//-----------------------------

//akcje po wcisnieciu przyciskow klawiatury
enum Actions { ALL_GOOD = 0, PRESSED_ESC };

//dzwieki do odtwarzania
enum Sounds { SPACE = 0, LINE, DEFEAT, BRICK_PLACED };

#endif