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

	return 0;
}

