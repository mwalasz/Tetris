#include "results.h"

#pragma region Constructors and decontructors
Results::Results() : userName_("Unknown"), gameDuration_(0), level_(0),
linesFilled_(0), endTime_(0) {}

Results::~Results() {}
#pragma endregion

#pragma region Getters and setters

void Results::SetLinesResult(int number)
{
	linesFilled_ = number;
}

void Results::SetLevel(int number)
{
	if (number == BEGINNER)
		level_ = BEGINNER;
	if (number == EASY)
		level_ = EASY;
	if (number == INTERMEDIATE)
		level_ = INTERMEDIATE;
	if (number == HARD)
		level_ = HARD;
	if (number == PROFESSIONAL)
		level_ = PROFESSIONAL;
}

std::chrono::time_point<std::chrono::system_clock> Results::GetTimeForDuration()
{
	return std::chrono::system_clock::now();
}

std::string Results::GetEndTimeOfGame()
{
	auto time = std::chrono::system_clock::now(); //odczytanie czasu wywolania funkcji
	time_t endTime = std::chrono::system_clock::to_time_t(time); //konwersja na odp typ

	return ctime(&endTime); //konwersja time_t na string
}

void Results::SetGameDuration(double time)
{
	gameDuration_ = time;
}


int Results::GetLinesFilled() const
{
	return linesFilled_;
}

std::string Results::GetNameOfGameLevel()
{
	if (level_ == BEGINNER)
		return BEGINNER_S;
	else if (level_ == EASY)
		return EASY_S;
	else if (level_ == INTERMEDIATE)
		return INTERMEDIATE_S;
	else if (level_ == HARD)
		return HARD_S;
	else if (level_ == PROFESSIONAL)
		return PROFESSIONAL_S;
	else throw std::out_of_range("INCORRECT NUMBER");
}

double Results::GetGameDuration()
{
	return round(gameDuration_ * 100.0) / 100.0; //zaokraglenie do 2 znaczacych miejsc
}

#pragma endregion

std::string Results::GameDurationForDisplay()
{
	double temp = GetGameDuration();
	std::string toDisplay{};

	if (temp > 0 && temp < 60) //jesli gra trwala mniej niz minute
	{
		toDisplay = std::to_string((int)temp) + " sec";
	}
	else
	{
		//stracenie dokladnosci double, na rzecz przeliczenia na min i sec :(
		int seconds = (int)temp % 60;
		int minutes = ((int)temp / 60);
		toDisplay = std::to_string(minutes) + " min, " + std::to_string(seconds) + " sec";
	}

	return toDisplay;
}

void Results::SaveResultsToFile(const std::string & fileName)
{
	std::ofstream output; //strumien plikowy
	output.open(fileName, std::ios::app); //otwarcie pliku z dopisywaniem do zawartosci

	try
	{
		if (output) //jesli poprawnie otworzono plik
		{ //wypisanie statystyk
			output << "----------------------------------------" << std::endl
				<< "----------------------------------------" << std::endl
				<< "Completed lines: " << std::setw(23) << std::right << GetLinesFilled() << std::endl
				<< "Level at defeat: " << std::setw(23) << std::right << GetNameOfGameLevel() << std::endl
				<< "Duration of game: " << std::setw(22) << std::right << GameDurationForDisplay() << std::endl
				<< "----------------------------------------" << std::endl
				<< "Date of game: " << std::setw(27) << std::right << GetEndTimeOfGame()
				<< "----------------------------------------" << std::endl
				<< "----------------------------------------" << std::endl << std::endl;

			output.close(); //zamkniecie pliku
		}
	}
	catch (std::out_of_range)
	{
		std::cout << "Internal error occurred, while computing game level!";
	}
}
