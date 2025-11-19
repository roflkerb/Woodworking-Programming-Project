// Woodworking Project 2 - ITCS 2350.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Updated: adds title screen with large green text and menu to choose Quick Calculator or Custom Project Planner.

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <limits>
#include <cctype>
#include <windows.h>

// Add these lines before using std::numeric_limits to avoid macro conflicts
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

struct Section
{
	float length = 0.0f;
	float width = 0.0f;
	float thickness = 0.0f;
	float boardFootage = 0.0f;
};

// ReadFloat now supports optional min/max bounds and will re-prompt until a valid numeric value inside range is provided.
static float ReadFloat(const std::string &prompt, float minValue = std::numeric_limits<float>::lowest(), float maxValue = std::numeric_limits<float>::max())
{
	std::string input;
	while (true)
	{
		std::cout << prompt;
		if (!std::getline(std::cin, input))
		{
			// EOF or stream error - exit gracefully
			std::cout << "\nInput stream closed. Exiting.\n";
			std::exit(0);
		}

		// Trim leading/trailing whitespace by checking emptiness after possible whitespace-only input
		bool allSpace = true;
		for (char ch : input)
		{
			if (!std::isspace(static_cast<unsigned char>(ch)))
			{
				allSpace = false;
				break;
			}
		}
		if (input.empty() || allSpace)
		{
			std::cout << "No input entered. Please enter a numeric value.\n";
			continue;
		}

		try
		{
			size_t idx = 0;
			float value = std::stof(input, &idx);

			// Ensure the whole string was a valid number (no trailing garbage)
			// skip trailing spaces
			while (idx < input.size() && std::isspace(static_cast<unsigned char>(input[idx]))) ++idx;
			if (idx != input.size())
			{
				std::cout << "Invalid characters found in input. Please enter only a number (e.g. 12.5).\n";
				continue;
			}

			if (value < minValue || value > maxValue)
			{
				if (minValue != std::numeric_limits<float>::lowest() && maxValue != std::numeric_limits<float>::max())
					std::cout << "Please enter a value between " << minValue << " and " << maxValue << ".\n";
				else if (minValue != std::numeric_limits<float>::lowest())
					std::cout << "Please enter a value greater than " << minValue << ".\n";
				else if (maxValue != std::numeric_limits<float>::max())
					std::cout << "Please enter a value less than " << maxValue << ".\n";
				continue;
			}

			return value;
		}
		catch (const std::invalid_argument &)
		{
			std::cout << "Invalid number. Please enter a numeric value (e.g. 12.5).\n";
		}
		catch (const std::out_of_range &)
		{
			std::cout << "Value out of range. Please enter a reasonably sized number.\n";
		}
	}
}

static int ReadInt(const std::string &prompt, int minValue, int maxValue)
{
	std::string input;
	while (true)
	{
		std::cout << prompt;
		if (!std::getline(std::cin, input))
		{
			std::cout << "\nInput stream closed. Exiting.\n";
			std::exit(0);
		}

		try
		{
			size_t idx = 0;
			int value = std::stoi(input, &idx);

			// skip trailing spaces
			while (idx < input.size() && std::isspace(static_cast<unsigned char>(input[idx]))) ++idx;
			if (idx != input.size())
			{
				std::cout << "Invalid characters found in input. Please enter an integer.\n";
				continue;
			}

			if (value < minValue || value > maxValue)
			{
				std::cout << "Please enter an integer between " << minValue << " and " << maxValue << ".\n";
				continue;
			}
			return value;
		}
		catch (...)
		{
			std::cout << "Invalid integer. Please try again.\n";
		}
	}
}

