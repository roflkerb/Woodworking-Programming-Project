// Woodworking Project 2 - ITCS 2350.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Updated: adds menu to collect N sections, prints results in a table, displays per-section values and totals,
// and uses the chosen project type as the table title.

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <limits>

struct Section
{
	float length = 0.0f;
	float width = 0.0f;
	float thickness = 0.0f;
	float boardFootage = 0.0f;
};

static float ReadFloat(const std::string &prompt)
{
	std::string input;
	while (true)
	{
		std::cout << prompt;
		std::getline(std::cin, input);
		try
		{
			float value = std::stof(input);
			return value;
		}
		catch (...)
		{
			std::cout << "Invalid number. Please enter a numeric value (e.g. 12.5).\n";
		}
	}
}

static int ReadInt(const std::string &prompt, int minValue, int maxValue)
{
	std::string input;
	while (true)
	{
		std::cout << prompt;
		std::getline(std::cin, input);
		try
		{
			int value = std::stoi(input);
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

int main()
{
	// Variables to store user inputs
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
		s.length = ReadFloat("Enter the length in inches: ");
		s.width = ReadFloat("Enter the width in inches: ");
		s.thickness = ReadFloat("Enter the thickness in inches: ");
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
