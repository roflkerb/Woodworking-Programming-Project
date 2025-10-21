// Woodworking Questionaire.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

int main()
{
    //Vairables to store user inputs
	std::string projectType;
	std::string woodType;
	std::string deadline;

	//Ask the first question
	std::cout << "What type of woodworking project are you interested in? ";
	std::getline(std::cin, projectType);
	//Ask the second question
	std::cout << "What type of wood do you prefer for your project? ";
	std::getline(std::cin, woodType);
	//Ask the third question
	std::cout << "What is your deadline for completing the project? ";
	std::getline(std::cin, deadline);

	//Display the collected information
	std::cout << "\nYou have chosen a " << projectType << " project using " << woodType << " wood, with a deadline of " << deadline << ".\n";

	return 0;
}