// Quick calculator: single-section board footage calculator, allows repeated calculations in one session.
static void QuickCalculator()
{
	std::cout << "\n--- Quick Calculator ---\n";
	while (true)
	{
		// Require strictly positive dimensions for a meaningful result.
		float length = ReadFloat("Enter the length in inches: ", std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
		if (length <= 0.0f)
		{
			std::cout << "Length must be greater than 0.\n";
			continue;
		}

		float width = ReadFloat("Enter the width in inches: ", std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
		if (width <= 0.0f)
		{
			std::cout << "Width must be greater than 0.\n";
			continue;
		}

		float thickness = ReadFloat("Enter the thickness in inches: ", std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
		if (thickness <= 0.0f)
		{
			std::cout << "Thickness must be greater than 0.\n";
			continue;
		}

		float boardFootage = (length * width * thickness) / 144.0f;
		std::cout << "\nBoard footage needed: " << std::fixed << std::setprecision(3) << boardFootage << " bd ft\n";

		// Ask whether to perform another calculation
		std::string again;
		while (true)
		{
			std::cout << "Perform another quick calculation? (y/n): ";
			if (!std::getline(std::cin, again))
			{
				std::cout << "\nInput stream closed. Exiting.\n";
				std::exit(0);
			}
			if (!again.empty())
			{
				char c = static_cast<char>(std::tolower(static_cast<unsigned char>(again[0])));
				if (c == 'y')
					break; // outer while loop continues for another calculation
				if (c == 'n')
					return; // exit QuickCalculator and return to caller
			}
			std::cout << "Please enter 'y' or 'n'.\n";
		}
	}
}

// Display large green title and return the user's menu choice (1 = quick, 2 = custom)
static int ShowTitleMenu()
{
	// Get console handle and original attributes so we can restore color
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	WORD originalAttr = 0;
	if (hOut != INVALID_HANDLE_VALUE && GetConsoleScreenBufferInfo(hOut, &csbi))
		originalAttr = csbi.wAttributes;

	// Set bright green and print ASCII banner
	if (hOut != INVALID_HANDLE_VALUE)
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	std::cout << R"(
	 __    __                _                    _     _				
	/ / /\ \ \___   ___   __| |_      _____  _ __| | _ (_)_ __   __ _ 
	\ \ / \/ / _ \ / _ \ / _` \ \ / \/ / _ \| '__| |/ /| | '_ \ / _` |
	 \ / \  / (_) | (_) | (_| |\ V  V / (_) | |  |  <| | | | | | (_| |
	  \ / \/ \___/ \___ /\__,_| \_/\_/ \___/|_|  |_|\_\|_|_| |_|\__, |
	                                                            |___/ 
	)" << "\n";

	// Restore original attributes
	if (hOut != INVALID_HANDLE_VALUE && originalAttr != 0)
		SetConsoleTextAttribute(hOut, originalAttr);

	std::cout << "Choose an option:\n";
	std::cout << "  1) Quick calculator (single-section)\n";
	std::cout << "  2) Custom project planner (multiple sections, table output)\n";
	int choice = ReadInt("Enter choice (1-2): ", 1, 2);
	return choice;
}

int main()
{
	// Show title/menu first and require choice
	int initialChoice = ShowTitleMenu();

	if (initialChoice == 1)
	{
		QuickCalculator();
		return 0; // exit after quick calculator session
	}

	// Variables to store user inputs for the custom planner
	std::string projectType;
	std::string woodType;
	std::string deadline;

	std::cout << "Welcome to the Woodworking Project Planner!\n";
	std::cout << "This program will help you plan your woodworking project by gathering some information and calculating the board footage needed.\n";
	std::cout << "Let's get started with some questions about your project.\n\n";

	// Project metadata
	std::cout << "What type of woodworking project are you interested in? ";
	std::getline(std::cin, projectType);

	std::cout << "What type of wood do you prefer for your project? ";
	std::getline(std::cin, woodType);

	std::cout << "What is your deadline for completing the project? ";
	std::getline(std::cin, deadline);

	std::cout << "\nYou have chosen a " << projectType << " project using " << woodType
			  << " wood, with a deadline of " << deadline << ".\n";

	// Ask how many sections
	int maxSections = 20; // reasonable upper limit
	int sectionsCount = ReadInt("\nHow many sections does your project have? ", 1, maxSections);

	// Collect dimensions for each section
	std::vector<Section> sections;
	sections.reserve(sectionsCount);

	for (int i = 0; i < sectionsCount; ++i)
	{
		std::cout << "\n--- Section " << (i + 1) << " ---\n";
		Section s;
		s.length = ReadFloat("Enter the length in inches: ", std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
		s.width = ReadFloat("Enter the width in inches: ", std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
		s.thickness = ReadFloat("Enter the thickness in inches: ", std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
		s.boardFootage = (s.length * s.width * s.thickness) / 144.0f;
		sections.push_back(s);
		std::cout << "Calculated board footage for Section " << (i + 1) << ": " << std::fixed << std::setprecision(3) << s.boardFootage << " bd ft\n";
	}

	// Calculate totals across all sections
	float totalLength = 0.0f;
	float totalWidth = 0.0f;
	float totalThickness = 0.0f;
	float totalBoardFootage = 0.0f;
	for (const auto &s : sections)
	{
		totalLength += s.length;
		totalWidth += s.width;
		totalThickness += s.thickness;
		totalBoardFootage += s.boardFootage;
	}

	// Print results as a table; title uses the chosen project type
	std::cout << "\n" << projectType << ":\n\n";

	const int labelWidth = 24;
	const int colWidth = 14;
	const int colCount = sectionsCount + 1; // extra column for Totals

	// Header row
	std::cout << std::left << std::setw(labelWidth) << "";
	for (int i = 0; i < sectionsCount; ++i)
	{
		std::string header = "Section " + std::to_string(i + 1);
		std::cout << std::right << std::setw(colWidth) << header;
	}
	std::cout << std::right << std::setw(colWidth) << "Total";
	std::cout << "\n";

	// Separator line
	int totalWidthChars = labelWidth + colWidth * colCount;
	std::cout << std::string(totalWidthChars, '-') << "\n";

	// Length row
	std::cout << std::left << std::setw(labelWidth) << "Length (in):";
	for (const auto &s : sections)
		std::cout << std::right << std::setw(colWidth) << std::fixed << std::setprecision(2) << s.length;
	std::cout << std::right << std::setw(colWidth) << std::fixed << std::setprecision(2) << totalLength;
	std::cout << "\n";

	// Width row
	std::cout << std::left << std::setw(labelWidth) << "Width (in):";
	for (const auto &s : sections)
		std::cout << std::right << std::setw(colWidth) << std::fixed << std::setprecision(2) << s.width;
	std::cout << std::right << std::setw(colWidth) << std::fixed << std::setprecision(2) << totalWidth;
	std::cout << "\n";

	// Thickness row
	std::cout << std::left << std::setw(labelWidth) << "Thickness (in):";
	for (const auto &s : sections)
		std::cout << std::right << std::setw(colWidth) << std::fixed << std::setprecision(2) << s.thickness;
	std::cout << std::right << std::setw(colWidth) << std::fixed << std::setprecision(2) << totalThickness;
	std::cout << "\n";

	// Board footage row
	std::cout << std::left << std::setw(labelWidth) << "Board Footage (bd ft):";
	for (const auto &s : sections)
		std::cout << std::right << std::setw(colWidth) << std::fixed << std::setprecision(3) << s.boardFootage;
	std::cout << std::right << std::setw(colWidth) << std::fixed << std::setprecision(3) << totalBoardFootage;
	std::cout << "\n";

	return 0;
}
