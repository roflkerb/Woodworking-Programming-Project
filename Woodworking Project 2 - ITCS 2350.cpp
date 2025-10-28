// Woodworking Project 2 - ITCS 2350.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iomanip>

int main()
{
	//Vairables to store user inputs
	std::string projectType;
	std::string woodType;
	std::string deadline;
	std::string lengthOne;
	std::string widthOne;
	std::string thicknessOne;

	//Greeting the user and explaining the program
	std::cout << "Welcome to the Woodworking Project Planner!\n";
	std::cout << "This program will help you plan your woodworking project by gathering some information and calculating the board footage needed.\n";
	std::cout << "Let's get started with some questions about your project.\n";

	//Asking the first question
	std::cout << "What type of woodworking project are you interested in? ";
	std::getline(std::cin, projectType);

	//Asking the second question
	std::cout << "What type of wood do you prefer for your project? ";
	std::getline(std::cin, woodType);

	//Asking the third question
	std::cout << "What is your deadline for completing the project? ";
	std::getline(std::cin, deadline);

	//Display the collected information
	std::cout << "\nYou have chosen a " << projectType << " project using " << woodType << " wood, with a deadline of " << deadline << ", good luck and remember to always take joy in the process of creating something wonderful!\n";

	//Start the Board Footage calulation using user defined sections
	std::cout << "\nNow let's calculate the board footage needed for your project.\n";

	//Asking for length
	std::cout << "Enter the length of the first section in inches: ";
	std::getline(std::cin, lengthOne);

	//Asking for width
	std::cout << "Enter the width of the first section in inches: ";
	std::getline(std::cin, widthOne);

	//Asking for thickness
	std::cout << "Enter the thickness of the first section in inches: ";
	std::getline(std::cin, thicknessOne);

	//Convert string inputs to float for calculation
	float length = std::stof(lengthOne);
	float width = std::stof(widthOne);
	float thickness = std::stof(thicknessOne);

	//Calculate board footage
	float boardFootage = (length * width * thickness) / 144;

	//Display the result
	std::cout << "\nThe board footage needed for this section is: " << boardFootage << " board feet.\n";

	// Print a formatted table titled "Project Dimensions:" with a column heading "Section 1"
	std::cout << "\nProject Dimensions:\n\n";

	// Header (leave first column for labels, second column is the Section 1 values)
	std::cout << std::left << std::setw(12) << "Section 1" << "\n";
	std::cout << std::string(36, '-') << "\n";

	// Rows
	std::cout << std::left << std::setw(24) << "Length (in):" << std::right << std::setw(12) << std::fixed << std::setprecision(2) << length << "\n";
	std::cout << std::left << std::setw(24) << "Width (in):" << std::right << std::setw(12) << std::fixed << std::setprecision(2) << width << "\n";
	std::cout << std::left << std::setw(24) << "Thickness (in):" << std::right << std::setw(12) << std::fixed << std::setprecision(2) << thickness << "\n";
	std::cout << std::left << std::setw(24) << "Board Footage (bd ft):" << std::right << std::setw(12) << std::fixed << std::setprecision(2) << boardFootage << "\n";

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
